# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

add_library(KPim6Mbox)
add_library(KPim6::Mbox ALIAS KPim6Mbox)

target_sources(KPim6Mbox PRIVATE
    mboxentry.cpp
    mbox_p.cpp
    mbox.cpp
    mboxentry.h
    mbox.h
    mbox_p.h
    mboxentry_p.h
)

ecm_qt_declare_logging_category(KPim6Mbox HEADER kmbox_debug.h IDENTIFIER KMBOX_LOG CATEGORY_NAME org.kde.pim.kmbox
        OLD_CATEGORY_NAMES log_kmbox
        DESCRIPTION "kmbox (pim lib)" EXPORT KMBOX)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KPim6Mbox PROPERTIES UNITY_BUILD ON)
endif()

ecm_generate_export_header(KPim6Mbox
    BASE_NAME kmbox
    VERSION ${KMBOX_VERSION}
    DEPRECATED_BASE_VERSION 0
    USE_VERSION_HEADER
)
target_include_directories(KPim6Mbox INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/KPim6/KMbox>")
target_include_directories(KPim6Mbox PUBLIC "$<BUILD_INTERFACE:${KMbox_SOURCE_DIR}/src;${KMbox_BINARY_DIR}/src>")

target_link_libraries(KPim6Mbox
   PUBLIC
    KPim6::Mime 
)

set_target_properties(KPim6Mbox PROPERTIES
    VERSION ${KMBOX_VERSION}
    SOVERSION ${KMBOX_SOVERSION}
    EXPORT_NAME Mbox
)

install(TARGETS KPim6Mbox EXPORT KPim6MboxTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

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
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/KMbox/KMbox/
    COMPONENT Devel
)


install(FILES
  ${KMbox_BINARY_DIR}/src/kmbox_export.h
  ${KMbox_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/KPim6/KMbox/kmbox
    COMPONENT Devel
)

ecm_qt_install_logging_categories(EXPORT KMBOX FILE kmbox.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
ecm_generate_pri_file(BASE_NAME KMbox LIB_NAME KPim6Mbox DEPS "KMime"
    FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR}/KPim6/KMbox)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_QCH)
    ecm_add_qch(
        KPim6Mbox_QCH
        NAME KMbox
        BASE_NAME KPim6Mbox
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${KMbox_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt6Core_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            KMBOX_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
