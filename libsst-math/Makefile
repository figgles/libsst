#	libsst-math/Makefile
#	Author: Charles Lena <cmlena@762studios.com>
#	Created: 5/17/2012
#
#	Purpose:
#
#	Makefile for libsst-math
#
#	License:
#
#	This program is free software. It comes without any warranty, to
#	the extent permitted by applicable law. You can redistribute it
#	and/or modify it under the terms of the Do What The Fuck You Want
#	To Public License, Version 2, as published by Sam Hocevar. See
#	http://sam.zoy.org/wtfpl/COPYING for more details.

#ifeq ($(IS_GCC),1)
#CFLAGS += -mssse3 -ftree-vectorize -ftree-vectorizer-verbose=5 -Wall -std=c99
#CODFLAG=-Wa,-a,-ad
#endif
#ifeq ($(IS_ICC), 1)
#CFLAGS=-vec-report2 -restrict -xSSSE3 -Wall -std=c99
#CODFLAG=-S -fcode-asm
#endif

BINNAME := $(DIST)/libsst-math.a
ifeq ($(TARGET),debug)
	BINNAME := $(subst .a,_d.a, $(BINNAME))
endif

#Required libraries
REQ_LIBS := libsst-math.a

# Generate the lib names with the full dist name.
# This is only used for dependency checking
REQ_LIBS_DIST := $(foreach lib,$(REQ_LIBS), $(DIST)/$(lib)) 

#Generate LDFLAGS for $REQ_LIBS: "libfoo.a" becomes "-lfoo"
REQ_LIBS_LDFLAGS := $(foreach lib,$(REQ_LIBS), $(subst lib,-l,$(lib)))
REQ_LIBS_LDFLAGS := -L$(DIST) $(foreach lib,$(REQ_LIBS_LDFLAGS), $(subst .a,,$(lib)))

DYNSRC_MAT= \
SST_Mat22f.c SST_Mat22d.c \
SST_Mat22i.c SST_Mat22u.c \
SST_Mat33f.c SST_Mat33d.c \
SST_Mat33i.c SST_Mat33u.c \
SST_Mat44f.c SST_Mat44d.c \
SST_Mat44i.c SST_Mat44u.c 

DYNSRC_VEC= \
SST_Vec2f.c   SST_Vec2d.c \
SST_Vec2i.c   SST_Vec2u.c \
SST_Vec3f.c   SST_Vec3u.c \
SST_Vec3d.c   SST_Vec3i.c \
SST_Vec4f.c   SST_Vec4d.c \
SST_Vec4i.c   SST_Vec4u.c 
DYNUNITTEST = $(addprefix ../ZTestSuite/Test-,$(DYNSRC_MAT:.c=.cpp)) $(addprefix ../ZTestSuite/Test-,$(DYNSRC_VEC:.c=.cpp))
DYNTEST : $(DYNTEST:.c=benchmark.c)
SRC=SST_Transform.c SST_Geo.c SST_VectorN.c
OBJ=$(addprefix obj/$(ARCH)/$(TARGET)/,$(subst .c,.o,$(SRC:.c=.o) $(DYNSRC_MAT:.c=.o) $(DYNSRC_VEC:.c=.o)) )
FULLOBJ=$(addprefix obj/$(ARCH)/$(TARGET)/,$(DYNTEST:.c=.o) )
CODs=$(SRC:.c=.cod)
PYFILE_MAT=./MatrixNxN.py
PYFILE_VEC=./VectorN.py
RANLIB?=ranlib

.PHONY: all clean cleanall assemblers

$(shell mkdir -p obj/$(ARCH)/$(TARGET))

$(BINNAME): $(OBJ) 
	$(AR) cru $@ $+
	$(RANLIB) $@

code:
	@rm -f $(DYNSRC_MAT) $(DYNSRC_VEC) $(DYNTEST) $(DYNUNITTEST)
	@$(MAKE) -C .. math

test.bin: $(FULLOBJ) $(REQ_LIBS_DIST) 
	@echo LD $@
	$(CC) $+ $(LDFLAGS) -o $@

