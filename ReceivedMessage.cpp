#include "ReceivedMessage.h"

ReceivedMessage::ReceivedMessage(std::list<std::string> &t, std::string s, bool imp, std::string r) : Message(t, imp), sender(move(s)), recipient(move(r)) {
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