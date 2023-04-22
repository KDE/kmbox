# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

add_library(KPim${KF_MAJOR_VERSION}Mbox)
add_library(KPim${KF_MAJOR_VERSION}::Mbox ALIAS KPim${KF_MAJOR_VERSION}Mbox)

target_sources(KPim${KF_MAJOR_VERSION}Mbox PRIVATE
    mboxentry.cpp
    mbox_p.cpp
    mbox.cpp
    mboxentry.h
    mbox.h
    mbox_p.h
    mboxentry_p.h
)

ecm_qt_declare_logging_category(KPim${KF_MAJOR_VERSION}Mbox HEADER kmbox_debug.h IDENTIFIER KMBOX_LOG CATEGORY_NAME org.kde.pim.kmbox
        OLD_CATEGORY_NAMES log_kmbox
        DESCRIPTION "kmbox (pim lib)" EXPORT KMBOX)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim${KF_MAJOR_VERSION}Mbox PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(KPim${KF_MAJOR_VERSION}Mbox BASE_NAME kmbox)

target_include_directories(KPim${KF_MAJOR_VERSION}Mbox INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/KMbox>")
target_include_directories(KPim${KF_MAJOR_VERSION}Mbox PUBLIC "$<BUILD_INTERFACE:${KMbox_SOURCE_DIR}/src;${KMbox_BINARY_DIR}/src>")

target_link_libraries(KPim${KF_MAJOR_VERSION}Mbox
   PUBLIC
    KPim${KF_MAJOR_VERSION}::Mime 
)
if (TARGET Qt6::Core5Compat)
    target_link_libraries(KPim${KF_MAJOR_VERSION}Mbox PRIVATE Qt6::Core5Compat) # QTextCodec
endif()

set_target_properties(KPim${KF_MAJOR_VERSION}Mbox PROPERTIES
    VERSION ${KMBOX_VERSION}
    SOVERSION ${KMBOX_SOVERSION}
    EXPORT_NAME Mbox
)

install(TARGETS KPim${KF_MAJOR_VERSION}Mbox EXPORT KPim${KF_MAJOR_VERSION}MboxTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

########### Generate Headers ###############
ecm_generate_headers(KMbox_CamelCase_HEADERS
  HEADER_NAMES
  MBox
  MBoxEntry
  PREFIX KMbox
  REQUIRED_HEADERS KMbox_HEADERS
)

install(FILES
    ${KMbox_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/KMbox/KMbox/
    COMPONENT Devel
)


install(FILES
  ${KMbox_BINARY_DIR}/src/kmbox_export.h
  ${KMbox_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/KMbox/kmbox
    COMPONENT Devel
)

ecm_qt_install_logging_categories(EXPORT KMBOX FILE kmbox.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
ecm_generate_pri_file(BASE_NAME KMbox LIB_NAME KPim${KF_MAJOR_VERSION}Mbox DEPS "KMime"
    FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim${KF_MAJOR_VERSION}/KMbox)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_QCH)
    ecm_add_qch(
        KPim${KF_MAJOR_VERSION}Mbox_QCH
        NAME KMbox
        BASE_NAME KPim${KF_MAJOR_VERSION}Mbox
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${KMbox_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            KMBOX_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
