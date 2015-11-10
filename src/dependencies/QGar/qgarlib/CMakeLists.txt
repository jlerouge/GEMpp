 
#######################################################################
# Library QgarLib, graphics analysis and recognition                  #
# Copyright (C) 2002  Qgar Project, LORIA                             #
#                                                                     #
# This library is free software; you can redistribute it and/or       #
# modify it under the terms of the GNU Lesser General Public          #
# License version 2.1, as published by the Free Software Foundation.  #
#                                                                     #
# This library is distributed in the hope that it will be useful,     #
# but WITHOUT ANY WARRANTY; without even the implied warranty of      #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                #
# See the GNU Lesser General Public License for more details.         #
#                                                                     #
# The GNU Lesser General Public License is included in the file       #
# LICENSE.LGPL, in the root directory of the Qgar packaging. See      #
# http://www.gnu.org/licenses/lgpl.html for the terms of the licence. #
# To receive a paper copy, write to the Free Software Foundation,     #
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA.       #
#                                                                     #
# Contact Project Qgar for any information:                           #
#   LORIA - équipe Qgar                                               #
#   B.P. 239, 54506 Vandoeuvre-lès-Nancy Cedex, France                #
#   email: qgar-contact@loria.fr                                      #
#   http://www.qgar.org/                                              #
#######################################################################



# @file CMakiLists.txt
# 
# @brief Configuration file of qgarlib directory: /Qgar/qgarlib
#
# @author <a href="mailto:qgar-develop@loria.fr?subject=Qgar fwd Vitor Vasconcelos">Vitor Vasconcelos</a>
# @date   June 6, 2007  17:22
# @since  Qgar 3.0
#


# Information

# Since CMake doesn't support "convenience" libraries as 
# libqgxml was used before, it's sources are included to 
# qgarlib base library if Qt package is found.


# Set a project to contain de library file to be generated
PROJECT(qgarlib)

# Inclusion of all modules needed by this project
INCLUDE (CheckIncludeFiles)
INCLUDE (CheckLibraryExists)

# The direct way of include Qt and set it's variables
FIND_PACKAGE(Qt4)

ADD_DEFINITIONS(-DQT_STATIC)

# Turno QtXml ON
SET(QT_USE_QTXML TRUE)

# Enable tests from this directory and below. The test command ctest
# expects to find the tests in the build directory root. Therefore, this 
# command should be in the source directory root.
ENABLE_TESTING()

# VARIABLES SECTION
# -------------------------------------------------------------------------
# Brief description of all variables used in this script
#
# ${LIBSOURCE}: List of source files (no .h files are explicitaly include) of qgar library.
# ${PROJECT_SOURCE_ROOT}: Directory one level above qgarlib.
# ${PROJECT_SOURCE_DIR}: Directory of qgarlib, automaticaly set by CMake configuration.
# ${CMAKE_SYSTEM_NAME}: CMake variable that contais the name of Operational System.

# All variables are in uppercase and there are no flag 
# to differentiate CMake variables and script created variables

# The command below stores all source files names to a variable
# ${LIBSOURCE} to be used later on

  SET(LIBSOURCE 
	      AbstractFile.cpp			AbstractGradientImage.cpp
	      AbstractGraphicsFile.cpp		AbstractMultiImage.cpp 
	      AbstractPbmPlusFile.cpp	        
	      AbstractQgarError.cpp
	      assert.cpp				BoundingBox.cpp
	      CannyGradientImage.cpp		CleanedBinaryImage.cpp
	      CloseBinaryImage.cpp		CloseImage.cpp
	      Component.cpp			ConnectedComponents.cpp
	      ConnectedComponentsImpl.cpp		ContrastEnhancedImage.cpp
	      DericheGradientImage.cpp		DilatedBinaryImage.cpp
	      DilatedImage.cpp			Dist34BlackCCImage.cpp
	      Dist34Image.cpp			Dist8cBlackCCImage.cpp
	      DxfFile.cpp				ErodedBinaryImage.cpp
	      ErodedImage.cpp			File.cpp
	      FreemanChain.cpp			FreemanCode.cpp
	      GeodesicRecBinaryImage.cpp		GeodesicRecEroBinaryImage.cpp
	      GeodesicRecEroImage.cpp		GeodesicRecImage.cpp
	      GradientLocalMaxImage.cpp		GradientModuleImage.cpp
	      Histogram.cpp			HysteresisBinaryImage.cpp
	      image.cpp				ISerializable.cpp
	      IsotropicDilatedBinaryImage.cpp	KanungoBinaryImage.cpp
	      LabeledSkeletonImage.cpp		LaplacianOfGaussianImage.cpp
	      LinDilatedBinaryImage.cpp		LinDilatedImage.cpp
	      LinErodedBinaryImage.cpp		LinErodedImage.cpp
	      LinkedChainList.cpp			Maer.cpp
	      MapleFile.cpp			Mask1dGauss.cpp
	      Mask1dGaussD1.cpp			Mask1dGaussD2.cpp
	      math.cpp				NiblackBinaryImage.cpp
	      OpenBinaryImage.cpp			OpenImage.cpp
	      PbmFile.cpp				PgmFile.cpp
	      PruneSmallCCBinaryImage.cpp		QgarApp.cpp
	      QgarAppDescr.cpp			QgarAppParamDescr.cpp
	      QgarArgs.cpp			QgarErrorAlgorithm.cpp
	      QgarErrorDeveloper.cpp		
	      QgarErrorDomain.cpp
	      QgarErrorInvalidArg.cpp		QgarErrorIO.cpp
	      QgarErrorUser.cpp
	      RegionalMaxBinaryImage.cpp
	      RegionalMaxImage.cpp		RegionalMinBinaryImage.cpp
	      RegionalMinImage.cpp		RWArcVector.cpp
	      RWSegmentVector.cpp			StandardDeviationImage.cpp
	      TgifFile.cpp			ThresBinaryImage.cpp
	      TTBinaryImage.cpp			UltimateErodedBinaryImage.cpp
	      WDSegmentList.cpp
	)

