#ifndef ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
#define ELABORATO_PROGRAMMAZIONE_CHATVIEW_H

#include <iostream>
#include <memory>
#include "Message.h"

class ChatView {
public:
    ChatView() = default;
    ~ChatView() = default;

    static void writeMessage(std::shared_ptr<Message> &m);
    static void getMessages(std::list<std::shared_ptr<Message>> list, bool parameter);

    static std::string writeResearchCommand();
    static void correspondingMessage(int quantity, std::list<std::shared_ptr<Message>> mFound);

    static std::string writeImportanceCommand();
    static void sayImportance(int parameter, unsigned int messageQuantity);
};


#endif //ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
