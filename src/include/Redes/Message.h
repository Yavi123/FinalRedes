#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 *  Mensaje del protocolo de la aplicación de Chat
 *
 *  +-------------------+
 *  | Tipo: uint8_t     | 0 (login), 1 (mensaje), 2 (logout)
 *  +-------------------+
 *  | Nick: char[8]     | Nick incluido el char terminación de cadena '\0'
 *  +-------------------+
 *  |                   |
 *  | Mensaje: char[80] | Mensaje incluido el char terminación de cadena '\0'
 *  |                   |
 *  +-------------------+
 *
 */

enum MessageType : u_int8_t
{
    EMPTY       = 0,
    LOGIN       = 1,
    MATCHSTART  = 2,
    INPUT       = 3,
    POSITION    = 4,
    NEWOBJECT   = 5,
    MATCHEND    = 6,
    LOGOUT      = 7
};

class Message: public Serializable
{
public:
    u_int8_t MESSAGE_SIZE = sizeof(uint8_t);

    const static u_int8_t MAX_SIZE = 255;

    Message(MessageType a) : type(a){};

    virtual void to_bin() override {
        alloc_data(MESSAGE_SIZE);
        memset(_data, 0, MESSAGE_SIZE);
        memcpy(_data, &type, sizeof(uint8_t));
    }

    virtual int from_bin(char * bobj) override {
        alloc_data(sizeof(uint8_t));
        memcpy(static_cast<void*>(_data), bobj, sizeof(uint8_t));
        memcpy(&type, bobj, sizeof(uint8_t));
        return 0;
    }

    MessageType type;
};

class LoginMessage : public Message {

public:
    LoginMessage() : Message(LOGIN), userName("SinNombre"){ MESSAGE_SIZE += userName.length() + sizeof(uint8_t); };
    LoginMessage(std::string name) : Message(LOGIN), userName(name){ MESSAGE_SIZE += userName.length() + sizeof(uint8_t); };

    void to_bin() override {
        Message::to_bin();
        char* aux = _data;
        aux += sizeof(uint8_t);

        uint8_t nameLength = userName.length();
        memcpy(_data, &nameLength, sizeof(uint8_t));
        aux += sizeof(uint8_t);

        memcpy(_data, userName.c_str(), nameLength);
    }

    int from_bin(char * bobj) override {
        alloc_data(MAX_SIZE);
        memcpy(static_cast<void*>(_data), bobj, MAX_SIZE);
        memcpy(&type, bobj, sizeof(uint8_t));
        bobj += sizeof(uint8_t);

        uint8_t nameSize = 0;
        memcpy(&nameSize, bobj, sizeof(uint8_t));
        bobj += sizeof(uint8_t);

        char* user;
        memcpy(user, bobj, nameSize);
        userName = std::string(user);
        return 0;
    }

    std::string userName;
};
