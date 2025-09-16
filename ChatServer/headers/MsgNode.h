#pragma once
#include <cstring>
#include "Const.h"
class MsgNode
{
public:
    MsgNode(short Maxlen);
    void clear();
    ~MsgNode();
    char* _data;
    short _maxlen;
    short _len;
};

class RecvMsgNode:public MsgNode
{
public:
    RecvMsgNode(short len,short msg_id);
    short _msgid;
};

class SendMsgNode:public MsgNode
{
public:
    SendMsgNode(const char* data,short len,short msg_id);
    short _msgid;
};
