/***************************************************************************
**
** Copyright (C) 2013 Research In Motion
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtNfc module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QLLCPSERVER_QNX_P_H
#define QLLCPSERVER_QNX_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qllcpserver_p.h"
#include "nfc/nfc.h"

QT_BEGIN_NAMESPACE

class QLlcpServerPrivate : public QObject
{
    Q_OBJECT
public:
    QLlcpServerPrivate(QLlcpServer *q);

    bool listen(const QString &serviceUri);
    bool isListening() const;

    void close();

    QString serviceUri() const;
    quint8 serverPort() const;

    bool hasPendingConnections() const;
    QLlcpSocket *nextPendingConnection();

    QLlcpSocket::SocketError serverError() const;

    Q_INVOKABLE void connected(nfc_target_t *);

private:
    QLlcpServer *q_ptr;
    QLlcpSocket *m_llcpSocket;
    //We can not use m_conListener for the connection state
    bool m_connected;
    nfc_llcp_connection_listener_t m_conListener;
    QString m_serviceUri;
    nfc_target_t *m_target;
};

QT_END_NAMESPACE

#endif // QLLCPSERVER_QNX_P_H