# The command below stores all header files names to a variable
# ${LIBSOURCE_H} to be used later on

  SET ( LIBSOURCE_H
        VecFile.h	image.h		GeodesicRecEroBinaryImage.h
	OLD.array.h	QgarApp.h	QgarAppParamDescr.h
	ThresBinaryImage.h		_QGAR_AbstractGenPrimitive.h
	RWArcVector.h			stl.h
	CleanedBinaryImage.h		AbstractFile.h
	LinkedChainList.h		_QGAR_translation.h
	ConnectedComponents.h		FreemanCode.h
	Mask1dGaussD2.h			GenImage.h
	LinErodedBinaryImage.h		BoundingBox.h
	GenPointChain.h			_QGAR_GenPolygon.h
	GenEdge.h			Dist8cBlackCCImage.h
	ErodedImage.h			_QGAR_GenSegment.h
	StandardDeviationImage.h	LaplacianOfGaussianImage.h
	CloseImage.h			OpenBinaryImage.h
	_QGAR_AbstractGenQgarPrimitive.h	qgar.h
	QgarErrorUser.h			OpenImage.h
	GenKMeans.h			_QGAR_GenArc.h
	AbstractGenPointChain.h		array.h
	GeodesicRecEroImage.h		math.h
	RWSegmentVector.h		PruneSmallCCBinaryImage.h
	assert.h			IsotropicDilatedBinaryImage.h
	GenMask2d.h			NiblackBinaryImage.h
	LinDilatedBinaryImage.h		Mask1dGauss.h
	_QGAR_GenQgarArc.h		AbstractQgarError.h
	TgifFile.h			WDSegmentList.h
	QgarErrorDomain.h		RegionalMaxImage.h
	HysteresisBinaryImage.h		ErodedBinaryImage.h
	QgarAppDescr.h			OLD.assert.h	
	GeodesicRecImage.h		FreemanChain.h
	GeodesicRecBinaryImage.h	ContrastEnhancedImage.h
	primitives.h			MapleFile.h
	DesShapeContext.h		Component.h
	_QGAR_point.h			QgarErrorInvalidArg.h
	_QGAR_GenQgarPolygon.h		Mask1dGaussD1.h
	QgarErrorAlgorithm.h		LinDilatedImage.h
	DilatedBinaryImage.h		PbmFile.h
	ISerializable.h			UltimateErodedBinaryImage.h
	GenUGraph.h			_QGAR_GenQgarSegment.h
	GradientLocalMaxImage.h		DxfFile.h
	AbstractGraphicsFile.h		GenTree.h
	CannyGradientImage.h		GenConvolImage.h
	LabeledSkeletonImage.h		GradientModuleImage.h
	AbstractPbmPlusFile.h		RegionalMinImage.h
	KanungoBinaryImage.h		RegionalMinBinaryImage.h
	CloseBinaryImage.h		Dist34Image.h
	GenMask1d.h			_QGAR_segment.h
	RegionalMaxBinaryImage.h	GenNode.h
	File.h				AbstractMultiImage.h	
	GenConvexHull.h			PgmFile.h
	Maer.h				AbstractGradientImage.h
	ConnectedComponentsImpl.h	QgarErrorIO.h
	_QGAR_GenPoint.h		Histogram.h
	_QGAR_GenPolyline.h		TTBinaryImage.h
	_QGAR_angle.h			_QGAR_distance.h
	_QGAR_primitiveTypes.h		QgarArgs.h
	LinErodedImage.h		DilatedImage.h
	_QGAR_GenQgarPolyline.h		QgarErrorDeveloper.h
	Dist34BlackCCImage.h		DericheGradientImage.h )

# The command below stores all header files names to a variable
# ${LIBSOURCE_TCC} to be used later on

