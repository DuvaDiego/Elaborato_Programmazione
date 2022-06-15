#include "Register.h"

Register::Register(std::string o) : owner(move(o)) {
    currentChat = nullptr;
    chatQuantity = 0;
}

Register::~Register() {
    for (auto& chat : chatList)
        chat.reset();
    currentChat.reset();
}

std::shared_ptr<Chat> Register::getChat(int number) const {
    auto it = chatList.begin();
    int i = 0;
    while (i < number) {
        it++;
        i++;
    }
    return it.operator*();
}

int Register::getChatQuantity() const {
    return chatQuantity;
}

bool Register::isEmpty() const {
    if (chatQuantity == 0)
        return true;
    return false;
}

void Register::addInChatList(std::shared_ptr<Chat> &newChat) {
    auto it = chatList.begin();
    for (auto& chat : chatList) {
        if (chat->getUser()->isFavourite())                                                                             // Una nuova chat viene inserita dopo quelle preferite.
            it++;
        else
            break;
    }
    chatList.insert(it, newChat);
    currentChat = newChat;
    chatQuantity++;
}

void Register::removeChat() {
    chatList.remove(currentChat);
    currentChat.reset();
    if (!isEmpty()) {
        currentChat = chatList.front();
    }
    else
        currentChat = nullptr;
    chatQuantity--;
}

bool Register::searchChat(std::string& nameChat) {
    for (auto& chat : chatList) {
        if (chat->getName() == nameChat) {
            currentChat = chat;
            return true;
        }
    }
    return false;
}

void Register::addInFavourites() {
    if (currentChat->getUser()->isFavourite()) {
        currentChat->getUser()->setFavouritism(false);

        chatList.remove(currentChat);
        auto it = chatList.begin();
        for (auto &chat: chatList) {
            if (chat->getUser()->isFavourite())                                                                         // Una chat rimossa dai preferiti va portata in coda all'ultima chat preferita.
                it++;
            else
                break;
        }
        chatList.insert(it, currentChat);
    } else {
        currentChat->getUser()->setFavouritism(true);

        chatList.remove(currentChat);
        chatList.push_front(currentChat);
    }
}

void Register::blockChat() {
    if (currentChat->isBlocked()) {
        currentChat->setBlock(false);
    } else {
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