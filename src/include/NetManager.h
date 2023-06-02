#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <thread>
#include <functional>
#include "src/include/Redes/Socket.h"
#include <list>

class Message;
class LoginMessage;

typedef void (*LoginCallback)(const LoginMessage&);

class NetManager {
public:

    static void Init(bool host, const char * name, const char * s, const char * p);
    static NetManager* Instance();
    static void Clear();

    //void setSock(const char* ip, const char* port);

    void SetOnLogin(const LoginCallback callback);

    void InitThread();

    void DoMessages();

    void SendMessage(Message &messageToSend);

private:

    NetManager();
    ~NetManager();

    static NetManager* _instance;

    bool isHost;

    const char* name;

    LoginCallback onLogin;

    Socket* socket;
    Socket* client;

    std::thread netThread;

    std::list<Message> toProcess;

};

#endif