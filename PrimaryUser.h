#ifndef ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H
#define ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H

#include "User.h"
#include "Register.h"

class PrimaryUser : public User{
public:
    explicit PrimaryUser(std::shared_ptr<Register> reg, std::string name = regOwner);
    ~PrimaryUser() override;

private:
    std::shared_ptr<Register> theRegister;
};


#endif //ELABORATO_PROGRAMMAZIONE_PRIMARYUSER_H
