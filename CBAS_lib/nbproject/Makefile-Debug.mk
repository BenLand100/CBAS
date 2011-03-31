#
# Generated Makefile - do not edit!
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
CC=i586-mingw32msvc-gcc
CCC=i586-mingw32msvc-g++
CXX=i586-mingw32msvc-g++
FC=
AS=i586-mingw32msvc-as

# Macros
CND_PLATFORM=MinGW-Linux-x86
CND_CONF=Debug
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

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
CFLAGS=-DBUILD_DLL

# CC Compiler Flags
CCFLAGS=-DBUILD_DLL
CXXFLAGS=-DBUILD_DLL

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lgdi32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/libcbas.dll

dist/Debug/libcbas.dll: ${OBJECTFILES}
	${MKDIR} -p dist/Debug
	${LINK.cc} -Wl,--add-stdcall-alias -shared -o dist/Debug/libcbas.dll -s -fPIC ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Main.o: nbproject/Makefile-${CND_CONF}.mk Main.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Main.o Main.cc

${OBJECTDIR}/adler32.o: nbproject/Makefile-${CND_CONF}.mk adler32.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/adler32.o adler32.c

${OBJECTDIR}/Find.o: nbproject/Makefile-${CND_CONF}.mk Find.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Find.o Find.cc

${OBJECTDIR}/Color.o: nbproject/Makefile-${CND_CONF}.mk Color.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Color.o Color.cc

${OBJECTDIR}/Utils.o: nbproject/Makefile-${CND_CONF}.mk Utils.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Utils.o Utils.cc

${OBJECTDIR}/DTM.o: nbproject/Makefile-${CND_CONF}.mk DTM.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/DTM.o DTM.cc

${OBJECTDIR}/Bitmap.o: nbproject/Makefile-${CND_CONF}.mk Bitmap.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Bitmap.o Bitmap.cc

${OBJECTDIR}/trees.o: nbproject/Makefile-${CND_CONF}.mk trees.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/trees.o trees.c

${OBJECTDIR}/Input.o: nbproject/Makefile-${CND_CONF}.mk Input.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Input.o Input.cpp

${OBJECTDIR}/deflate.o: nbproject/Makefile-${CND_CONF}.mk deflate.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/deflate.o deflate.c

${OBJECTDIR}/zutil.o: nbproject/Makefile-${CND_CONF}.mk zutil.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/zutil.o zutil.c

${OBJECTDIR}/DebugWnd.o: nbproject/Makefile-${CND_CONF}.mk DebugWnd.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/DebugWnd.o DebugWnd.cc

${OBJECTDIR}/gzio.o: nbproject/Makefile-${CND_CONF}.mk gzio.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/gzio.o gzio.c

${OBJECTDIR}/crc32.o: nbproject/Makefile-${CND_CONF}.mk crc32.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/crc32.o crc32.c

${OBJECTDIR}/Plugins.o: nbproject/Makefile-${CND_CONF}.mk Plugins.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/Plugins.o Plugins.cc

${OBJECTDIR}/inflate.o: nbproject/Makefile-${CND_CONF}.mk inflate.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/inflate.o inflate.c

${OBJECTDIR}/inftrees.o: nbproject/Makefile-${CND_CONF}.mk inftrees.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/inftrees.o inftrees.c

${OBJECTDIR}/inffast.o: nbproject/Makefile-${CND_CONF}.mk inffast.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -O3 -s -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/inffast.o inffast.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/libcbas.dll

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
