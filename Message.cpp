#include "Message.h"

Message::Message(std::string t, bool imp) : text(move(t)), important(imp) {
}

std::string Message::getText() const {
    return text;
}

void Message::setText(std::string newText) {
    text = move(newText);
}

bool Message::getImportance() const {
    return important;
}

void Message::setImportance(bool newImportance) {
    important = newImportance;
}