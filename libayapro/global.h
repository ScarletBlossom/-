#ifndef GLOBAL_H
#define GLOBAL_H

#include <QWidget>
#include <functional>
#include "QStyle"
#include <QRegularExpression>
#include <memory.h>

#include <QByteArray>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDir>
#include <QSettings>
#include <QString>
/******************************************************************************
 *
 * @file       global.h
 * @brief      refresh page
 *
 * @author     Libaya
 * @date       2025/05/28
 * @history
 *****************************************************************************/
extern QString gate_url_prefix;

extern std::function<void(QWidget*)> repolish;
enum ReqId{
    ID_GET_VERIFY_CODE = 1001,
    ID_REG_USER = 1002,
    ID_CHANGE_PW = 1003,
    // ID_CHAT_LOGIN_REQ = 1004,
    ID_CHAT_LOGIN_RSP = 1004,
};

enum Modules{
    REGISTERMOD = 0,
    CHANGEPWMOD = 1,
    LOGINMOD = 2,
};

enum ErrorCodes{
    SUCCESS = 0,
    ERR_JSON = 1,
    ERR_NETWORK = 2,
};

enum ClickLbState{
    Normal = 0,
    Selected = 1
};

enum TipErr{
    TIP_SUCCESS = 0,
    TIP_EMAIL_ERR = 1,
    TIP_PWD_ERR = 2,
    TIP_CONFIRM_ERR = 3,
    TIP_PWD_CONFIRM = 4,
    TIP_VERIFY_ERR = 5,
    TIP_USER_ERR = 6
};

struct ServerInfo
{
    QString Host;
    QString Port;
    QString Token;
    int Uid;
};


#endif // GLOBAL_H
