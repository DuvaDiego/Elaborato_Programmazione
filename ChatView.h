#ifndef ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
#define ELABORATO_PROGRAMMAZIONE_CHATVIEW_H

#include <iostream>
#include <memory>
#include "Chat.h"
#include "Message.h"

class ChatView {
public:
    explicit ChatView(std::shared_ptr<Chat> c);
    ~ChatView() = default;

    void writeTextMessage(std::shared_ptr<Message> &m);
    void getAllMessages();
    void getSavedMessages();
    void getFoundMessages();

    std::string chooseGenCommand();
    std::string chooseResCommand();
    std::string chooseImpCommand();

    void selectCase(int n, int parameter);

    void associateChat(std::shared_ptr<Chat>& newChat);

private:
    std::shared_ptr<Chat> aChat;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
