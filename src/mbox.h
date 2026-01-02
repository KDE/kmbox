/*
    SPDX-FileCopyrightText: 2009 Bertjan Broeksema <broeksema@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "kmbox_export.h"
#include "mboxentry.h"
#include <memory>

#include <KMime/Message>

namespace KMBox
{
class MBoxPrivate;

/*!
 * \class KMBox::MBox
 * \inmodule KMBox
 * \inheaderfile KMbox/MBox
 * \brief A class to access mail storages in MBox format.
 *
 * \since 4.6
 */
class KMBOX_EXPORT MBox
{
public:
    /*!
     * Describes the type of locking that will be used.
     *
     * \value ProcmailLockfile
     * \value MuttDotlock
     * \value MuttDotlockPrivileged
     * \value None
     */
    enum LockType {
        ProcmailLockfile,
        MuttDotlock,
        MuttDotlockPrivileged,
        None
    };

    /*!
     * Creates a new mbox object.
     */
    MBox();

    /*!
     * Destroys the mbox object.
     *
     * The file will be unlocked if it is still open.
     */
    ~MBox();

    /*!
     * Appends \a message to the MBox and returns the corresponding mbox entry for it.
     *
     * You must load a mbox file by making a call to load( const QString& ) before
     * appending entries.
     * The returned mbox entry is only valid for that particular file.
     *
     * \a message The message to append to the mbox.
     *
     * Returns the corresponding mbox entry for the message in the file or an invalid mbox entry
     *         if the message was not added.
     */
    [[nodiscard]] MBoxEntry appendMessage(const std::shared_ptr<KMime::Message> &message);

    /*!
     * Retrieve the mbox entry objects for all emails from the file except the
     * \a deletedEntries.
     *
     * The \a deletedEntries should be a list of mbox entries with offsets of deleted messages.
     *
     * \a deletedEntries list of mbox entries that have been deleted and need not be retrieved
     *
     * \note One must call load() before calling this method.
     */
    [[nodiscard]] MBoxEntry::List entries(const MBoxEntry::List &deletedEntries = MBoxEntry::List()) const;

    /*!
     * Returns the file name that was passed to the last call to load().
     */
    [[nodiscard]] QString fileName() const;

    /*!
     * Loads the raw mbox data from disk into the current MBox object.
     *
     * Messages already present are not preserved. This method does not load the
     * full messages into memory but only the offsets of the messages and their
     * sizes. If the file currently is locked this method will do nothing and
     * return false. Appended messages that are not written yet will get lost.
     *
     * \a fileName the name of the mbox on disk.
     *
     * Returns \c true, if successful, \c false on error.
     *
     * \sa save()
     */
    [[nodiscard]] bool load(const QString &fileName);

    /*!
     * Locks the mbox file using the configured lock method.
     *
     * This can be used
     * for consecutive calls to readMessage and readMessageHeaders. Calling lock()
     * before these calls prevents the mbox file being locked for every call.
     *
     * \note Even when the lock method is None the mbox is internally marked as
     *       locked. This means that it must be unlocked before calling load().
     *
     * Returns \c true if locked successful, \c false on error.
     *
     * \sa setLockType(), unlock()
     */
    [[nodiscard]] bool lock();

    /*!
     * Returns whether or not the mbox currently is locked.
     */
    [[nodiscard]] bool locked() const;

    /*!
     * Removes all messages for the given mbox entries from the current reference file
     * (the file that is loaded with load().
     *
     * This method will first check if all lines at the offsets are actually
     * separator lines if this is not then no message will be deleted to prevent
     * corruption.
     *
     * \a deletedEntries The mbox entries of the messages that should be removed from
     *                       the file.
     *
     * \a movedEntries Optional list for storing pairs of mbox entries that got moved
     *                     within the file due to the deletions.
     *                     The first member of the pair is the entry with the original offsets
     *                     the second member is the entry with the new (current) offset
     *
     * Returns \c true if all offsets refer to a mbox separator line and a file was
     *         loaded, \c false otherwise. If the latter, the physical file has
     *         not changed.
     */
    [[nodiscard]] bool purge(const MBoxEntry::List &deletedEntries, QList<MBoxEntry::Pair> *movedEntries = nullptr);

    /*!
     * Reads the entire message from the file for the given mbox \a entry.
     *
     * If the mbox file is not locked this method will lock the file before reading and
     * unlock it after reading. If the file already is locked, it will not
     * unlock the file after reading the entry.
     *
     * \a entry The entry in the mbox file.
     *
     * Returns the message for the given entry or 0 if the file could not be locked
     *         or the entry offset > fileSize.
     *
     * \sa lock(), unlock()
     */
    std::unique_ptr<KMime::Message> readMessage(const MBoxEntry &entry);

    /*!
     * Reads the headers of the message for the given mbox \a entry.
     *
     * If the
     * mbox file is not locked this method will lock the file before reading and
     * unlock it after reading. If the file already is locked, it will not
     * unlock the file after reading the entry.
     *
     * \a entry The entry in the mbox file.
     *
     * Returns QByteArray containing the raw message header data.
     *
     * \sa lock(), unlock()
     */
    [[nodiscard]] QByteArray readMessageHeaders(const MBoxEntry &entry);

    /*!
     * Reads the entire message from the file for the given mbox \a entry.
     *
     * If the
     * mbox file is not locked this method will lock the file before reading and
     * unlock it after reading. If the file already is locked, it will not
     * unlock the file after reading the entry.
     *
     * \a entry The entry in the mbox file.
     *
     * Returns QByteArray containing the raw message data.
     *
     * \sa lock(), unlock()
     */
    [[nodiscard]] QByteArray readRawMessage(const MBoxEntry &entry);

    /*!
     * Writes the mbox to disk. If the fileName is empty only appended messages
     * will be written to the file that was passed to load( const QString & ).
     * Otherwise the contents of the file that was loaded with load is copied to
     * \a fileName first.
     *
     * \a fileName the name of the file
     *
     * Returns \c true if the save was successful; \c false otherwise.
     *
     * \sa load()
     */
    [[nodiscard]] bool save(const QString &fileName = QString());

    /*!
     * Sets the locktype that should be used for locking the mbox file.
     *
     * If the
     * new LockType cannot be used (e.g. the lockfile executable could not be
     * found) the LockType will not be changed.
     *
     * \a ltype the locktype to set
     *
     * This method will not do anything if the mbox object is currently locked
     * to make sure that it doesn't leave a locked file for one of the lockfile
     * methods.
     */
    [[nodiscard]] bool setLockType(LockType ltype);

    /*!
     * Sets the lockfile that should be used by the procmail or the KDE lock
     * file method.
     *
     * If this method is not called and one of the before mentioned
     * lock methods is used the name of the lock file will be equal to
     * MBOXFILENAME.lock.
     *
     * \a lockFile the lockfile to set
     */
    void setLockFile(const QString &lockFile);

    /*!
     * By default the unlock method will directly unlock the file.
     *
     * However this
     * is expensive in case of many consecutive calls to readEntry. Setting the
     * time out to a non zero value will keep the lock open until the timeout has
     * passed. On each read the timer will be reset.
     *
     * \a msec the time out to set for file lock
     */
    void setUnlockTimeout(int msec);

    /*!
     * Unlock the mbox file.
     *
     * Returns \c true if the unlock was successful, \c false otherwise.
     *
     * \sa lock()
     */
    [[nodiscard]] bool unlock();

    /*!
     * Set the access mode of the mbox file to read only.
     *
     * If this is set to true, the mbox file can only be read from disk.
     * When the mbox file given in load() can not be opened in readWrite mode,
     * but can be opened in readOnly mode, this flag is automatically set to true.
     * You can still append messages, which are stored in memory
     * until save() is called, but the mbox can not be saved/purged to itself.
     * However it is possible to save it to a different file.
     *
     * \a ro the readOnly flag to use
     *
     * \sa save()
     *
     * \since 4.14.5
     */
    void setReadOnly(bool ro = true);

    /*!
     * Returns if the current access mode is set to readOnly.
     *
     * The access mode can either be set explicitly with setReadOnly() or
     * implicitly by calling load() on a readOnly file.
     *
     * \since 4.14.5
     */
    [[nodiscard]] bool isReadOnly() const;

private:
    Q_DISABLE_COPY(MBox)
    std::unique_ptr<class MBoxPrivate> const d;
};
}
