#######################################################
# cmake file for building TpcSDHCALSim package
# @author rete , IPNL
#######################################################

# include directories
INCLUDE_DIRECTORIES( include )

# require proper c++
ADD_DEFINITIONS( "-pedantic -Wunused-value -O2" )
ADD_DEFINITIONS("-Wno-long-long -Wreturn-type")

#IF( OPENMP_FOUND )
#	ADD_DEFINITIONS("-fopenmp")
#ENDIF()

FILE (
	GLOB_RECURSE
	SRC_FILES
	src/*
)

ADD_EXECUTABLE( ${PROJECT_NAME} main/${PROJECT_NAME}.cc ${SRC_FILES} )


INSTALL(
  TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin 
)