###############################
# THIS IS THE MATRIX AREA     #
###############################
SST_Mat22f.c:
	@echo GEN $@
	@$(PYFILE_MAT) 2 float > SST_Mat22f.c

SST_Mat22d.c:
	@echo GEN $@
	@$(PYFILE_MAT) 2 double > SST_Mat22d.c

SST_Mat22i.c:
	@echo GEN $@
	@$(PYFILE_MAT) 2 int > SST_Mat22i.c

SST_Mat22u.c:
	@echo GEN $@
	@$(PYFILE_MAT) 2 "unsigned int" > SST_Mat22u.c

SST_Mat33f.c:
	@echo GEN $@
	@$(PYFILE_MAT) 3 float > SST_Mat33f.c

SST_Mat33d.c:
	@echo GEN $@
	@$(PYFILE_MAT) 3 double > SST_Mat33d.c

SST_Mat33i.c:
	@echo GEN $@
	@$(PYFILE_MAT) 3 int > SST_Mat33i.c

SST_Mat33u.c:
	@echo GEN $@
	@$(PYFILE_MAT) 3 "unsigned int" > SST_Mat33u.c

SST_Mat44f.c:
	@echo GEN $@
	@$(PYFILE_MAT) 4 float > SST_Mat44f.c

SST_Mat44d.c:
	@echo GEN $@
	@$(PYFILE_MAT) 4 double > SST_Mat44d.c

SST_Mat44i.c:
	@echo GEN $@
	@$(PYFILE_MAT) 4 int > SST_Mat44i.c

SST_Mat44u.c:
	@echo GEN $@
	@$(PYFILE_MAT) 4 "unsigned int" > SST_Mat44u.c

###############################
# THIS IS THE VECTOR AREA     #
###############################
SST_Vec2f.c:
	@echo GEN $@
	echo "$(PYFILE_VEC) 2 float > SST_Vec2f.c"
	@$(PYFILE_VEC) 2 float > SST_Vec2f.c

SST_Vec2d.c:
	@echo GEN $@
	@$(PYFILE_VEC) 2 double > SST_Vec2d.c

SST_Vec2i.c:
	@echo GEN $@
	@$(PYFILE_VEC) 2 int > SST_Vec2i.c

SST_Vec2u.c:
	@echo GEN $@
	@$(PYFILE_VEC) 2 "unsigned int" > SST_Vec2u.c

SST_Vec3f.c:
	@echo GEN $@
	@$(PYFILE_VEC) 3 float > SST_Vec3f.c

SST_Vec3d.c:
	@echo GEN $@
	@$(PYFILE_VEC) 3 double > SST_Vec3d.c

SST_Vec3i.c:
	@echo GEN $@
	@$(PYFILE_VEC) 3 int > SST_Vec3i.c

SST_Vec3u.c:
	@echo GEN $@
	@$(PYFILE_VEC) 3 "unsigned int" > SST_Vec3u.c

SST_Vec4f.c:
	@echo GEN $@
	@$(PYFILE_VEC) 4 float > SST_Vec4f.c

SST_Vec4d.c:
	@echo GEN $@
	@$(PYFILE_VEC) 4 double > SST_Vec4d.c

SST_Vec4i.c:
	@echo GEN $@
	@$(PYFILE_VEC) 4 int > SST_Vec4i.c

SST_Vec4u.c:
	@echo GEN $@
	@$(PYFILE_VEC) 4 "unsigned int" > SST_Vec4u.c

##################################
# THIS IS THE VECTEST SUITE AREA #
##################################
../ZTestSuite/Test-SST_Vec2f.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 2 float  unittest > $@

../ZTestSuite/Test-SST_Vec2d.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 2 double unittest > $@

../ZTestSuite/Test-SST_Vec2i.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 2 int    unittest > $@

../ZTestSuite/Test-SST_Vec2u.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 2 "unsigned int" unittest > $@

../ZTestSuite/Test-SST_Vec3f.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 3 float  unittest > $@

../ZTestSuite/Test-SST_Vec3d.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 3 double unittest > $@

