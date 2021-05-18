add_library(KF5Mbox)
add_library(KF5::Mbox ALIAS KF5Mbox)

target_sources(KF5Mbox PRIVATE
    mboxentry.cpp
    mbox_p.cpp
    mbox.cpp
)

ecm_qt_declare_logging_category(KF5Mbox HEADER kmbox_debug.h IDENTIFIER KMBOX_LOG CATEGORY_NAME org.kde.pim.kmbox
        OLD_CATEGORY_NAMES log_kmbox
        DESCRIPTION "kmbox (pim lib)" EXPORT KMBOX)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF5Mbox PROPERTIES UNITY_BUILD ON)
endif()

generate_export_header(KF5Mbox BASE_NAME kmbox)

target_include_directories(KF5Mbox INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KMbox>")
target_include_directories(KF5Mbox PUBLIC "$<BUILD_INTERFACE:${KMbox_SOURCE_DIR}/src;${KMbox_BINARY_DIR}/src>")

target_link_libraries(KF5Mbox
   PUBLIC
    KF5::Mime 
)

set_target_properties(KF5Mbox PROPERTIES
    VERSION ${KMBOX_VERSION}
    SOVERSION ${KMBOX_SOVERSION}
    EXPORT_NAME Mbox
)

install(TARGETS KF5Mbox EXPORT KF5MboxTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

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
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KMbox/KMbox/
    COMPONENT Devel
)


install(FILES
  ${KMbox_BINARY_DIR}/src/kmbox_export.h
  ${KMbox_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KMbox/kmbox
    COMPONENT Devel
)

ecm_qt_install_logging_categories(EXPORT KMBOX FILE kmbox.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
ecm_generate_pri_file(BASE_NAME KMbox LIB_NAME KF5Mbox DEPS "KMime" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KMbox)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
