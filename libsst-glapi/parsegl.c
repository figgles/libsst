/*
	parsegl.c
	Author: Patrick Baggett <ptbaggett@762studios.com>
	Created: 12/12/2012

	Purpose: 

	Parse GL function definitions and generate libsst-glapi code/headers

	License:

	This program is free software. It comes without any warranty, to
	the extent permitted by applicable law. You can redistribute it
	and/or modify it under the terms of the Do What The Fuck You Want
	To Public License, Version 2, as published by Sam Hocevar. See
	http://sam.zoy.org/wtfpl/COPYING for more details.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFS "gl33.txt"

typedef struct GLFunc
{
	char name[64];				/* Name of OpenGL function, sans "gl" prefix */
	char returnType[64];		/* C return value type */
	char argTypes[16][64];		/* C argument type */
	
	unsigned int constBitmask;	/* If bit 'n' is set, then parameter 'n' is a const parameter. highest bit is return type */
	unsigned int nrArgs;		/* Number of arguments in the function */
	
	struct GLFunc* next;		/* Next function in the list */
} GLFunc;

/* These test if parameter is marked as "const" */
#define ISCONST(func, n)	(func->constBitmask & (1u << n))
#define ISCONSTRETURN(func)	ISCONST(func, 31u)

/* Linked list of functions parsed */
GLFunc* first = NULL;
GLFunc* last = NULL;
unsigned int totalParsed = 0;

/******************************************************************************/

static void parseLine(const char* line);
static void genStruct(FILE* fp);
static void genLinkCode(FILE* fp);
static void genMacros(FILE* fp);
static void autogenHeader(FILE* fp) { fprintf(fp, "/* AUTOGENERATED BY parsegl.c -- DO NOT MODIFY */\n"); }

/******************************************************************************/

int main()
{
	char line[1024];
	FILE* fp = fopen(DEFS, "r");
	int c;
	int eolFound = 0;
	int k = 0;
	
	/* Can't open GL function definitions? */
	if(fp == NULL)
	{
		printf("Could not open file \"%s\" for reading\n", DEFS);
		exit(1);
	}
	
	/* Read each line of text until EOF */
	do
	{
		c = fgetc(fp);
		
		switch(c)
		{
			/* These end a line */
			case 0x0A:
			case 0x0D:
				eolFound = 1;
				line[k] = '\0';
				k=0;
				break;
			
			case EOF:
				break;
				
			/* Otherwise, copy the line */
			default:
				line[k] = (char)c;
				k++;
				break;
		}
		
		/* Time to parse a line? */
		if(eolFound)
		{
			parseLine(line);	
			eolFound = 0;
		}
	
	} while(c != EOF);

	fclose(fp);

	printf("%u GL functions parsed\n", totalParsed);

	/* Write API structure */
	fp = fopen("SST_GLAPIStruct.h", "w");
	if(fp != NULL)
	{
		autogenHeader(fp);
		genStruct(fp);
		fclose(fp);
	}

	/* Write runtime API resolution */
	fp = fopen("SST_GLAPIStruct.c", "w");
	if(fp != NULL)
	{
		autogenHeader(fp);
		genLinkCode(fp);

		fclose(fp);
	}
	
	/* Write canonical glDoThing() macros */
	fp = fopen("SST_GLAPIMacros.h", "w");
	if(fp != NULL)
	{
		autogenHeader(fp);
		genMacros(fp);
		fclose(fp);
	}
	
	/* Done */
	return 0;
}

/******************************************************************************/

