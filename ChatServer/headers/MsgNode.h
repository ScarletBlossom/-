#pragma once
#include <cstring>
class MsgNode
{
public:
    MsgNode(int Maxlen):_maxlen(Maxlen),_len(0){
        _data = new char[Maxlen+1]();
        _data[Maxlen] = '\0';
    }
    void clear(){
        _len = 0;
        if(_data) memset(_data,0,_maxlen);
    }
    ~MsgNode(){
        if(_data) delete[] _data;
    }
    char* _data;
    short _maxlen;
    short _len;
};

class RecvMsgNode:public MsgNode
{
public:
    RecvMsgNode(short Maxlen,short Msgid);
    ~RecvMsgNode();
    short _msgid;
};

class SendMsgNode:public MsgNode
{
private:
    /* data */
public:
 SendMsgNode:public MsgNode(/* args */);
     SendMsgNode:public MsgNode();
};
