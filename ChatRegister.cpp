#include "ChatRegister.h"

ChatRegister::ChatRegister(std::string o) : owner(move(o)) {
    currentChat = nullptr;
}

ChatRegister::~ChatRegister() {
    for (auto& chat : chatList)
        chat.reset();
    currentChat.reset();
}

void ChatRegister::getChatList() const {
    std::cout << "\nRegistro Chat:" << std::endl;
        for (auto &chat: chatList) {
            std::cout << "- " << chat->getName() << std::flush;
            if (chat->getUser()->isFavourite()) {
                char ch = (char) 3;                                                                                     // aggiunge un cuore dopo il nome della chat
                std::cout << "  " << ch << std::flush;
            }
            std::cout << std::endl;
        }
}

bool ChatRegister::isEmpty() const {
    if (chatList.empty())
        return true;
    return false;
}

void ChatRegister::addInChatList(std::shared_ptr<Chat> &newChat) {
    auto it = chatList.begin();
    for (auto& chat : chatList) {
        if (chat->getUser()->isFavourite())                                                                             // una nuova chat viene inserita dopo quelle preferite
            it++;
        else
            break;
    }
    chatList.insert(it, newChat);
    currentChat = newChat;
    std::cout << "\nSei nella chat '" << newChat->getName() << "_' appena aggiunta al registro." << std::endl;
}

void ChatRegister::removeChat() {
    std::cout << "\nChat '" << currentChat->getName() << "_' eliminata." << std::endl;

    chatList.remove(currentChat);
    currentChat.reset();
    if (!isEmpty()) {
        currentChat = chatList.front();
        std::cout << "\nSei nella chat '" << currentChat->getName() << "_'." << std::endl;
    }
    else
        currentChat = nullptr;
}

void ChatRegister::searchChat(std::string& nameChat) {
    bool chatFound = false;
    for (auto& chat : chatList) {
        if (chat->getName() == nameChat) {
            currentChat = chat;
            chatFound = true;
        }
    }
    if (!chatFound)
        std::cout << "\nLa Chat '" << nameChat << "_' non esiste nel registro." << std::flush;
}

void ChatRegister::addInFavourites() {
    if (currentChat->getUser()->isFavourite()) {
        currentChat->getUser()->setFavouritism(false);
        std::cout << "\nChat rimossa dai Preferiti." << std::endl;

        chatList.remove(currentChat);
        auto it = chatList.begin();
        for (auto &chat: chatList) {
            if (chat->getUser()->isFavourite())                                                                         // una chat rimossa dai preferiti va portata
                it++;                                                                                                   // in coda all'ultima chat preferita
            else
                break;
        }
        chatList.insert(it, currentChat);
    } else {
        currentChat->getUser()->setFavouritism(true);

        chatList.remove(currentChat);
        chatList.push_front(currentChat);

        std::cout << "\nChat aggiunta ai Preferiti." << std::endl;
    }
}

void ChatRegister::blockChat() {
    if (currentChat->isBlocked()) {
        currentChat->setBlock(false);
        std::cout << "\nLa chat '" << currentChat->getName() << "_' e' stata sbloccata." << std::endl;
    } else {
        currentChat->setBlock(true);
        std::cout << "\nLa chat '" << currentChat->getName() << "_' e' stata bloccata." << std::endl;
    }
}

std::shared_ptr<Chat> ChatRegister::getCurrent() const {
    return currentChat;
}

void ChatRegister::setCurrent(std::shared_ptr<Chat> newCurrent) {
    currentChat = move(newCurrent);
}

std::string ChatRegister::getOwner() const {
    return owner;
}