../ZTestSuite/Test-SST_Vec3i.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 3 int    unittest > $@

../ZTestSuite/Test-SST_Vec3u.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 3 "unsigned int" unittest > $@

../ZTestSuite/Test-SST_Vec4f.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 4 float  unittest > $@

../ZTestSuite/Test-SST_Vec4d.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 4 double unittest > $@

../ZTestSuite/Test-SST_Vec4i.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 4 int    unittest > $@

../ZTestSuite/Test-SST_Vec4u.cpp:
	@echo GEN $@
	@$(PYFILE_VEC) 4 "unsigned int" unittest > $@

###############################
# THIS IS THE TEST SUITE AREA #
###############################
../ZTestSuite/Test-SST_Mat22f.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 2 float  unittest > $@

../ZTestSuite/Test-SST_Mat22d.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 2 double unittest > $@

../ZTestSuite/Test-SST_Mat22i.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 2 int    unittest > $@

../ZTestSuite/Test-SST_Mat22u.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 2 "unsigned int" unittest > $@

../ZTestSuite/Test-SST_Mat33f.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 3 float  unittest > $@

../ZTestSuite/Test-SST_Mat33d.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 3 double unittest > $@

../ZTestSuite/Test-SST_Mat33i.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 3 int    unittest > $@

../ZTestSuite/Test-SST_Mat33u.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 3 "unsigned int" unittest > $@

../ZTestSuite/Test-SST_Mat44f.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 4 float  unittest > $@

../ZTestSuite/Test-SST_Mat44d.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 4 double unittest > $@

../ZTestSuite/Test-SST_Mat44i.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 4 int    unittest > $@

../ZTestSuite/Test-SST_Mat44u.cpp:
	@echo GEN $@
	@$(PYFILE_MAT) 4 "unsigned int" unittest > $@

###############################
# THIS IS THE BENCHMARK AREA #
###############################
SST_Mat22f_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 2 float  benchmark > $@

SST_Mat22d_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 2 double benchmark > $@

SST_Mat22i_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 2 int    benchmark > $@

SST_Mat22u_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 2 "unsigned int" benchmark > $@

SST_Mat33f_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 3 float  benchmark > $@

SST_Mat33d_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 3 double benchmark > $@

SST_Mat33i_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 3 int    benchmark > $@

SST_Mat33u_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 3 "unsigned int" benchmark > $@

SST_Mat44f_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 4 float  benchmark > $@

SST_Mat44d_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 4 double benchmark > $@

SST_Mat44i_benchmark.c :
	@echo GEN $@
	@$(PYFILE_MAT) 4 int    benchmark > $@

SST_Mat44u_benchmark.c : 
	@echo GEN $@
	@$(PYFILE_MAT) 4 "unsigned int" benchmark > $@


# *.c files to *.o files
obj/$(ARCH)/$(TARGET)/%.o: %.c
	@echo CC $@
	@$(CC) $(CFLAGS) -c $*.c -o obj/$(ARCH)/$(TARGET)/$*.o

# *.cpp files to *.o files - specifically used for unit test code check 
#  This should be removed eventually and handled through the ... ZTestSuite?
obj/$(ARCH)/$(TARGET)/%.o: %.cpp
	@echo CXX $@
	@$(CXX) $(CXXFLAGS) -I../Include -I../Lib/Include -c $< -o $@

$(CODs) : $(SRC) 
	$(CC)  $(CODFLAG) $(CFLAGS) -c $< > $@

assemblers: $(CODs)

# CLEAN
clean:
	@-rm -r -f obj $(DIST)/libsst-math*.a test.bin

# CLEAN - Gets rid of dynamically generated code as well
cleanall: clean
	$(RM) $(OBJ) 
	$(RM) $(DYNSRC_MAT) 
	$(RM) $(DYNSRC_VEC) 
	$(RM) $(DYNTEST) 
	$(RM) $(DYNUNITTEST)

all: $(DYNSRC) $(OBJ) $(BINNAME) $(DYNUNITTEST) 

release: $(OBJ) $(BINNAME) 