/* Read the line and parse out any GL function definitions */
static void parseLine(const char* line)
{
	int exitTime;
	int k = 0;
	int nrFound = 0;
	char word[64];
	char* s = word;
	GLFunc* func;
	
	/* Ignore leading whitespace */
	while(isspace(*line))
		line++;
	
	/* Nothing to parse? */
	if(strlen(line) == 0)
		return;

	/* Ignore comment lines */
	if(line[0] == '/' && line[1] == '/')
		return;
	
	memset(word, 0, sizeof(word));
	func = (GLFunc*)calloc(1, sizeof(*func));

	/* Pull words out of the line */
	exitTime = 0;
	do
	{
		if(line[k] == '\0')
		{
			exitTime = 1;
			*s = '\0';
		}
		if(isspace(line[k]))
			*s = '\0';
		else
			*s = line[k];
		k++;

		/* Parse word time? */
		if(*s == '\0')
		{
			s = word;
			
			/* Skip all blank spaces */
			while(isspace(*s))
				s++;

			/* Non-zero lengths only, please */
			if(strlen(s) >= 0)
			{
		
				/* First word is the return value type */
				if(nrFound == 0)
				{
					if(strstr(s, "const_"))
					{
						func->constBitmask |= (1u << 31);
						s += strlen("const_");
					}
					
					strcpy(func->returnType, s);
				}
				else if (nrFound == 1) /* Second word is the function name */
					strcpy(func->name, s);
				else /* Remaining words are arguments */
				{
					int arg = nrFound - 2;
					
					/* Is it a const arg? */
					if(strstr(s, "const_"))
					{
						func->constBitmask |= (1u << arg);
						s += strlen("const_");
					}

					strcpy(func->argTypes[arg], s);
					func->nrArgs++;
				}
				
				nrFound++;

			} /* non-zero length string */

			s = word;
		} /* Done parsing word */
		else
			s++;

	} while(!exitTime);
	
	/* Store */
	if(first == NULL)
		first = func;
		
	if(last != NULL)
		last->next = func;
	last = func;
	totalParsed++;
	
}

/******************************************************************************/

static void genStruct(FILE* fp)
{
	const GLFunc* func = first;
	
	fprintf(fp,
	"#ifndef _SST_GLAPISTRUCT_H\n"
	"#define _SST_GLAPISTRUCT_H\n\n");
	fprintf(fp, "#include <SST/SST_GLAPIDefs.h>\n\n");
	fprintf(fp, "typedef struct SST_GLAPI\n{\n");
	while(func)
	{
		unsigned int i;
		
		/* Return value and name of function */
		fprintf(fp, "\t%s%s (OGLCALL* %s)(",
		ISCONSTRETURN(func) ? "const " : "",
		func->returnType,
		func->name);
	
		/* Run through each valid argument */
		for(i=0; i<func->nrArgs; i++)
		{
			if(ISCONST(func, i))
				fprintf(fp, "const ");
				
			fprintf(fp, "%s", func->argTypes[i]);
		
			if(i != func->nrArgs-1)
				fprintf(fp, ", ");
		}
		fprintf(fp, ");\n");
	
		func = func->next;
	}
	fprintf(fp, "\t/*======================================*/\n");
	fprintf(fp, "\tvoid* libGL; /* OpenGL library handle */\n");
	fprintf(fp, "\tchar* libGLName; /* OpenGL library name */\n");
	
	
	fprintf(fp, "} SST_GLAPI;\n#endif\n\n");
}

static void genLinkCode(FILE* fp)
{
	const GLFunc* func = first;
	fprintf(fp, "#include <SST/SST_GLAPIStruct.h>\n");
	fprintf(fp, "#include \"GLAPIPrivate.h\"\n\n");
	fprintf(fp, "void resolveGLAPI(const GLAPIResolver* resolver, struct SST_GLAPI* api)\n{\n");

	while(func)
	{
		unsigned int i;

		/* Resolve it */
		fprintf(fp, "\tapi->%s = resolveGLSymbol(resolver, \"gl%s\");\n",
			func->name, func->name);

		func = func->next;
	}

	fprintf(fp, "\n}\n");
}

static void genMacros(FILE* fp)
{
	const GLFunc* func = first;
	
	fprintf(fp,
	"#ifndef _SST_GLAPIMACROS_H\n"
	"#define _SST_GLAPIMACROS_H\n\n");
	
	while(func)
	{
		unsigned int i;

		/* #define a macro for it */
		fprintf(fp, "#define gl%s(",func->name);

		/* Label macro arguments as 'a', 'b', 'c', ... */
		for(i=0; i<func->nrArgs; i++)
		{
			fprintf(fp, "%c%s",
				'a'+i,
				i < func->nrArgs-1?",":"");
		}
		
		fprintf(fp, ") __sstglctx->%s(", func->name);

		/* Label macro arguments as 'a', 'b', 'c', ... */
		for(i=0; i<func->nrArgs; i++)
		{
			fprintf(fp, "(%c)%s",
				'a'+i,
				i < func->nrArgs-1?",":"");
		}
		fprintf(fp, ")\n");


		func = func->next;
	}

	

	fprintf(fp, " \n#endif\n\n");

}