SET ( LIBSOURCE_TCC
    _QGAR_angle.tcc	_QGAR_distance.tcc	_QGAR_GenQgarPolygon.tcc
    GenImage.tcc	GenTree.tcc		GenConvolImage.tcc
    GenKMeans.tcc	_QGAR_GenArc.tcc	GenConvexHull.tcc
    _QGAR_GenQgarPolyline.tcc			GenPointChain.tcc
    _QGAR_GenPolygon.tcc			GenEdge.tcc
    GenMask1d.tcc				_QGAR_AbstractGenPrimitive.tcc
    _QGAR_GenPolyline.tcc			_QGAR_translation.tcc
    GenUGraph.tcc				_QGAR_GenQgarSegment.tcc
    AbstractGenPointChain.tcc			_QGAR_AbstractGenQgarPrimitive.tcc
    _QGAR_segment.tcc				GenNode.tcc
    _QGAR_GenPoint.tcc				_QGAR_point.tcc
    GenMask2d.tcc				_QGAR_GenQgarArc.tcc
    _QGAR_GenSegment.tcc )

# The command below stores all source files names to a variable
# ${LIBSOURCE_XML} to be used only if Qt is present

  SET(LIBSOURCE_XML 
      qtimpl/QIODeviceAdaptor.cpp		
      qtimpl/QtLocatorAdaptor.cpp
      qtimpl/QtQgarDTDHandlerAdaptor.cpp	
      qtimpl/QtQgarErrorHandlerAdaptor.cpp
      qtimpl/XMLReaderFactory.cpp		
      qtimpl/QtAttributesAdaptor.cpp
      qtimpl/QtQgarEntityResolverAdaptor.cpp  
      qtimpl/QtXMLReaderAdaptor.cpp
      qtimpl/QtQgarContentHandlerAdaptor.cpp
      )

# Define the include directories:
#
# All library files includes a directory one level above, like #include <qgarlib/FILE>. So, we MUST
# include this directory.
# 
# This is done by using the PROJECT_SOURCE_DIR variable, that contais the project directory,
# removing the ggarlib directory at the end using with the STRING command.
# Then, the new string is included by the INCLUDE_DIRECTORIES command

STRING (REGEX REPLACE "/qgarlib" "" PROJECT_SOURCE_ROOT ${PROJECT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_ROOT})

#IF(WIN32)
#    STRING (REGEX REPLACE "include" "mkspecs/default" QT_MKSPECS ${QT_INCLUDE_DIR})
#    INCLUDE_DIRECTORIES(${QT_MKSPECS})
#ENDIF(WIN32)

IF(QT4_FOUND)

	# Configuring QT to build the Qgar XML extension
	SET(QT_USE_QTXML true)

	INCLUDE_DIRECTORIES ( ${QT_INCLUDE_DIR} )	
	INCLUDE_DIRECTORIES ( ${QT_QTCORE_INCLUDE_DIR} )	
	INCLUDE_DIRECTORIES ( ${QT_QTXML_INCLUDE_DIR} )	

	LINK_DIRECTORIES ( ${QT_LIBRARY_DIR} )
	
	# Just include the QT files to the source
	SET(LIBTMP ${LIBSOURCE} ${LIBSOURCE_XML})
	SET(LIBSOURCE ${LIBTMP})

ENDIF(QT4_FOUND)

# The line below defines what the project is doing.
# We're generating the qgar library (libqgar) as a static library based on all source files
# The ADD_LIBRARY command allows other types of libraries STATIC, SHARED or MODULE.
#
# The lib prefix is automatically preppended to qgar name.
#
# See CMake documentation to know more about it.

IF(WIN32)
  SET(LIBQGAR_NAME "qgarwin")
ELSE(WIN32)
  SET(LIBQGAR_NAME "qgar")
ENDIF(WIN32)

# Chose the type of library to be built

SET(LIB_TYPE "STATIC")

MESSAGE (STATUS "Library type ---> " ${LIB_TYPE})
ADD_LIBRARY (${LIBQGAR_NAME} ${LIB_TYPE} ${LIBSOURCE})

IF(QT4_FOUND)

	TARGET_LINK_LIBRARIES (${LIBQGAR_NAME} ${QT_QTXML_LIBRARY})	

ENDIF(QT4_FOUND)

# -----------------------------------------------------------------
# 
# INSTALL
#
# -----------------------------------------------------------------

#INSTALL(TARGETS ${LIBQGAR_NAME} ARCHIVE 
#		DESTINATION ${CMAKE_INSTALL_PREFIX}/${QGAR_NAME_VERSION}/qgarlib)

# Qgar is always built as a static library. So, no symbolic links are created
# but the library is generated in the source tree and also copied at INSTALL_PREFIX/lib
INSTALL(TARGETS ${LIBQGAR_NAME} ARCHIVE 
		DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

INSTALL(FILES ${LIBSOURCE_H} ${LIBSOURCE_TCC} 
	      DESTINATION ${CMAKE_INSTALL_PREFIX}/include/qgarlib)

# The next install puts all source files in the directory qgarlib
# it's necessary to allow the automatic package generation to 
# create the packages with que source code
#INSTALL(FILES ${LIBSOURCE} ${LIBSOURCE_H} ${LIBSOURCE_TCC}
#	      DESTINATION ${CMAKE_INSTALL_PREFIX}/${QGAR_NAME_VERSION}/qgarlib)


ADD_SUBDIRECTORY(testsuite)
