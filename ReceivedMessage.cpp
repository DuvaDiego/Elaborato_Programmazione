#include "ReceivedMessage.h"

ReceivedMessage::ReceivedMessage(std::string t, bool imp, SecondaryUser *s, std::string r) : Message(move(t), imp), sender(s), recipient(move(r)) {
}

SecondaryUser *ReceivedMessage::getSender() const {
    return sender;
}

void ReceivedMessage::setSender(SecondaryUser *newSender) {
    sender = newSender;
}

std::string ReceivedMessage::getRecipient() const {
    return recipient;
}