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
	${OBJECTDIR}/Loader.o

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
.build-conf: ${BUILD_SUBPROJECTS} dist/Release/GNU-Windows/cbas_main.exe

dist/Release/GNU-Windows/cbas_main.exe: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Windows
	${LINK.cc} -o dist/Release/GNU-Windows/cbas_main ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/Loader.o: Loader.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/Loader.o Loader.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Windows/cbas_main.exe

# Subprojects
.clean-subprojects:
