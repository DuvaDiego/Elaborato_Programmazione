#ifndef ELABORATO_PROGRAMMAZIONE_REGISTERVIEW_H
#define ELABORATO_PROGRAMMAZIONE_REGISTERVIEW_H

#include <iostream>
#include <memory>
#include "Register.h"
#include "Chat.h"

class RegisterView {
public:
    explicit RegisterView(std::shared_ptr<Register> r);
    ~RegisterView();

    void tellInstruction(int parameter);

    std::string writeNameChat(int parameter);
    void getChatList();
    void tellCurrentChat(std::string name);
    void tellStateChat(std::string name, int parameter, bool parValue);
    void closeRegister();

    std::shared_ptr<Register> getRegister();

private:
    std::shared_ptr<Register> aRegister;
};


#endif //ELABORATO_PROGRAMMAZIONE_REGISTERVIEW_H
