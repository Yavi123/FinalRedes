#include "src/include/NetManager.h"
#include "src/include/Redes/Message.h"
#include "src/include/StateMachine.h"
#include "src/include/State.h"
#include "SDL.h"

NetManager* NetManager::_instance = nullptr;

NetManager::NetManager() {
    name = "name";
    host = false;
    socket = nullptr;
    toProcess = std::list<Message*>();
    turn = false;
}
NetManager::~NetManager() {
    delete socket;
}

void NetManager::Init(bool host, const char * name, const char * s, const char * p) {
    if (_instance == nullptr) {
        _instance = new NetManager();
        _instance->name = name;
        _instance->host = host;

        if(_instance->host){
            _instance->socket = new Socket(s, p);
            _instance->socket->bind();
            _instance->client = nullptr;
            _instance->turn = true;
            //_instance->InitThread();
        }else{
            _instance->socket = new Socket(s, p);
            _instance->socket->bind();
            std::string s;
            std::cout << "Introduzca ip del servidor: ";
            std::cin >> s;
            _instance->client = new Socket(s.c_str(),"8080");
            LoginMessage m = LoginMessage(_instance->name);
            _instance->SendMessage(m);
            _instance->turn = true;
           // _instance->InitThread();
        }
    }
}

NetManager* NetManager::Instance() {
    return _instance;
}

void NetManager::Clear() {
    if (_instance) {
        Message a = Message(LOGOUT);
        _instance->SendMessage(a);
        delete _instance;
    }
    _instance = nullptr;
}

void NetManager::InitThread() {
}

void NetManager::DoMessages() {

    while (true)
    {
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */

        //Recibir Mensajes en y en función del tipo de mensaje
        // - LOGIN: Añadir al vector clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
        Message msg(EMPTY);
        Socket* client;
        int ret = socket->recv(msg, &client);
        if(ret == -1) continue;

        if(msg.type == LOGIN) {
            host = true;
            LoginMessage login;
            login.from_bin(msg.data());
            this->client = client;
        }
        else if(msg.type == TRANSFORM) {
        }
    }
}

void NetManager::SendMessage(Message &messageToSend) {
    if(client!=nullptr)
    socket->send(messageToSend, *client);
}

void NetManager::receive(){
    Uint32 tick = SDL_GetTicks();
    while(SDL_GetTicks() - tick <= 5){
        Message* msg = new Message(EMPTY);
        Socket* client;
        int ret = socket->recv(*msg, &client);
        if(ret == -1) { 
            delete msg;
            continue;
        }
        else toProcess.push_back(msg);
        if(msg->type == LOGIN){
            this->client = client;
        }
    }
}
void NetManager::process(){
    for(Message* m : toProcess){     
        stMachine->GetCurrentState()->HandleMessage(*m);            
    }

    for(auto it = toProcess.begin(); it!=toProcess.end(); ++it){
        delete *it;
    }

    toProcess.clear();
}

void NetManager::setAsHost(){
    host = true;
    turn = true;
    client = nullptr;

    
}