#include "src/include/NetManager.h"
#include "src/include/Redes/Message.h"

NetManager* NetManager::_instance = nullptr;

NetManager::NetManager() {
    name = "name";
    isHost = false;
    socket = nullptr;
    onLogin = nullptr;
}
NetManager::~NetManager() {
    delete socket;
}

void NetManager::Init(bool host, const char * name, const char * s, const char * p) {
    if (_instance == nullptr) {
        _instance = new NetManager();
        _instance->name = name;
        _instance->isHost = host;
        _instance->socket = new Socket(s, p);
        _instance->socket->bind();

        _instance->InitThread();
    }
}

NetManager* NetManager::Instance() {
    return _instance;
}

void NetManager::Clear() {
    if (_instance)
        delete _instance;
    _instance = nullptr;
}

void NetManager::InitThread() {
    netThread = std::thread([this]() { DoMessages();});
}

void NetManager::SetOnLogin(const LoginCallback callback) {
    onLogin = callback;
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
            isHost = true;
            LoginMessage login;
            login.from_bin(msg.data());

            if (onLogin != nullptr) {
                onLogin(login);
            }
        }

    }
}

void NetManager::SendMessage(Message &messageToSend) {
    socket->send(messageToSend, *socket);
}