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
        for (auto &chat: chatList)
            std::cout << "- " << chat->getName() << std::endl; //TODO: aggiungere la caratteristica delle chat preferite che compaiono in cima al registro

}

bool ChatRegister::isEmpty() const {
    if (chatList.empty())
        return true;
    return false;
}

void ChatRegister::addInChatList(Chat *newChat) {
    chatList.push_front(newChat);
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

Chat *ChatRegister::getCurrent() const {
    return currentChat;
}

void ChatRegister::setCurrent(Chat *newCurrent) {
    currentChat = newCurrent;
}

std::string ChatRegister::getOwner() const {
    return owner;
}