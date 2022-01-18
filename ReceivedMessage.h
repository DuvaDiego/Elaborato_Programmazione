#ifndef ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H

#include <iostream>
#include <list>
#include "Message.h"
#include "SecondaryUser.h"

class ReceivedMessage : public Message{
public:
    ReceivedMessage(std::list<std::string>& t, std::string s, bool imp = false, std::string r = "Diego");
    ~ReceivedMessage() override = default;

    std::string getSender() const;
    void setSender(std::string newSender);

    std::string getRecipient() const;

private:
    std::string sender;
    const std::string recipient;
};


#endif //ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H
