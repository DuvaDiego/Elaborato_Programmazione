#include "Register.h"

Register::Register(std::string o) : owner(move(o)) {
    currentChat = nullptr;
}

Register::~Register() {
    for (auto& chat : chatList)
        chat.reset();
    currentChat.reset();
}

void Register::getChatList() const {
    RegisterView::writeChats(chatList);
}

bool Register::isEmpty() const {
    if (chatList.empty())
        return true;
    return false;
}

void Register::addInChatList(std::shared_ptr<Chat> &newChat) {
    auto it = chatList.begin();
    for (auto& chat : chatList) {
        if (chat->getUser()->isFavourite())                                                                             // una nuova chat viene inserita dopo quelle preferite
            it++;
        else
            break;
    }
    chatList.insert(it, newChat);
    currentChat = newChat;
    RegisterView::tellCurrentChat(currentChat->getName());
}

void Register::removeChat() {
    RegisterView::tellStateChat(currentChat->getName(), 0, false);

    chatList.remove(currentChat);
    currentChat.reset();
    if (!isEmpty()) {
        currentChat = chatList.front();
        RegisterView::tellCurrentChat(currentChat->getName());
    }
    else
        currentChat = nullptr;
}

void Register::searchChat(std::string& nameChat) {
    bool chatFound = false;
    for (auto& chat : chatList) {
        if (chat->getName() == nameChat) {
            currentChat = chat;
            chatFound = true;
            break;
        }
    }
    if (!chatFound)
        RegisterView::tellStateChat(nameChat, 0, false);
}

void Register::addInFavourites() {
    if (currentChat->getUser()->isFavourite()) {
        RegisterView::tellStateChat(currentChat->getName(), 1, true);
        currentChat->getUser()->setFavouritism(false);

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
        RegisterView::tellStateChat(currentChat->getName(), 1, false);
        currentChat->getUser()->setFavouritism(true);

        chatList.remove(currentChat);
        chatList.push_front(currentChat);
    }
}

void Register::blockChat() {
    if (currentChat->isBlocked()) {
        RegisterView::tellStateChat(currentChat->getName(), 2, true);
        currentChat->setBlock(false);
    } else {
        RegisterView::tellStateChat(currentChat->getName(), 2, false);
        currentChat->setBlock(true);
    }
}

std::shared_ptr<Chat> Register::getCurrent() const {
    return currentChat;
}

void Register::setCurrent(std::shared_ptr<Chat> newCurrent) {
    currentChat = move(newCurrent);
}

std::string Register::getOwner() const {
    return owner;
}