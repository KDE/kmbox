cmake_minimum_required(VERSION 2.8.12)

project(KMbox)

# ECM setup
find_package(ECM 5.17.0 CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)

set(KF5_VERSION "5.17.0")
set(KMBOX_LIB_VERSION "5.1.40")
set(KMIME_LIB_VERSION "5.1.40")

ecm_setup_version(${KMBOX_LIB_VERSION} VARIABLE_PREFIX KMBOX
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kmbox_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5MboxConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KF5Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")

########### Targets ###########
add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Mbox")

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
   DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}
   COMPONENT Devel
)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
