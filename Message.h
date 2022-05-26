#ifndef ELABORATO_PROGRAMMAZIONE_MESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_MESSAGE_H

#include <iostream>
#include <list>

class Message {
public:
    explicit Message(std::list<std::string>& t, bool imp = false);
    Message(std::list<std::string>& t, std::string s, std::string r, bool imp = false);
    virtual ~Message() = default;

    void getText();
    void setText(std::list<std::string> newText);

    bool getImportance() const;
    void setImportance(bool newImportance);

    std::string getSender() const;
    void setSender(std::string newSender);

    std::string getRecipient() const;
    void setRecipient(std::string newRecipient);

protected:
    std::list<std::string> text;
    bool important;
    std::string sender;
    std::string recipient;
};


#endif //ELABORATO_PROGRAMMAZIONE_MESSAGE_H
