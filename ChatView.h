#ifndef ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
#define ELABORATO_PROGRAMMAZIONE_CHATVIEW_H

#include <iostream>
#include <memory>
#include "Message.h"
#include "Chat.h"

class ChatView {
public:
    explicit ChatView(std::shared_ptr<Chat> c);
    ~ChatView() = default;

    void writeMessage(std::shared_ptr<Message> &m);
    void getMessages();

    std::string writeResearchCommand();
    void getFoundMessages();

    std::string writeGeneralCommand();
    void selectionCase(int parameter, unsigned int messageQuantity);
    std::string writeImportanceCommand();

    void associateChat(std::shared_ptr<Chat> newChat);

private:
    std::shared_ptr<Chat> aChat;
};


#endif //ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
