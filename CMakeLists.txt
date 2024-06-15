# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "6.1.2")

project(KMbox VERSION ${PIM_VERSION})

# ECM setup
set(KF_MIN_VERSION "6.0.0")
set(QT_REQUIRED_VERSION "6.6.0")
find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(ECMGenerateExportHeader)
include(ECMGenerateHeaders)

include(ECMSetupVersion)
include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
include(ECMFeatureSummary)
include(ECMAddQch)

set(KMBOX_LIB_VERSION ${PIM_VERSION})
set(KMIME_LIB_VERSION "6.1.2")

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")
ecm_setup_version(PROJECT VARIABLE_PREFIX KMBOX
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/kmbox_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim6MboxConfigVersion.cmake"
                        SOVERSION 6
)

########### Find packages ###########
find_package(KPim6Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)

add_definitions(-DQT_NO_CONTEXTLESS_CONNECT)
ecm_set_disabled_deprecation_versions(QT 6.7.0 KF 6.1.0)

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

########### Targets ###########
add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim6Mbox")
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim6Mbox_QCH
        FILE KPim6MBoxQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim6MBoxQchTargets.cmake\")")
endif()
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KPimMboxConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KPim6MboxConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KPim6MboxConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KPim6MboxConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KPim6MboxTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim6MboxTargets.cmake NAMESPACE KPim6::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/src/kmbox_version.h
   DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/KMbox
   COMPONENT Devel
)

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
ecm_feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
