/*
  SPDX-FileCopyrightText: 2009 Bertjan Broeksema <broeksema@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include "mbox.h"

class QTemporaryDir;

class MBoxBenchmark : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testNoLockPerformance();
    void testProcfileLockPerformance();

private:
    QString fileName();

private:
    QTemporaryDir *mTempDir = nullptr;
    std::shared_ptr<KMime::Message> mMail1;
};
