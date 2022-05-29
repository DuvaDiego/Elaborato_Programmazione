#ifndef ELABORATO_PROGRAMMAZIONE_REGISTER_H
#define ELABORATO_PROGRAMMAZIONE_REGISTER_H

#include <iostream>
#include <list>
#include "Chat.h"
#include "RegisterView.h"

#define regOwner "Diego"

class Register {
public:
    explicit Register(std::string o = regOwner);
    ~Register();

    void getChatList() const;
    bool isEmpty() const;
    void addInChatList(std::shared_ptr<Chat>& newChat);
    void removeChat();
    void searchChat(std::string& nameChat);
    void addInFavourites();
    void blockChat();

    std::shared_ptr<Chat> getCurrent() const;
    void setCurrent(std::shared_ptr<Chat> newCurrent);

    std::string getOwner() const;

private:
    std::list<std::shared_ptr<Chat>> chatList;
    std::shared_ptr<Chat> currentChat;
    std::string owner;
};


#endif //ELABORATO_PROGRAMMAZIONE_REGISTER_H
