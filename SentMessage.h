#ifndef ELABORATO_PROGRAMMAZIONE_SENTMESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_SENTMESSAGE_H

#include <iostream>
#include <list>
#include "Message.h"
#include "SecondaryUser.h"

class SentMessage : public Message{
public:
    SentMessage(std::list<std::string>& t, std::string r, bool imp = false, std::string s = "Diego");
    ~SentMessage() override = default;

    void getText() const override;

    std::string getSender() const;

    std::string getRecipient() const;
    void setRecipient(std::string newRecipient);

private:
    const std::string sender;
    std::string recipient;
};


#endif //ELABORATO_PROGRAMMAZIONE_SENTMESSAGE_H
