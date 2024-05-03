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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=1
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/BloomFilter.o \
	${OBJECTDIR}/ChildInfo.o \
	${OBJECTDIR}/File.o \
	${OBJECTDIR}/HashFunctions.o \
	${OBJECTDIR}/Session.o \
	${OBJECTDIR}/SessionParent.o \
	${OBJECTDIR}/SkipList.o \
	${OBJECTDIR}/TravelRequestList.o \
	${OBJECTDIR}/date.o \
	${OBJECTDIR}/datecmp.o \
	${OBJECTDIR}/datevacc.o \
	${OBJECTDIR}/lista.o \
	${OBJECTDIR}/main_travelmonitor.o \
	${OBJECTDIR}/main_vaccinemonitor.o \
	${OBJECTDIR}/operations.o \
	${OBJECTDIR}/operations_parent.o \
	${OBJECTDIR}/readerwriter.o \
	${OBJECTDIR}/readerwriter_all.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/giorgios_ak_3

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/giorgios_ak_3: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/giorgios_ak_3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/BloomFilter.o: BloomFilter.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/BloomFilter.o BloomFilter.cpp

${OBJECTDIR}/ChildInfo.o: ChildInfo.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ChildInfo.o ChildInfo.cpp

${OBJECTDIR}/File.o: File.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/File.o File.cpp

${OBJECTDIR}/HashFunctions.o: HashFunctions.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/HashFunctions.o HashFunctions.cpp

${OBJECTDIR}/Session.o: Session.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Session.o Session.cpp

${OBJECTDIR}/SessionParent.o: SessionParent.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SessionParent.o SessionParent.cpp

${OBJECTDIR}/SkipList.o: SkipList.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SkipList.o SkipList.cpp

${OBJECTDIR}/TravelRequestList.o: TravelRequestList.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TravelRequestList.o TravelRequestList.cpp

${OBJECTDIR}/date.o: date.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/date.o date.cpp

${OBJECTDIR}/datecmp.o: datecmp.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/datecmp.o datecmp.cpp

${OBJECTDIR}/datevacc.o: datevacc.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/datevacc.o datevacc.cpp

${OBJECTDIR}/lista.o: lista.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lista.o lista.cpp

${OBJECTDIR}/main_travelmonitor.o: main_travelmonitor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_travelmonitor.o main_travelmonitor.cpp

${OBJECTDIR}/main_vaccinemonitor.o: main_vaccinemonitor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_vaccinemonitor.o main_vaccinemonitor.cpp

${OBJECTDIR}/operations.o: operations.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/operations.o operations.cpp

${OBJECTDIR}/operations_parent.o: operations_parent.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/operations_parent.o operations_parent.cpp

${OBJECTDIR}/readerwriter.o: readerwriter.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/readerwriter.o readerwriter.cpp

${OBJECTDIR}/readerwriter_all.o: readerwriter_all.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/readerwriter_all.o readerwriter_all.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
