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
                char ch = (char) 3;
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
        if (chat->getUser()->isFavourite())
            it++;
        else
            break;
    }
    chatList.insert(it, newChat);
    currentChat = newChat;
    std::cout << "\nSei nella chat '" << newChat->getName() << "_' appena aggiunta al registro." << std::endl;
}

void ChatRegister::removeChat(std::shared_ptr<Chat> &current) {
    chatList.remove(current);
    if (!isEmpty())
        currentChat = chatList.front();
    else
        currentChat = nullptr;
}

bool ChatRegister::searchChat(std::string& nameChat) {
    for (auto& chat : chatList) {
        if (chat->getName() == nameChat) {
            currentChat = chat;
            return true;
        }
    }
    return false;
}

void ChatRegister::addInFavourites() {
    if (currentChat->getUser()->isFavourite()) {
        currentChat->getUser()->setFavouritism(false);
        std::cout << "\nChat rimossa dai Preferiti." << std::endl;

        chatList.remove(currentChat);
        auto it = chatList.begin();
        for (auto &chat: chatList) {
            if (chat->getUser()->isFavourite())
                it++;
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