#ifndef ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H

#include <iostream>
#include <list>
#include "Message.h"
#include "SecondaryUser.h"

class ReceivedMessage : public Message{
public:
    ReceivedMessage(std::list<std::string>& t, std::string s, bool imp = false);
    ~ReceivedMessage() override = default;

    void getText() override;

    std::string getSender() const;
    void setSender(std::string newSender);

    std::string getRecipient() const;

private:
    std::string sender;
    const std::string recipient = regOwner;
};


#endif //ELABORATO_PROGRAMMAZIONE_RECEIVEDMESSAGE_H
