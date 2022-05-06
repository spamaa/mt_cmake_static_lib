cmake_minimum_required(VERSION 3.15)

project(CMakeStaticLib
	DESCRIPTION "A simple cmake static library"
	LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

add_library(CMakeStaticLib src/CMakeStaticLib.cpp include/CMakeStaticLib.h)
add_library(CMakeStaticLib::CMakeStaticLib ALIAS CMakeStaticLib)

if(BUILD_SHARED_LIBS AND WIN32)
	target_compile_definitions(CMakeStaticLib
		PRIVATE "CMAKESTATICLIB_EXPORT=__declspec(dllexport)"
		INTERFACE "CMAKESTATICLIB_EXPORT=__declspec(dllimport)")
endif()

target_compile_features(CMakeStaticLib PUBLIC cxx_std_17)
target_include_directories(CMakeStaticLib
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

configure_package_config_file(cmake/config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake-static-lib-config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake-static-lib
	NO_SET_AND_CHECK_MACRO)
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake-static-lib-config.cmake
	DESTINATION
		${CMAKE_INSTALL_DATADIR}/cmake-static-lib)

install(TARGETS CMakeStaticLib EXPORT cmake-static-lib-targets)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT cmake-static-lib-targets
	NAMESPACE CMakeStaticLib::
	DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake-static-lib)
