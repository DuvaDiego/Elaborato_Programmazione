#ifndef ELABORATO_PROGRAMMAZIONE_CHAT_H
#define ELABORATO_PROGRAMMAZIONE_CHAT_H

#include <iostream>
#include <memory>
#include "Message.h"
#include "SecondaryUser.h"
#include "ChatView.h"

#define Max 50

class Chat {
public:
    Chat(std::shared_ptr<SecondaryUser> u, std::shared_ptr<User> w);
    ~Chat();

    std::string getName() const;
    void setName(std::string newName);

    bool isBlocked() const;
    void setBlock(bool newSetup);

    void getChatMessages() const;
    void writeMessage(std::shared_ptr<Message>& newMessage);
    void searchMessages(std::string& word);
    bool setMessImportance(unsigned int n);

    std::shared_ptr<SecondaryUser> getUser() const;
    void setUser(std::shared_ptr<SecondaryUser> newUser);

    std::shared_ptr<User> getWriter() const;
    void setWriter(std::shared_ptr<User> newWriter);

private:
    std::string nameChat;
    bool blocked;
    std::list<std::shared_ptr<Message>> savedMessage;
    std::list<std::shared_ptr<Message>> messagesList;
    std::list<std::shared_ptr<Message>> messagesFound;
    int maxSavedMessage = Max;
    std::shared_ptr<SecondaryUser> user;
    std::shared_ptr<User> writer;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHAT_H
