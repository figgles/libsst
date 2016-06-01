
#ifdef HAVE_XINPUT2
#include <dlfcn.h>
#include "XlibPrivate.h"
#include "XI2Private.h"

XI2Functions XI = { 0 };

void XI2_Load()
{
	const int flags = RTLD_LAZY | RTLD_GLOBAL;
	void* XI2lib;

	/* Try opening the correct SONAME version of libXi */
	XI2lib = dlopen("libXi.so.6", flags);

	/* Didn't work? */
	if(XI2lib == NULL)
	{
		/* Try a super-generic version */
		XI2lib = dlopen("libXi.so", flags);
		if(XI2lib == NULL)
			return;

	}
	
	/* Resolve symbols */
	XI.SelectEvents = dlsym(XI2lib, "XISelectEvents");
	XI.QueryVersion = dlsym(XI2lib, "XIQueryVersion");
	
	if(XI.SelectEvents == NULL || XI.QueryVersion == NULL)
	{
		dlclose(XI2lib);
		return;
	}	


	/* Save handle */
    XI.XI2lib = XI2lib;
    return;
}

/******************************************************************************/

void XI2_Unload()
{
    if(XI.XI2lib != NULL)
        dlclose(XI.XI2lib);
}

/******************************************************************************/

int XI2_IsLoaded()
{
	return (XI.XI2lib != NULL);
}

/******************************************************************************/

void XI2_IsSupportedOnConnection(SST_DisplayTarget_Xlib* displayTarget)
{
    int major = 2, minor = 0;
    int dummyEvent, dummyError;
        
    /* Default to NO */
    displayTarget->xi2Support = 0;
    displayTarget->xi2opcode = ~0;
        
    /* Check if server has XI at all. */
    if(X.QueryExtension(displayTarget->display, "XInputExtension", &displayTarget->xi2opcode, &dummyEvent, &dummyError))
    {
        /* OK, does it support XI2? */
		XI.QueryVersion(displayTarget->display, &major, &minor);
   
        /* If the version is at least 2.0, we're good */
        if(major * 100 + minor >= 200) {
			displayTarget->xi2Support = 1;
		}

    }
}

#endif
