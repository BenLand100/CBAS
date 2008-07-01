#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/GNU-Windows

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Main.o \
	${OBJECTDIR}/adler32.o \
	${OBJECTDIR}/Find.o \
	${OBJECTDIR}/Color.o \
	${OBJECTDIR}/Utils.o \
	${OBJECTDIR}/DTM.o \
	${OBJECTDIR}/Bitmap.o \
	${OBJECTDIR}/trees.o \
	${OBJECTDIR}/Input.o \
	${OBJECTDIR}/deflate.o \
	${OBJECTDIR}/zutil.o \
	${OBJECTDIR}/DebugWnd.o \
	${OBJECTDIR}/gzio.o \
	${OBJECTDIR}/crc32.o \
	${OBJECTDIR}/Plugins.o \
	${OBJECTDIR}/inflate.o \
	${OBJECTDIR}/inftrees.o \
	${OBJECTDIR}/inffast.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Release/GNU-Windows/libCBAS_lib.dll

dist/Release/GNU-Windows/libCBAS_lib.dll: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Windows
	${LINK.cc} -shared -o dist/Release/GNU-Windows/libCBAS_lib.dll -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Main.o: Main.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/Main.o Main.cc

${OBJECTDIR}/adler32.o: adler32.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/adler32.o adler32.c

${OBJECTDIR}/Find.o: Find.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/Find.o Find.cc

${OBJECTDIR}/Color.o: Color.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/Color.o Color.cc

${OBJECTDIR}/Utils.o: Utils.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/Utils.o Utils.cc

${OBJECTDIR}/DTM.o: DTM.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/DTM.o DTM.cc

${OBJECTDIR}/Bitmap.o: Bitmap.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/Bitmap.o Bitmap.cc

${OBJECTDIR}/trees.o: trees.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/trees.o trees.c

${OBJECTDIR}/Input.o: Input.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/Input.o Input.cpp

${OBJECTDIR}/deflate.o: deflate.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/deflate.o deflate.c

${OBJECTDIR}/zutil.o: zutil.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/zutil.o zutil.c

${OBJECTDIR}/DebugWnd.o: DebugWnd.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/DebugWnd.o DebugWnd.cc

${OBJECTDIR}/gzio.o: gzio.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/gzio.o gzio.c

${OBJECTDIR}/crc32.o: crc32.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/crc32.o crc32.c

${OBJECTDIR}/Plugins.o: Plugins.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -fPIC  -o ${OBJECTDIR}/Plugins.o Plugins.cc

${OBJECTDIR}/inflate.o: inflate.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/inflate.o inflate.c

${OBJECTDIR}/inftrees.o: inftrees.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/inftrees.o inftrees.c

${OBJECTDIR}/inffast.o: inffast.c 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.c) -O2 -fPIC  -o ${OBJECTDIR}/inffast.o inffast.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Windows/libCBAS_lib.dll

# Subprojects
.clean-subprojects: