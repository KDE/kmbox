/*
    SPDX-FileCopyrightText: 2009 Bertjan Broeksema <broeksema@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QByteArray>

const QByteArray sEntry1(
    "Return-path: <commitfilter@new.kstuff.org>\n"
    "Received: from smtp1.tb.mail.iss.as9143.net ([212.54.42.132])\n"
    " by mta2z1.tb.mail.iss.as9143.net\n"
    " (Sun Java(tm) System Messaging Server 6.3-7.04 (built Sep 26 2008; 32bit))\n"
    " with ESMTP id <0KL300ECMGTOOV10@mta2z1.tb.mail.iss.as9143.net> for\n"
    " broeksema@kde.org; Thu, 11 Jun 2009 23:53:48 +0200 (CEST)\n"
    "Received: from mx4.tb.mail.iss.as9143.net ([212.54.42.103])\n"
    " by smtp1.tb.mail.iss.as9143.net with esmtp (Exim 4.69)\n"
    " (envelope-from <commitfilter@new.kstuff.org>)\n"
    " id 1MEsDT-0002ap-FM  for broeksema@kde.org; Thu, 11 Jun 2009 23:53:47 +0200\n"
    "Received: from kdeget.osuosl.org ([140.211.166.77])\n"
    " by mx4.tb.mail.iss.as9143.net with esmtp (Exim 4.69)\n"
    " (envelope-from <commitfilter@new.kstuff.org>)\n"
    " id 1MEsDS-00011A-Kf  for broeksema@kde.org; Thu, 11 Jun 2009 23:53:47 +0200\n"
    "Received: from ktown.kde.org ([131.246.120.250])  by kdeget.osuosl.org with smtp\n"
    " (Exim 4.69)\n"
    " (envelope-from <kde-commits-bounces-+commitfilter=new.kstuff.org@kde.org>)\n"
    " id 1MEsCw-0002Hs-9n  for commitfilter@new.kstuff.org; Thu,\n"
    " 11 Jun 2009 23:53:14 +0200\n"
    "Received: (qmail 22909 invoked by uid 72); Thu, 11 Jun 2009 21:53:05 +0000\n"
    "Received: (qmail 22893 invoked from network); Thu, 11 Jun 2009 21:53:02 +0000\n"
    "Received: from unknown (HELO office.kde.org) (195.135.221.67)\n"
    " by ktown.kde.org with SMTP; Thu, 11 Jun 2009 21:53:00 +0000\n"
    "Received: from svn.kde.org (localhost [127.0.0.1])  by office.kde.org (Postfix)\n"
    " with SMTP id 1F87C64 for <kde-commits@kde.org>; Thu,\n"
    " 11 Jun 2009 23:53:01 +0200 (CEST)\n"
    "Received: (nullmailer pid 3865 invoked by uid 50099); Thu,\n"
    " 11 Jun 2009 21:53:01 +0000\n"
    "Date: Thu, 11 Jun 2009 21:53:01 +0000\n"
    "From: Bertjan Broeksema <broeksema@kde.org>\n"
    "Subject: KDE/kdepim/akonadi/resources/mbox\n"
    "To: kde-commits@kde.org\n"
    "Reply-to: kde-commits@kde.org\n"
    "Message-id: <1244757181.066698.3864.nullmailer@svn.kde.org>\n"
    "MIME-version: 1.0\n"
    "Content-type: text/plain;\n"
    "  charset=UTF-8\n"
    "Content-transfer-encoding: 8bit\n"
    "Precedence: list\n"
    "X-BeenThere: kde-commits@kde.org\n"
    "X-Spam-Checker-Version: SpamAssassin 3.2.5 (2008-06-10) on ktown.kde.org\n"
    "X-Commit-Directories: (0) trunk/KDE/kdepim/akonadi/resources/mbox\n"
    "  trunk/KDE/kdepim/akonadi/resources/mbox/libmbox\n"
    "X-MailScanner-ID: 1MEsDS-00011A-Kf\n"
    "X-ZiggoMX-MailScanner: Found to be clean\n"
    "X-ZiggoMX-MailScanner-SpamCheck: not spam\n"
    "X-ZiggoMX-MailScanner-From: commitfilter@new.kstuff.org\n"
    "X-ZiggoSMTP-MailScanner-Information: Please contact the ISP for more information\n"
    "X-ZiggoSMTP-MailScanner-ID: 1MEsDT-0002ap-FM\n"
    "X-ZiggoSMTP-MailScanner: Found to be clean\n"
    "X-ZiggoSMTP-MailScanner-SpamCheck: not spam, SpamAssassin (not cached,\n"
    "  score=2.654, required 5, BAYES_00 -2.60, FRT_PROFILE2 2.11, FRT_STOCK2 2.99,\n"
    " TW_FC 0.08, TW_OC 0.08)\n"
    "X-ZiggoSMTP-MailScanner-SpamScore: ss\n"
    "X-ZiggoSMTP-MailScanner-From: commitfilter@new.kstuff.org\n"
    "X-Mailman-Version: 2.1.9\n"
    "List-Post: <mailto:kde-commits@kde.org>\n"
    "List-Subscribe: <https://mail.kde.org/mailman/listinfo/kde-commits>,\n"
    " <mailto:kde-commits-request@kde.org?subject=subscribe>\n"
    "List-Unsubscribe: <https://mail.kde.org/mailman/listinfo/kde-commits>,\n"
    " <mailto:kde-commits-request@kde.org?subject=unsubscribe>\n"
    "List-Help: <mailto:kde-commits-request@kde.org?subject=help>\n"
    "List-Id: Notification of KDE commits <kde-commits.kde.org>\n"
    "Original-recipient: rfc822;broeksema@kde.org\n"
    "X-Spam-Status: No\n"
    "Status: R\n"
    "X-Status: N\n"
    "X-KMail-EncryptionState:\n"
    "X-KMail-SignatureState:\n"
    "X-KMail-MDN-Sent:\n"
    "\n"
    "TEST MESSAGE 1");

const QByteArray sEntry2(
    "Return-path: <commitfilter@new.kstuff.org>\n"
    "Received: from smtp1.tb.mail.iss.as9143.net ([212.54.42.132])\n"
    " by mta2z1.tb.mail.iss.as9143.net\n"
    " (Sun Java(tm) System Messaging Server 6.3-7.04 (built Sep 26 2008; 32bit))\n"
    " with ESMTP id <0KL300ECMGTOOV10@mta2z1.tb.mail.iss.as9143.net> for\n"
    " broeksema@kde.org; Thu, 11 Jun 2009 23:53:48 +0200 (CEST)\n"
    "Received: from mx4.tb.mail.iss.as9143.net ([212.54.42.103])\n"
    " by smtp1.tb.mail.iss.as9143.net with esmtp (Exim 4.69)\n"
    " (envelope-from <commitfilter@new.kstuff.org>)\n"
    " id 1MEsDT-0002ap-FM  for broeksema@kde.org; Thu, 11 Jun 2009 23:53:47 +0200\n"
    "Received: from kdeget.osuosl.org ([140.211.166.77])\n"
    " by mx4.tb.mail.iss.as9143.net with esmtp (Exim 4.69)\n"
    " (envelope-from <commitfilter@new.kstuff.org>)\n"
    " id 1MEsDS-00011A-Kf  for broeksema@kde.org; Thu, 11 Jun 2009 23:53:47 +0200\n"
    "Received: from ktown.kde.org ([131.246.120.250])  by kdeget.osuosl.org with smtp\n"
    " (Exim 4.69)\n"
    " (envelope-from <kde-commits-bounces-+commitfilter=new.kstuff.org@kde.org>)\n"
    " id 1MEsCw-0002Hs-9n  for commitfilter@new.kstuff.org; Thu,\n"
    " 11 Jun 2009 23:53:14 +0200\n"
    "Received: (qmail 22909 invoked by uid 72); Thu, 11 Jun 2009 21:53:05 +0000\n"
    "Received: (qmail 22893 invoked from network); Thu, 11 Jun 2009 21:53:02 +0000\n"
    "Received: from unknown (HELO office.kde.org) (195.135.221.67)\n"
    " by ktown.kde.org with SMTP; Thu, 11 Jun 2009 21:53:00 +0000\n"
    "Received: from svn.kde.org (localhost [127.0.0.1])  by office.kde.org (Postfix)\n"
    " with SMTP id 1F87C64 for <kde-commits@kde.org>; Thu,\n"
    " 11 Jun 2009 23:53:01 +0200 (CEST)\n"
    "Received: (nullmailer pid 3865 invoked by uid 50099); Thu,\n"
    " 11 Jun 2009 21:53:01 +0000\n"
    "Date: Thu, 11 Jun 2009 21:53:01 +0000\n"
    "From: Jaap Aap <jaap@aap.nl>\n"
    "Subject: KDE/kdepim/akonadi/resources/mbox\n"
    "To: kde-commits@kde.org\n"
    "Reply-to: kde-commits@kde.org\n"
    "Message-id: <1244757181.066698.3864.nullmailer@svn.kde.org>\n"
    "MIME-version: 1.0\n"
    "Content-type: text/plain;\n"
    "  charset=UTF-8\n"
    "Content-transfer-encoding: 8bit\n"
    "Precedence: list\n"
    "X-BeenThere: kde-commits@kde.org\n"
    "X-Spam-Checker-Version: SpamAssassin 3.2.5 (2008-06-10) on ktown.kde.org\n"
    "X-Commit-Directories: (0) trunk/KDE/kdepim/akonadi/resources/mbox\n"
    "  trunk/KDE/kdepim/akonadi/resources/mbox/libmbox\n"
    "X-MailScanner-ID: 1MEsDS-00011A-Kf\n"
    "X-ZiggoMX-MailScanner: Found to be clean\n"
    "X-ZiggoMX-MailScanner-SpamCheck: not spam\n"
    "X-ZiggoMX-MailScanner-From: commitfilter@new.kstuff.org\n"
    "X-ZiggoSMTP-MailScanner-Information: Please contact the ISP for more information\n"
    "X-ZiggoSMTP-MailScanner-ID: 1MEsDT-0002ap-FM\n"
    "X-ZiggoSMTP-MailScanner: Found to be clean\n"
    "X-ZiggoSMTP-MailScanner-SpamCheck: not spam, SpamAssassin (not cached,\n"
    "  score=2.654, required 5, BAYES_00 -2.60, FRT_PROFILE2 2.11, FRT_STOCK2 2.99,\n"
    " TW_FC 0.08, TW_OC 0.08)\n"
    "X-ZiggoSMTP-MailScanner-SpamScore: ss\n"
    "X-ZiggoSMTP-MailScanner-From: commitfilter@new.kstuff.org\n"
    "X-Mailman-Version: 2.1.9\n"
    "List-Post: <mailto:kde-commits@kde.org>\n"
    "List-Subscribe: <https://mail.kde.org/mailman/listinfo/kde-commits>,\n"
    " <mailto:kde-commits-request@kde.org?subject=subscribe>\n"
    "List-Unsubscribe: <https://mail.kde.org/mailman/listinfo/kde-commits>,\n"
    " <mailto:kde-commits-request@kde.org?subject=unsubscribe>\n"
    "List-Help: <mailto:kde-commits-request@kde.org?subject=help>\n"
    "List-Id: Notification of KDE commits <kde-commits.kde.org>\n"
    "Original-recipient: rfc822;broeksema@kde.org\n"
    "X-Spam-Status: No\n"
    "Status: R\n"
    "X-Status: N\n"
    "X-KMail-EncryptionState:\n"
    "X-KMail-SignatureState:\n"
    "X-KMail-MDN-Sent:\n"
    "\n"
    "This is another test message.\n"
    "\n"
    "Cheers,\n"
    "\n"
    "Bertjan");

