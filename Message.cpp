#include "Message.h"

Message::Message(std::list<std::string> &t, bool imp) : important(imp) {
    auto it = text.begin();
    text.splice(it, t);
}

Message::Message(std::list<std::string> &t, std::string s, std::string r, bool imp) : sender(move(s)), recipient(move(r)),  important(imp) {
    auto it = text.begin();
    text.splice(it, t);
}

void Message::getText() {
    std::cout << sender << ": " << std::flush;
    for (auto& word : text)
        std::cout << word << " " << std::flush;
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

std::string Message::getSender() const {
    return sender;
}

void Message::setSender(std::string newSender) {
    sender = move(newSender);
}

std::string Message::getRecipient() const {
    return recipient;
}

void Message::setRecipient(std::string newRecipient) {
    recipient = move(newRecipient);
}