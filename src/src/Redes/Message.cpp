#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "src/include/Redes/Serializable.h"
#include "src/include/Redes/Socket.h"
#include "src/include/Redes/Message.h"
#include "src/include/Transform.h"


Message::Message(MessageType a) : type(a){};

void Message::to_bin() {
    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    memcpy(_data, &type, sizeof(MessageType));
}

int Message::from_bin(char * bobj) {
    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);
    memcpy(&type, bobj, MAX_SIZE);
    return 0;
}



LoginMessage::LoginMessage() : Message(LOGIN), userName("SinNombre"), nameLength(strlen(userName.c_str()))
{ MESSAGE_SIZE = strlen(userName.c_str()) + sizeof(uint8_t) + sizeof(size_t); };

LoginMessage::LoginMessage(std::string name) : Message(LOGIN), userName(name), nameLength(strlen(userName.c_str()))
{ MESSAGE_SIZE = strlen(userName.c_str()) + sizeof(uint8_t) + sizeof(size_t); };

void LoginMessage::to_bin() {
    alloc_data(MAX_SIZE);
    memset(_data, 0, MAX_SIZE);
    char* aux = _data;
    memcpy(aux, &type, sizeof(MessageType));
    aux += sizeof(MessageType);

    std::cout << "Login::toBin type: " << type << "\n";

    memcpy(aux, &nameLength, sizeof(size_t));
    aux += sizeof(size_t);

    std::cout << "Login::toBin nameLength: " << (size_t)nameLength << "\n";

    const char* a = userName.c_str();
        memcpy(aux, a, nameLength);

    std::cout << "Login::toBin userName: " << a << "\n";
}

int LoginMessage::from_bin(char * bobj) {

    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);
    memcpy(&type, bobj, sizeof(MessageType));
    bobj += sizeof(uint8_t);

    std::cout << "Login::fromBin type: " << type << "\n";

    memcpy(&nameLength, bobj, sizeof(size_t));
    bobj += sizeof(size_t);

    std::cout << "Login::fromBin nameLength: " << nameLength << "\n";

    char user[nameLength];
    memcpy(user, bobj, nameLength);
    userName = std::string(user);

    std::cout << "Login::fromBin userName: " << userName << "\n";
    return 0;
}


NewObjectMessage::NewObjectMessage() : Message(NEWOBJECT){
    MESSAGE_SIZE = sizeof(float)*7;
}

NewObjectMessage::NewObjectMessage(Transform* tr) :  Message(NEWOBJECT){
    velocity = tr->getVelocity();
    position = tr->getPosition();
    size = tr->getSize();
    rotation = tr->getRotation();
    MESSAGE_SIZE = sizeof(float)*7;
};

void NewObjectMessage::to_bin(){
    alloc_data(MESSAGE_SIZE);
    memset(_data, 0, MESSAGE_SIZE);
    char* aux = _data;
    memcpy(aux, &type, sizeof(MessageType));
    aux += sizeof(MessageType);

    std::cout << "Login::toBin type: " << type << "\n";

    memcpy(aux, &position.x, sizeof(size_t));
    aux += sizeof(float);

    memcpy(aux, &position.y, sizeof(float));
    aux += sizeof(float);

    memcpy(aux, &size.x, sizeof(float));
    aux += sizeof(float);

    memcpy(aux, &size.y, sizeof(float));
    aux += sizeof(float);

    memcpy(aux, &velocity.x, sizeof(float));
    aux += sizeof(float);

    memcpy(aux, &velocity.y, sizeof(float));
    aux += sizeof(float);

    memcpy(aux, &rotation, sizeof(float));
}

int NewObjectMessage::from_bin(char*bobj){
    alloc_data(MAX_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);
    memcpy(&type, bobj, sizeof(MessageType));
    bobj += sizeof(uint8_t);

    memcpy(&position.x, bobj, sizeof(float));
    bobj += sizeof(float);

    memcpy(&position.y, bobj, sizeof(float));
    bobj += sizeof(float);

    memcpy(&size.x, bobj, sizeof(float));
    bobj += sizeof(float);

    memcpy(&size.y, bobj, sizeof(float));
    bobj += sizeof(float);

    memcpy(&velocity.x, bobj, sizeof(float));
    bobj += sizeof(float);

    memcpy(&velocity.y, bobj, sizeof(float));
    bobj += sizeof(float);

    memcpy(&rotation, bobj, sizeof(float));
    bobj += sizeof(float);
    return 0;

}