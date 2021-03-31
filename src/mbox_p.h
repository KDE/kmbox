/*
  SPDX-FileCopyrightText: 2009 Bertjan Broeksema <broeksema@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "mbox.h"

#include <QFile>
#include <QObject>
#include <QTimer>

namespace KMBox
{
class MBoxPrivate : public QObject
{
    Q_OBJECT

public:
    MBoxPrivate(MBox *mbox);

    ~MBoxPrivate() override;

    void close();

    void initLoad(const QString &fileName);

    Q_REQUIRED_RESULT bool open();

    Q_REQUIRED_RESULT bool startTimerIfNeeded();

    Q_REQUIRED_RESULT bool isMBoxSeparator(const QByteArray &line) const;

public Q_SLOTS:
    void unlockMBox();

public:
    QByteArray mAppendedEntries;
    MBoxEntry::List mEntries;
    quint64 mInitialMboxFileSize = 0;
    QString mLockFileName;
    MBox *const mMBox;
    QFile mMboxFile;
    QTimer mUnlockTimer;
    QRegExp mSeparatorMatcher;
    MBox::LockType mLockType;
    bool mFileLocked = false;
    bool mReadOnly = false;

public: /// Static helper methods
    static QByteArray escapeFrom(const QByteArray &msg);

    /**
     * Generates a mbox message separator line for given message.
     */
    static QByteArray mboxMessageSeparator(const QByteArray &msg);

    /**
     * Unescapes the raw message read from the file.
     */
    static void unescapeFrom(char *msg, size_t size);
};
}

