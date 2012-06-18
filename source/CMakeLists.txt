CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (LevelSet)

FIND_PACKAGE (ITK)
INCLUDE(${USE_ITK_FILE})

SET (CXX_FILES
	Main.cxx
	LevelSet.cxx
	ReadImage.cxx
	WriteImage.cxx
	Segmentation.cxx
	)

SET (H_FILES
	LevelSet.h
	ReadImage.h
	WriteImage.h
	Segmentation.h
	)

ADD_EXECUTABLE(LevelSet ${CXX_FILES} ${H_FILES})

TARGET_LINK_LIBRARIES (LevelSet ${ITK_LIBRARIES})
