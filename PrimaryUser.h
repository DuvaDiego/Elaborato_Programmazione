#ifndef ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H
#define ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H

#include "User.h"
#include "ChatRegister.h"

class PrimaryUser : public User{
public:
    explicit PrimaryUser(ChatRegister* reg, std::string name = "Diego");
    ~PrimaryUser() override;

    void writeRegister() const;

private:
    ChatRegister* theRegister;
};


#endif //ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H
