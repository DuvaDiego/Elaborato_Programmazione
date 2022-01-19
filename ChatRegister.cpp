#include "ChatRegister.h"

ChatRegister::ChatRegister(std::string o) : owner(move(o)) {
    currentChat = nullptr;
}

ChatRegister::~ChatRegister() {
    for (auto& chat : chatList)
        delete chat;
    delete currentChat;
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

void ChatRegister::addInChatList(Chat *newChat) {
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

void ChatRegister::removeChat(Chat *current) {
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

void ChatRegister::addInFavourites(Chat *theChat) {
    if (theChat->getUser()->isFavourite()) {
        theChat->getUser()->setFavouritism(false);
        std::cout << "\nChat rimossa dai Preferiti." << std::endl; //FIXME: se tolgo la chat dai preferiti, rimane in cima alla lista
    } else {
        theChat->getUser()->setFavouritism(true);

        chatList.remove(theChat);
        chatList.push_front(theChat);

        std::cout << "\nChat aggiunta ai Preferiti." << std::endl;
    }
}

Chat *ChatRegister::getCurrent() const {
    return currentChat;
}

void ChatRegister::setCurrent(Chat *newCurrent) {
    currentChat = newCurrent;
}

std::string ChatRegister::getOwner() const {
    return owner;
}