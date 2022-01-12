#ifndef ELABORATO_PROGRAMMAZIONE_SENTMESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_SENTMESSAGE_H

#include <iostream>
#include "Message.h"
#include "SecondaryUser.h"

class SentMessage : public Message{
public:
    SentMessage(std::string t, bool imp, SecondaryUser* r, std::string s = "Diego");
    ~SentMessage() override = default;

    std::string getSender() const;

    SecondaryUser* getRecipient() const;
    void setRecipient(SecondaryUser* newRecipient);

private:
    const std::string sender;
    SecondaryUser* recipient;
};


#endif //ELABORATO_PROGRAMMAZIONE_SENTMESSAGE_H
