cmake_minimum_required(VERSION 3.0.2)
 
PROJECT(milxImageViewer2 C CXX)
 
#find libraries
include(find)
set( UIs milxQtImage2.ui)
# all .h file  
set (HEADER_FILES milxQtImage2.h)  
  
# all .cpp file  
set (SOURCES_FILES milxImageViewer2.cpp milxQtImage2.cpp ${HEADER_FILES})
#--------------------------------------------------------------------------------
# This sets the windows build that will need the special winmain@16 call. Qt provides
#  this for us in the qtmain.lib file. Using this cmake code will ensure we have it
#  linked into our build. Not needed on Unix/OS X/Linux which is why we have the 
#  IF(WIN32) conditional.
IF (WIN32)
    SET (QT_USE_QTMAIN TRUE)
ENDIF (WIN32)

#Add compiler flags
add_definitions (-DMILXQT_DLL -DMILXQT_MAKEDLL)
if (MILXQT_64)
	add_definitions (-DMILXQT_64)
endif (MILXQT_64)

#--------------------------------------------------------------------------------
# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
FIND_PACKAGE(Qt4 REQUIRED QtCore QtGui QtWebkit)



#--------------------------------------------------------------------------------
# QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to
# a CMake script that sets up this directory for building with Qt4
INCLUDE( ${QT_USE_FILE} )

file(GLOB MILXQT_HEADERS ${LIBRARY_INCLUDE_PATH}/Qt/*.h ${SMILI_SOURCE_DIR}/ui/*.h )
file(GLOB MILXQT_SRC_UIS ${SMILI_SOURCE_DIR}/ui/*.ui)
# this moc's the above variable and appends to the cxx sources
QT4_WRAP_CPP(MILXQT_MOCS ${MILXQT_HEADERS})
QT4_WRAP_CPP(MILXQTIMAGE2_MOCS milxQtImage2.h )
# Add Headers into List
INCLUDE_DIRECTORIES(${MILXQT_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
LINK_DIRECTORIES(${MILXQT_INSTALL_BINARY_DIR})
qt4_wrap_ui(UI_Srcs ${UIs} ${MILXQT_SRC_UIS})
ADD_EXECUTABLE(milxImageViewer2 ${SOURCES_FILES} ${MILXQT_MOCS} ${MILXQTIMAGE2_MOCS} ${UI_Srcs})
TARGET_LINK_LIBRARIES(milxImageViewer2 milx-Qt ${QT_LIBRARIES} milx-SMILI ${VTK_QT_LIBRARIES} ${ITK_LIBRARIES} vtk-ext ${VTK_LIBRARIES} ${ITK_REVIEW_LIBRARIES} ${ZLIB_LIBRARIES})