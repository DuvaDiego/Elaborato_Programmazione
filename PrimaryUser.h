#ifndef ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H
#define ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H

#include "User.h"
#include "ChatRegister.h"

class PrimaryUser : public User{
public:
    explicit PrimaryUser(std::shared_ptr<ChatRegister> reg, std::string name = regOwner);
    ~PrimaryUser() override;

    void writeRegister() const;

private:
    std::shared_ptr<ChatRegister> theRegister;
};


#endif //ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H
