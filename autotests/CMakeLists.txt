# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kde_enable_exceptions()

include(ECMAddTests)
find_package(Qt6Test CONFIG REQUIRED)

########### next target ###############

ecm_add_tests(mboxtest.cpp NAME_PREFIX "mbox-" LINK_LIBRARIES KPim6Mbox Qt::Test)

add_executable(mboxbenchmark mboxbenchmark.cpp)
target_link_libraries(
    mboxbenchmark
    PRIVATE
        KPim6Mbox
        Qt::Test
)
