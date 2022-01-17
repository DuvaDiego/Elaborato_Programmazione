#include "ChatRegister.h"

ChatRegister::ChatRegister(std::list<Chat *> list, std::string o) : chatList(move(list)), owner(move(o)) {
}

ChatRegister::~ChatRegister() {
    for (auto& chat : chatList)
        delete chat;
}

bool ChatRegister::getChatList() const {
    if (isEmpty()) {
        return false;
    }
    else {
        std::cout << "\nRegistro Chat:" << std::endl;
        for (auto &chat: chatList)
            std::cout << "- " << chat->getName() << std::endl; //TODO: aggiungere la caratteristica delle chat preferite che compaiono in cima al registro
        return true;
    }
}

bool ChatRegister::isEmpty() const {
    if (chatList.empty())
        return true;
    return false;
}

void ChatRegister::addInChatList(Chat *newChat) {
    chatList.push_front(newChat);
    std::cout << "\nChat '" << newChat->getName() << "_' aggiunta al registro." << std::endl;
}

Chat* ChatRegister::removeChat(Chat *aChat) {
    chatList.remove(aChat);
    delete aChat;
    return chatList.front();
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