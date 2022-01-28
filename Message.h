#ifndef ELABORATO_PROGRAMMAZIONE_MESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_MESSAGE_H

#include <iostream>
#include <list>

#define regOwner "Diego"

class Message {
public:
    explicit Message(std::list<std::string>& t, bool imp = false);
    virtual ~Message() = default;

    virtual void getText() = 0;
    void setText(std::list<std::string> newText);

    bool getImportance() const;
    void setImportance(bool newImportance);

protected:
    std::list<std::string> text;
    bool important;

};


#endif //ELABORATO_PROGRAMMAZIONE_MESSAGE_H
