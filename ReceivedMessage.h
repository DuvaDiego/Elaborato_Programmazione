#ifndef ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H

#include <iostream>
#include "Message.h"
#include "SecondaryUser.h"

class ReceivedMessage : public Message{
public:
    ReceivedMessage(std::string t, bool imp, SecondaryUser* s, std::string r = "Diego");
    ~ReceivedMessage() override = default;

    SecondaryUser* getSender() const;
    void setSender(SecondaryUser* newSender);

    std::string getRecipient() const;

private:
    SecondaryUser* sender;
    const std::string recipient;
};


#endif //ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H
