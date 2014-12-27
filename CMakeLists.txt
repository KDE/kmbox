cmake_minimum_required(VERSION 2.8.12)

project(KMbox)

# ECM setup
find_package(ECM 1.3.0 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings)

set(KF5_VERSION "5.5.0")
set(KMBOXLIB_VERSION "4.79.0")
set(KMIMELIBS_VERSION "4.79.0")

ecm_setup_version(${KMBOXLIB_VERSION} VARIABLE_PREFIX KMBOX
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kmbox_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5MboxConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5CoreAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KDELibs4Support ${KF5_VERSION} CONFIG REQUIRED)

find_package(KF5Mime ${KMIMELIBS_VERSION} CONFIG REQUIRED)
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")

########### Targets ###########
add_subdirectory(src)
add_subdirectory(autotests)

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Mbox")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5MboxConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5MboxConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5MboxConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5MboxConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5MboxTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5MboxTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/kmbox_version.h
   DESTINATION ${KF5_INCLUDE_INSTALL_DIR}
   COMPONENT Devel
)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
