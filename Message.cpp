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

bool Message::searchWord(std::string word) const {
    for (auto& w : text) {
        if(isEgual(word, w))
            return true;
    }
    return false;
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

bool Message::isEgual(std::string word, std::string model) {
    std::string capitalModel = model;                                                                                   // variante del modello con lettera maiuscola
    int iMaiusc = (int) model.front() - 32;
    char lMaiusc = (char) iMaiusc;
    capitalModel.replace(0, 1, &lMaiusc);
    capitalModel.erase(1, 3);

    std::string lowercaseModel = model;                                                                                 // variante del modello con lettera minuscola
    int iMinusc = (int) model.front() + 32;
    char lMinusc = (char) iMinusc;
    lowercaseModel.replace(0, 1, &lMinusc);
    lowercaseModel.erase(1, 3);

    std::string simpleModel = model;                                                                                    // variante del modello con punteggiatura in fondo
    simpleModel.pop_back();

    std::string simpleCapitalModel = capitalModel;                                                                      // variante del modello con lettera maiuscola e punteggiatura in fondo
    simpleCapitalModel.pop_back();

    std::string simpleLowercaseModel = lowercaseModel;                                                                  // variante del modello con lettera minuscola e punteggiatura in fondo
    simpleLowercaseModel.pop_back();

    std::string simpleWord = word;
    simpleWord.pop_back();

    if(word == model || word == capitalModel || word == lowercaseModel || word == simpleModel || word == simpleCapitalModel || word == simpleLowercaseModel)
        return true;
    else if (simpleWord == model || simpleWord == capitalModel || simpleWord == lowercaseModel || simpleWord == simpleModel || simpleWord == simpleCapitalModel || simpleWord == simpleLowercaseModel)
        return true;
    else
        return false;
}