#include "SentMessage.h"

SentMessage::SentMessage(std::string t, bool imp, SecondaryUser *r, std::string s) : Message(move(t), imp), recipient(r), sender(move(s)) {
}

std::string SentMessage::getSender() const {
    return sender;
}

SecondaryUser *SentMessage::getRecipient() const {
    return recipient;
}

void SentMessage::setRecipient(SecondaryUser *newRecipient) {
    recipient = newRecipient;
}
