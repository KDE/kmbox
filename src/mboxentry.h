/*
    SPDX-FileCopyrightText: 2010 Tobias Koenig <tokoe@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kmbox_export.h"

#include <QList>
#include <QPair>
#include <QSharedDataPointer>

namespace KMBox
{
class MBoxEntryPrivate;
/*!
 * \class KMBox::MBoxEntry
 * \inmodule KMBox
 * \brief A class that encapsulates an entry of a MBox.
 *
 * \since 4.6
 */
class KMBOX_EXPORT MBoxEntry
{
public:
    /*!
     * Describes a list of mbox entry objects.
     */
    using List = QList<MBoxEntry>;

    /*!
     * Describes a pair of mbox entry objects.
     */
    using Pair = QPair<MBoxEntry, MBoxEntry>;

    /*!
     * Creates an invalid mbox entry object.
     */
    MBoxEntry();

    /*!
     * Creates an mbox entry object.
     *
     * \a offset The offset of the message the object references.
     */
    explicit MBoxEntry(quint64 offset);

    /*!
     * Creates an mbox entry object from an \a other object.
     */
    MBoxEntry(const MBoxEntry &other);

    /*!
     * Destroys the mbox entry object.
     */
    ~MBoxEntry();

    /*!
     * Replaces this mbox entry object with an \a other object.
     */
    MBoxEntry &operator=(const MBoxEntry &other);

    /*!
     * Returns whether this mbox entry object is equal to an \a other.
     */
    bool operator==(const MBoxEntry &other) const;

    /*!
     * Returns whether this mbox entry object is not equal to an \a other.
     */
    bool operator!=(const MBoxEntry &other) const;

    /*!
     * Returns whether this is a valid mbox entry object.
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * Returns the offset of the message that is referenced by this
     * mbox entry object.
     */
    [[nodiscard]] quint64 messageOffset() const;

    /*!
     * Returns the size of the message that is referenced by this
     * mbox entry object.
     */
    [[nodiscard]] quint64 messageSize() const;

    /*!
     * Returns the separator size of the message that is referenced by this
     * mbox entry object.
     */
    [[nodiscard]] quint64 separatorSize() const;

private:
    friend class MBox;

    QSharedDataPointer<MBoxEntryPrivate> d;
};
}

Q_DECLARE_TYPEINFO(KMBox::MBoxEntry, Q_RELOCATABLE_TYPE);
