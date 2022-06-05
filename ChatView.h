#ifndef ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
#define ELABORATO_PROGRAMMAZIONE_CHATVIEW_H

#include <iostream>
#include <memory>
#include "Message.h"

#define Max 50

class ChatView {
public:
    ChatView() = default;
    ~ChatView() = default;

    static void writeMessage(std::shared_ptr<Message> &m);
    static void getMessages(std::list<std::shared_ptr<Message>> list, bool parameter);

    static std::string writeResearchCommand();
    static void correspondingMessage(int quantity, std::list<std::shared_ptr<Message>> mFound);

    static std::string writeGeneralCommand();
    static void selectionCase(int parameter, unsigned int messageQuantity);
    static std::string writeImportanceCommand();
};


#endif //ELABORATO_PROGRAMMAZIONE_CHATVIEW_H
