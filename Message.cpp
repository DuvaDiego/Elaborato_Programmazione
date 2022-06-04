#include "Message.h"

Message::Message(std::list<std::string> &t, std::string s, std::string r, bool imp, bool read) : sender(move(s)), recipient(move(r)),  important(imp), read(read) {
    auto it = text.begin();
    text.splice(it, t);
}

void Message::getText() {
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

bool Message::isRead() const {
    return read;
}

void Message::setRead(bool newRead) {
    read = newRead;
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