#ifndef ELABORATO_PROGRAMMAZIONE_MESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_MESSAGE_H

#include <iostream>
#include <list>

class Message {
public:
    Message(std::list<std::string>& t, std::string s, std::string r, bool imp = false, bool read = false);
    virtual ~Message() = default;

    void getText();
    void setText(std::list<std::string> newText);
    bool searchWord(std::string word) const;

    bool getImportance() const;
    void setImportance(bool newImportance);

    bool isRead() const;
    void setRead(bool newRead);

    std::string getSender() const;
    void setSender(std::string newSender);

    std::string getRecipient() const;
    void setRecipient(std::string newRecipient);

    static bool isEqual(std::string word, std::string model);

protected:
    std::list<std::string> text;
    bool important;
    bool read;
    std::string sender;
    std::string recipient;
};


#endif //ELABORATO_PROGRAMMAZIONE_MESSAGE_H
