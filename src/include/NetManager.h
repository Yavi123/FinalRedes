#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <thread>
#include <functional>
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

    //void setSock(const char* ip, const char* port);

    void InitThread();

    void DoMessages();

    void receive();
    void process();


    void SendMessage(Message &messageToSend);

    std::string GetNick() {return name;}

private:

    NetManager();
    ~NetManager();

    static NetManager* _instance;

    bool isHost;

    const char* name;

    Socket* socket;
    Socket* client;

    std::list<Message*> toProcess;
    bool turn;

    StateMachine* stMachine;

};

#endif