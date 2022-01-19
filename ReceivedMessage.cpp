#include "ReceivedMessage.h"

ReceivedMessage::ReceivedMessage(std::list<std::string> &t, std::string s, bool imp) : Message(t, imp), sender(move(s)) {
}

void ReceivedMessage::getText() {
    std::cout << sender << ": " << std::flush;
    for (auto& word : text)
        std::cout << word << " " << std::flush;
}

std::string ReceivedMessage::getSender() const {
    return sender;
}

void ReceivedMessage::setSender(std::string newSender) {
    sender = move(newSender);
}

std::string ReceivedMessage::getRecipient() const {
    return recipient;
}