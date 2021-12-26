# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kde_enable_exceptions()

include(ECMAddTests)
find_package(Qt${QT_MAJOR_VERSION}Test CONFIG REQUIRED)

########### next target ###############

ecm_add_tests(mboxtest.cpp mboxbenchmark.cpp NAME_PREFIX "mbox-" LINK_LIBRARIES KF5Mbox Qt${QT_MAJOR_VERSION}::Test)
