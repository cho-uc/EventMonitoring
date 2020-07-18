# main source/target
SET(SRC_FILES
  MainWindow.cpp
  stdafx.cpp
  SystemInfo.cpp
  SystemInfo.rc
  DiskSpaceInfo.cpp
  TVLogFile.cpp
  TeamViewerUI.cpp
  TopPriority.cpp
  BaseModel.cpp
)

SET(H_FILES 
	MainWindow.h
	IModel.h
	resource.h
	stdafx.h
	SystemInfo.h
	targetver.h
	DiskSpaceInfo.h
	TVLogFile.h
	TeamViewerUI.h
	TopPriority.h
	BaseModel.h
)

#Install options

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../source ${WTL_INCLUDE_DIR})

ADD_EXECUTABLE(SysMonitor WIN32 ${SRC_FILES} ${H_FILES})
SET_TARGET_PROPERTIES(SysMonitor PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
#TARGET_LINK_LIBRARIES(SysMonitor iomessages conserv ${PROTO_LIBRARIES} ${ZLIB_LIBRARIES} ${QTSERVICE_LIBRARIES} ${PCRE16_LIBRARIES}) 

#INSTALL target
INSTALL(TARGETS SysMonitor
		RUNTIME DESTINATION "bin" COMPONENT "Core"
		LIBRARY DESTINATION "lib" COMPONENT "Core"
		ARCHIVE DESTINATION "lib" COMPONENT "Core")