cmake_minimum_required(VERSION 3.24.0)
project(ZeldaOTRizer VERSION 0.2)
add_library(ZeldaOTRizer Sequence.cpp)
add_library(ZeldaOTRizer::ZeldaOTRizer ALIAS ZeldaOTRizer)
option(BUILD_SHARED_LIBS "Build shared library" OFF)
include(GenerateExportHeader)
generate_export_header(ZeldaOTRizer
    EXPORT_MACRO_NAME ZELDA_OTRIZER_API
    EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/include/ZeldaOTRizer/core/common.h
)
target_compile_features(ZeldaOTRizer PUBLIC cxx_std_20)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(ZeldaOTRizer PRIVATE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
    "$<${msvc_like_cxx}:$<BUILD_INTERFACE:/Od;/Wall;/Zi;>>"
)
target_include_directories(ZeldaOTRizer
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
find_package(OTRizer)
target_link_libraries(ZeldaOTRizer OTRizer::OTRizer)

set_target_properties(ZeldaOTRizer PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

include (GNUInstallDirs)

install(TARGETS ZeldaOTRizer
    EXPORT ZeldaOTRizerTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ZeldaOTRizer
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT ZeldaOTRizerTargets
    FILE ZeldaOTRizerTargets.cmake
    NAMESPACE ZeldaOTRizer::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZeldaOTRizer
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ZeldaOTRizerConfig.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/ZeldaOTRizerConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZeldaOTRizer
)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/ZeldaOTRizerConfigVersion.cmake
    VERSION ${ZELDA_OTRIZER_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/cmake/ZeldaOTRizerConfig.cmake
        ${CMAKE_BINARY_DIR}/cmake/ZeldaOTRizerConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZeldaOTRizer
)

export(EXPORT ZeldaOTRizerTargets
    FILE ${CMAKE_BINARY_DIR}/cmake/ZeldaOTRizerTargets.cmake
    NAMESPACE ZeldaOTRizer::
)
