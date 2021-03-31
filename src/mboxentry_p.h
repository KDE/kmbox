/*
    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QSharedData>

namespace KMBox
{
class MBoxEntryPrivate : public QSharedData
{
public:
    MBoxEntryPrivate()
    {
    }

    MBoxEntryPrivate(const MBoxEntryPrivate &other)
        : QSharedData(other)
    {
        mOffset = other.mOffset;
        mMessageSize = other.mMessageSize;
        mSeparatorSize = other.mSeparatorSize;
    }

    quint64 mOffset = 0;
    quint64 mMessageSize = 0;
    quint64 mSeparatorSize = 0;
};
}

