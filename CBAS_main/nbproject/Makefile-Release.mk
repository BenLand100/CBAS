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
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Loader.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/MinGW-Linux-x86/cbas_main

dist/Release/MinGW-Linux-x86/cbas_main: ${OBJECTFILES}
	${MKDIR} -p dist/Release/MinGW-Linux-x86
	${LINK.cc} Resource.o -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/cbas_main ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Loader.o: nbproject/Makefile-${CND_CONF}.mk Loader.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Loader.o Loader.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/MinGW-Linux-x86/cbas_main

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
