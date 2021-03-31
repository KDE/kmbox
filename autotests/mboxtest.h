/*
  SPDX-FileCopyrightText: 2009 Bertjan Broeksema <broeksema@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>
#include <QThread>

#include "mbox.h"

class QTemporaryDir;

class MboxTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void testSetLockMethod();
    void testLockBeforeLoad();
    void testProcMailLock();
    void testConcurrentAccess();
    void testAppend();
    void testSaveAndLoad();
    void testBlankLines();
    void testLockTimeout();
    void cleanupTestCase();
    void testEntries();
    void testPurge();
    void testHeaders();
    void testReadOnlyMbox();

private:
    QString fileName();
    QString lockFileName();
    void removeTestFile();

private:
    QTemporaryDir *mTempDir = nullptr;
    KMime::Message::Ptr mMail1;
    KMime::Message::Ptr mMail2;
};

class ThreadFillsMBox : public QThread
{
    Q_OBJECT

public:
    explicit ThreadFillsMBox(const QString &fileName);

protected:
    void run() override;

private:
    KMBox::MBox *mbox = nullptr;
};

