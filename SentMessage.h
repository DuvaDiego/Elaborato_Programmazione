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

    //FIXME: vanno sistemti i metodi getter e setter del destinatario (anche le definizioni)
    SecondaryUser* getRecipient() const;
    void setRecipient(SecondaryUser* newRecipient);

private:
    const std::string sender;
    SecondaryUser* recipient; //FIXME: trattandosi di un nome dovrebbe essere una stringa, non un SecondaryUser*
};


#endif //ELABORATO_PROGRAMMAZIONE_SENTMESSAGE_H
