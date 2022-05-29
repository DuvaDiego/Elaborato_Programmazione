#ifndef ELABORATO_PROGRAMMAZIONE_REGISTERVIEW_H
#define ELABORATO_PROGRAMMAZIONE_REGISTERVIEW_H

#include <iostream>
#include <memory>
#include "Chat.h"

class RegisterView {
public:
    RegisterView() = default;
    ~RegisterView() = default;

    static void tellInstruction(int parameter);
    static std::string writeNameChat(int parameter);
    static void writeChats(std::list<std::shared_ptr<Chat>> list);
    static void tellCurrentChat(std::string name);
    static void tellStateChat(std::string name, int parameter, bool parValue);
    static void closeRegister();
};


#endif //ELABORATO_PROGRAMMAZIONE_REGISTERVIEW_H
