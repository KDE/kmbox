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
    return mTempDir->path() + QLatin1Char('/') + QLatin1String(testFile);
}

void MBoxBenchmark::initTestCase()
{
    mTempDir = new QTemporaryDir(QDir::tempPath() + QLatin1Char('/') + QLatin1String(testDir));
    mMail1 = KMime::Message::Ptr(new KMime::Message);
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
            delete mail;
        }
    }
}

void MBoxBenchmark::testProcfileLockPerformance()
{
    mMail1 = KMime::Message::Ptr(new KMime::Message);
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
            delete mail;
        }
    }
}

void MBoxBenchmark::voidTestMD5Performance()
{
    MBox mbox;
    mbox.setLockType(MBox::None);
    mbox.load(fileName());

    for (int i = 0; i < 1000; ++i) {
        mbox.appendMessage(mMail1);
    }

    mbox.save(fileName());

    QBENCHMARK {
        QFile file(fileName());
        QVERIFY(file.exists());
        QVERIFY(file.open(QIODevice::ReadOnly));

        QCryptographicHash hash(QCryptographicHash::Md5);
        qint64 blockSize = 512 * 1024; // Read blocks of 512K

        while (!file.atEnd()) {
            hash.addData(file.read(blockSize));
        }

        file.close();
    }
}
