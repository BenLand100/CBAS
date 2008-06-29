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
CC=gcc.exe
CCC=g++.exe
CXX=g++.exe
FC=g77.exe

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/MinGW-Windows

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

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/CBAS.exe

dist/Debug/CBAS.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Debug
	${LINK.cc} Resource.o -o dist/Debug/CBAS -s ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Loader.o: Loader.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O3 -s -o ${OBJECTDIR}/Loader.o Loader.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/CBAS.exe

# Subprojects
.clean-subprojects:
