# Find WTL (by Michael Braitmaier based on Blasius Czink)
#
# This module defines
#  WTL_INCLUDE_DIR    - WTL include path
#  WTL_FOUND          - true if WTL was found

IF (WTL_LIBRARIES)
  SET(WTL_FIND_QUIETLY TRUE)
ENDIF (WTL_LIBRARIES)

FIND_PATH (WTL_INCLUDE_DIR atlwinx.h 
  PATHS
  $ENV{WTL_HOME}/src/
  $ENV{EXTERNLIBS}/WTL/src/
  $ENV{EXTERNLIBS}/WTL/include
  ${CMAKE_SOURCE_DIR}/../dependencies/WTL/include
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local/include
  /usr/include
  /sw/include        # Fink
  /opt/local/include # DarwinPorts
  /opt/csw/include   # Blastwave
  /opt/include
  DOC "WTL - Headers"
)

IF(WTL_INCLUDE_DIR)
   SET(WTL_FOUND TRUE)
ELSE(WTL_INCLUDE_DIR)
   SET(WTL_FOUND FALSE)
   MESSAGE(STATUS "WTL Include-directory or libraries not found!")
ENDIF (WTL_INCLUDE_DIR)

IF (WTL_FOUND)
   IF (NOT WTL_FIND_QUIETLY)
      MESSAGE(STATUS "Found WTL : ${WTL_LIBRARIES}\n")
   ENDIF (NOT WTL_FIND_QUIETLY)
ELSE (WTL_FOUND)
   IF (WTL_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could NOT find WTL!")
   ENDIF (WTL_FIND_REQUIRED)
ENDIF (WTL_FOUND)
