#ifndef MSG_HPP
#define MSG_HPP

enum MSG_TYPE {
    PLAYER_DATA_REQ =  0,
    PLAYER_DATA,
    
    
    JOIN_BATTLE     = 10,
    
    MSG_GLOBAL      = 20
};

class Msg {
    
    public:
    virtual void exec()=0;
};

class MsgPlayerDataReq: public Msg{
    
};

#endif // MSG_HPP
