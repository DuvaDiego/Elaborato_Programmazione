#include "Message.h"

Message::Message(std::list<std::string> &t, bool imp) : important(imp) {
    auto it = text.begin();
    text.splice(it, t);
}

void Message::setText(std::list<std::string> newText) {
    text = move(newText);
}

bool Message::getImportance() const {
    return important;
}

void Message::setImportance(bool newImportance) {
    important = newImportance;
}