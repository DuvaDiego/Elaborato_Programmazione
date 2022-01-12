#ifndef ELABORATO_PROGRAMMAZIONE_MESSAGE_H
#define ELABORATO_PROGRAMMAZIONE_MESSAGE_H

#include <iostream>

class Message {
public:
    explicit Message(std::string t, bool imp = false);
    virtual ~Message() = default;

    std::string getText() const;
    void setText(std::string newText);

    bool getImportance() const;
    void setImportance(bool newImportance);

protected:
    std::string text;
    bool important;

};


#endif //ELABORATO_PROGRAMMAZIONE_MESSAGE_H
