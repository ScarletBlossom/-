#include "../headers/MsgNode.h"

MsgNode::MsgNode(short Maxlen):_maxlen(Maxlen)
{
    _data = new char[_maxlen+1];
    _len = 0;
    if(_data) memset(_data,0,_maxlen+1);
}
void MsgNode::clear()
{
    _len = 0;
    if(_data) memset(_data,0,_maxlen);
}
MsgNode::~MsgNode(){
    if(_data) delete[] _data;
}

RecvMsgNode::RecvMsgNode(short len,short msg_id):MsgNode(len),_msgid(msg_id)
{
}

SendMsgNode::SendMsgNode(const char* data,short len,short msg_id):MsgNode(len+HEADER_LENGTH),_msgid(msg_id){
    short netlen = htons(len);
    short netid = htons(msg_id);
    memcpy(_data,&netid,HEAD_ID);
    memcpy(_data+HEAD_ID,&netlen,HEAD_LENGTH);
    memcpy(_data+HEADER_LENGTH,data,len);
}