set(kmbox_SRCS
    mboxentry.cpp
    mbox_p.cpp
    mbox.cpp
)

add_library(KF5Mbox ${kmbox_SRCS})

generate_export_header(KF5Mbox BASE_NAME kmbox)

add_library(KF5::Mbox ALIAS KF5Mbox)

target_include_directories(KF5Mbox INTERFACE "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}/kmbox>")
target_include_directories(KF5Mbox PUBLIC "$<BUILD_INTERFACE:${KMbox_SOURCE_DIR}/src;${KMbox_BINARY_DIR}/src>")

target_link_libraries(KF5Mbox
    KF5::CoreAddons
    KF5::KMime
)

set_target_properties(KF5Mbox PROPERTIES
    VERSION ${KMBOX_VERSION_STRING}
    SOVERSION ${KMBOX_SOVERSION}
    EXPORT_NAME Mbox
)

install(TARGETS KF5Mbox EXPORT KF5MboxTargets ${INSTALL_TARGETS_DEFAULT_ARGS})

########### Generate Headers ###############
ecm_generate_headers(KMbox_CamelCase_HEADERS
  HEADER_NAMES
  MBox
  MBoxEntry

  REQUIRED_HEADERS KMbox_HEADERS
  PREFIX KMbox
)

install(FILES
    ${KMbox_CamelCase_HEADERS}
    DESTINATION ${INCLUDE_INSTALL_DIR}/KMbox
    COMPONENT Devel
)

install(FILES
  ${KMbox_BINARY_DIR}/src/kmbox_export.h
  ${KMbox_HEADERS}
  DESTINATION ${INCLUDE_INSTALL_DIR}/kmbox
  COMPONENT Devel
)

ecm_generate_pri_file(BASE_NAME Mbox LIB_NAME KF5Mbox DEPS "CoreAddons KMime" FILENAME_VAR PRI_FILENAME)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})