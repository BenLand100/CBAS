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
	${OBJECTDIR}/Loader.o

# C Compiler Flags
CFLAGS=-mwindows

# CC Compiler Flags
CCFLAGS=-mwindows
CXXFLAGS=-mwindows

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/CBAS.exe

dist/Debug/CBAS.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug
	${LINK.cc} Resource.o -o dist/Debug/CBAS.exe -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Loader.o: nbproject/Makefile-${CND_CONF}.mk Loader.cc 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Loader.o Loader.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/CBAS.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
