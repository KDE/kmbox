# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(PIM_VERSION "5.23.2")

project(KMbox VERSION ${PIM_VERSION})

# ECM setup
set(KF_MIN_VERSION "5.103.0")
find_package(ECM ${KF_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(ECMSetupVersion)
include(FeatureSummary)
include(KDEGitCommitHooks)
include(KDEClangFormat)
file(GLOB_RECURSE ALL_CLANG_FORMAT_SOURCE_FILES *.cpp *.h *.c)
kde_clang_format(${ALL_CLANG_FORMAT_SOURCE_FILES})

include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
include(ECMAddQch)

if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_MIN_VERSION "6.4.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
else()
    set(KF_MAJOR_VERSION "5")
endif()

set(KMBOX_LIB_VERSION ${PIM_VERSION})
set(KMIME_LIB_VERSION "5.23.2")
option(BUILD_WITH_COMPAT_LIBS "Generate compat cmake file (Set at false will allow to co-install lib)" ON)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")
ecm_setup_version(PROJECT VARIABLE_PREFIX KMBOX
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kmbox_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MboxConfigVersion.cmake"
                        SOVERSION 5
)

########### Find packages ###########
find_package(KPim${KF_MAJOR_VERSION}Mime ${KMIME_LIB_VERSION} CONFIG REQUIRED)
if (QT_MAJOR_VERSION STREQUAL "6")
    find_package(Qt6Core5Compat)
endif()

ecm_set_disabled_deprecation_versions(QT 6.4  KF 5.104.0)

option(USE_UNITY_CMAKE_SUPPORT "Use UNITY cmake support (speedup compile time)" OFF)

set(COMPILE_WITH_UNITY_CMAKE_SUPPORT OFF)
if (USE_UNITY_CMAKE_SUPPORT)
    set(COMPILE_WITH_UNITY_CMAKE_SUPPORT ON)
endif()

if (BUILD_WITH_COMPAT_LIBS)
if (QT_MAJOR_VERSION STREQUAL "5")
##
# TODO: Backwards compatiblity. Remove in next major version
##
set(CMAKECONFIG_INSTALL_DIR_KF5 "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Mbox")
set(KMBOX_KF5_COMPAT TRUE)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KPimMboxConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MboxConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR_KF5}
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5MboxConfig.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    COMPONENT Devel
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MboxConfigVersion.cmake"
    RENAME "KF5MboxConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    COMPONENT Devel
)
install(EXPORT KPim${KF_MAJOR_VERSION}MboxTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR_KF5}"
    FILE KPim${KF_MAJOR_VERSION}MboxTargets.cmake
    NAMESPACE KF5::
)
endif()
endif()

########### Targets ###########
add_subdirectory(src)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KPim${KF_MAJOR_VERSION}Mbox")
set(KMBOX_KF5_COMPAT FALSE)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KPimMboxConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MboxConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MboxConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KPim${KF_MAJOR_VERSION}MboxConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KPim${KF_MAJOR_VERSION}MboxTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KPim${KF_MAJOR_VERSION}MboxTargets.cmake NAMESPACE KPim${KF_MAJOR_VERSION}::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/kmbox_version.h
   DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/KMbox
   COMPONENT Devel
)

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KPim${KF_MAJOR_VERSION}Mbox_QCH
        FILE KPim${KF_MAJOR_VERSION}MBoxQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KPim${KF_MAJOR_VERSION}MBoxQchTargets.cmake\")")
endif()

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
