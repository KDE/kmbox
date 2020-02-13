set(kmbox_SRCS
    mboxentry.cpp
    mbox_p.cpp
    mbox.cpp
)

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(kmbox_SRCS HEADER kmbox_debug.h IDENTIFIER KMBOX_LOG CATEGORY_NAME org.kde.pim.kmbox)
else()
    ecm_qt_declare_logging_category(kmbox_SRCS HEADER kmbox_debug.h IDENTIFIER KMBOX_LOG CATEGORY_NAME org.kde.pim.kmbox
        OLD_CATEGORY_NAMES log_kmbox
        DESCRIPTION "kmbox (pim lib)" EXPORT KMBOX)
endif()



add_library(KF5Mbox ${kmbox_SRCS})

generate_export_header(KF5Mbox BASE_NAME kmbox)

add_library(KF5::Mbox ALIAS KF5Mbox)

target_include_directories(KF5Mbox INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KMbox>")
target_include_directories(KF5Mbox PUBLIC "$<BUILD_INTERFACE:${KMbox_SOURCE_DIR}/src;${KMbox_BINARY_DIR}/src>")

target_link_libraries(KF5Mbox
   PUBLIC
    KF5::Mime 
)

set_target_properties(KF5Mbox PROPERTIES
    VERSION ${KMBOX_VERSION_STRING}
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

if (NOT ECM_VERSION VERSION_LESS "5.68.0")
   ecm_qt_install_logging_categories(EXPORT KMBOX FILE kmbox.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
endif()
ecm_generate_pri_file(BASE_NAME Mbox LIB_NAME KF5Mbox DEPS "Mime" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KMbox)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
