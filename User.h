#ifndef ELABORATO_PROGRAMMAZIONE_USER_H
#define ELABORATO_PROGRAMMAZIONE_USER_H

#include <iostream>

class User {
public:
    explicit User(std::string name);
    virtual ~User() = default;

    std::string getName() const;
    void setName(std::string newNickName);

protected:
    std::string nickName;
};


#endif //ELABORATO_PROGRAMMAZIONE_USER_H
