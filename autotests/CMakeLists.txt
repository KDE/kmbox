# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

kde_enable_exceptions()

include(ECMAddTests)
find_package(Qt6Test CONFIG REQUIRED)

########### next target ###############

ecm_add_tests(mboxtest.cpp mboxbenchmark.cpp NAME_PREFIX "mbox-" LINK_LIBRARIES KPim6Mbox Qt::Test)
