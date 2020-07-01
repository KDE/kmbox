/*
    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "mboxentry.h"

#include "mboxentry_p.h"

using namespace KMBox;

MBoxEntry::MBoxEntry()
    : d(new MBoxEntryPrivate)
{
}

MBoxEntry::MBoxEntry(quint64 offset)
    : d(new MBoxEntryPrivate)
{
    d->mOffset = offset;
}

MBoxEntry::MBoxEntry(const MBoxEntry &other)
    : d(other.d)
{
}

MBoxEntry::~MBoxEntry()
{
}

MBoxEntry &MBoxEntry::operator=(const MBoxEntry &other)
{
    if (this != &other) {
        d = other.d;
    }

    return *this;
}

bool MBoxEntry::operator==(const MBoxEntry &other) const
{
    return d->mOffset == other.d->mOffset;
}

bool MBoxEntry::operator!=(const MBoxEntry &other) const
{
    return !(other == *this);
}

bool MBoxEntry::isValid() const
{
    return (d->mOffset != 0) && (d->mMessageSize != 0);
}

quint64 MBoxEntry::messageOffset() const
{
    return d->mOffset;
}

quint64 MBoxEntry::messageSize() const
{
    return d->mMessageSize;
}

quint64 MBoxEntry::separatorSize() const
{
    return d->mSeparatorSize;
}
