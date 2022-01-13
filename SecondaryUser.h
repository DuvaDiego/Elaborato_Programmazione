#ifndef ELABORATO_PROGRAMMAZIONE_SECONDARYUSER_H
#define ELABORATO_PROGRAMMAZIONE_SECONDARYUSER_H

#include "User.h"

class SecondaryUser : public User{
public:
    SecondaryUser(bool f, std::string name);

    bool isFavourite() const;
    void setFavouritism(bool favouritism);

private:
    bool favourite;
};


#endif //ELABORATO_PROGRAMMAZIONE_SECONDARYUSER_H
