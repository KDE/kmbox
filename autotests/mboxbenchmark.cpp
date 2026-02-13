/*
  SPDX-FileCopyrightText: 2009 Bertjan Broeksema <broeksema@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mboxbenchmark.h"

#include <QCryptographicHash>

#include <QTemporaryDir>
#include <QTest>

QTEST_MAIN(MBoxBenchmark)

#include "test-entries.h"

using namespace KMBox;

static const char *testDir = "libmbox-unit-test";
static const char *testFile = "test-mbox-file";

QString MBoxBenchmark::fileName()
{
    return mTempDir->path() + QLatin1Char('/') + QLatin1StringView(testFile);
}

void MBoxBenchmark::initTestCase()
{
    mTempDir = new QTemporaryDir(QDir::tempPath() + QLatin1Char('/') + QLatin1StringView(testDir));
    mMail1 = std::make_shared<KMime::Message>();
    mMail1->setContent(KMime::CRLFtoLF(sEntry1));
    mMail1->parse();
}

void MBoxBenchmark::cleanupTestCase()
{
    mTempDir->remove();
    delete mTempDir;
}

void MBoxBenchmark::testNoLockPerformance()
{
    MBox mbox;
    mbox.setLockType(MBox::None);
    mbox.load(fileName());

    for (int i = 0; i < 1000; ++i) {
        mbox.appendMessage(mMail1);
    }

    mbox.save(fileName());

    QBENCHMARK {
        MBox mbox2;
        mbox2.setLockType(MBox::None);
        mbox2.setUnlockTimeout(5000);
        mbox2.load(fileName());
        const auto lst = mbox2.entries();
        for (const MBoxEntry &entry : lst) {
            auto mail = mbox2.readMessage(entry);
        }
    }
}

void MBoxBenchmark::testProcfileLockPerformance()
{
    mMail1 = std::make_shared<KMime::Message>();
    mMail1->setContent(KMime::CRLFtoLF(sEntry1));
    mMail1->parse();

    MBox mbox;
    mbox.setLockType(MBox::ProcmailLockfile);
    mbox.load(fileName());
    for (int i = 0; i < 1000; ++i) {
        mbox.appendMessage(mMail1);
    }

    mbox.save(fileName());

    QBENCHMARK {
        MBox mbox2;
        mbox2.setLockType(MBox::ProcmailLockfile);
        mbox2.load(fileName());
        mbox2.setUnlockTimeout(5000); // Keep the mbox locked for five seconds.

        const auto lst = mbox2.entries();
        for (const MBoxEntry &entry : lst) {
            auto mail = mbox2.readMessage(entry);
        }
    }
}

#include "moc_mboxbenchmark.cpp"
