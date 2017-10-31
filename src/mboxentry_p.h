/*
    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef KMBOX_MBOXENTRY_P_H
#define KMBOX_MBOXENTRY_P_H

#include <QSharedData>

namespace KMBox {
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

#endif // KMBOX_MBOXENTRY_P_H
