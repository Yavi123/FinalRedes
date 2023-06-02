#ifndef NETMANAGER_H
#define NETMANAGER_H

#include "src/include/Redes/Socket.h"
#include <list>

class Message;
class LoginMessage;
class PositionMessage;
class StateMachine;

class NetManager {
public:

    static void Init(bool host, const char * name, const char * s, const char * p);
    static NetManager* Instance();
    static void Clear();

    void SetStateMachine(StateMachine* m) {stMachine = m;};

    void receive();
    void process();

    void SendMessage(Message &messageToSend);

    inline std::string GetNick() {return name;};

    inline bool isTurn() {return turn;};
   
    inline bool isHost() {return host;};
    void setAsHost();

    void changeTurn();
    inline void setTurn(bool b){turn = b;};
    void EndMatch();
private:

    NetManager();
    ~NetManager();

    static NetManager* _instance;

    bool host;

    const char* name;

    Socket* socket;
    Socket* client;

    std::list<Message*> toProcess;
    bool turn;

    StateMachine* stMachine;

};

#endif