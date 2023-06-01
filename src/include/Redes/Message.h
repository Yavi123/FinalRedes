#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "Serializable.h"
#include "Socket.h"
#include "src/include/Vector2.h"

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

enum MessageType : uint8_t
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

    Message(MessageType a);

    virtual void to_bin() override;

    virtual int from_bin(char * bobj) override;

    MessageType type;
};

class LoginMessage : public Message {

public:
    LoginMessage();
        
    LoginMessage(std::string name);

    void to_bin() override;

    int from_bin(char * bobj) override;

    std::string userName;
    size_t nameLength;
};

class Transform;

class NewObjectMessage : public Message {
public:
    NewObjectMessage();
    NewObjectMessage(Transform* tr);


    void to_bin() override;
    int from_bin (char* bobj) override;

    //Transform* tr;
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    float rotation;
};
