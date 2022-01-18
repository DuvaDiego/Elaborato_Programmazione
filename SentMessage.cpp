#include "SentMessage.h"

SentMessage::SentMessage(std::list<std::string> &t, std::string r, bool imp) : Message(t, imp), recipient(move(r)) {

}

void SentMessage::getText() const {
    std::cout << sender << ": " << std::flush;
    for (auto& word : text)
        std::cout << word << " " << std::flush;
}

std::string SentMessage::getSender() const {
    return sender;
}

std::string SentMessage::getRecipient() const {
    return recipient;
}

void SentMessage::setRecipient(std::string newRecipient) {
    recipient = move(newRecipient);
}
