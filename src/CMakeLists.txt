# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

add_library(KF5Mbox)
add_library(KF5::Mbox ALIAS KF5Mbox)

target_sources(KF5Mbox PRIVATE
    mboxentry.cpp
    mbox_p.cpp
    mbox.cpp
    mboxentry.h
    mbox.h
    mbox_p.h
    mboxentry_p.h
)

ecm_qt_declare_logging_category(KF5Mbox HEADER kmbox_debug.h IDENTIFIER KMBOX_LOG CATEGORY_NAME org.kde.pim.kmbox
        OLD_CATEGORY_NAMES log_kmbox
        DESCRIPTION "kmbox (pim lib)" EXPORT KMBOX)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5Mbox PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(KF5Mbox BASE_NAME kmbox)

target_include_directories(KF5Mbox INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/KMbox>")
target_include_directories(KF5Mbox PUBLIC "$<BUILD_INTERFACE:${KMbox_SOURCE_DIR}/src;${KMbox_BINARY_DIR}/src>")

target_link_libraries(KF5Mbox
   PUBLIC
    KF5::Mime 
)
if (TARGET Qt6::Core5Compat)
    target_link_libraries(KF5Mbox PRIVATE Qt6::Core5Compat) # QTextCodec
endif()

set_target_properties(KF5Mbox PROPERTIES
    VERSION ${KMBOX_VERSION}
    SOVERSION ${KMBOX_SOVERSION}
    EXPORT_NAME Mbox
)

install(TARGETS KF5Mbox EXPORT KF5MboxTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

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
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KMbox/KMbox/
    COMPONENT Devel
)


install(FILES
  ${KMbox_BINARY_DIR}/src/kmbox_export.h
  ${KMbox_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/KMbox/kmbox
    COMPONENT Devel
)

ecm_qt_install_logging_categories(EXPORT KMBOX FILE kmbox.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
ecm_generate_pri_file(BASE_NAME KMbox LIB_NAME KF5Mbox DEPS "KMime" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/KMbox)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

if (BUILD_QCH)
    ecm_add_qch(
        KF5MBox_QCH
        NAME KMBox
        BASE_NAME KF5MBox
        VERSION ${PIM_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${KMbox_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        #IMAGE_DIRS "${CMAKE_SOURCE_DIR}/docs/pics"
        LINK_QCHS
            Qt5Core_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            KMBOX_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
