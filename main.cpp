#include <iostream>
#include <memory>

#include "User.h"
#include "PrimaryUser.h"
#include "SecondaryUser.h"
#include "ChatRegister.h"
#include "Chat.h"
#include "Message.h"
#include "SentMessage.h"
#include "ReceivedMessage.h"

int main() {
    std::list<Chat*> chatList;
    ChatRegister* WhatsApp = new ChatRegister(chatList);
    std::unique_ptr<PrimaryUser> Diego (new PrimaryUser(WhatsApp));

    char c;
    while (std::cin.get(c)) {
        std::cin.ignore(100, '\n');
        switch (c) {
            case 'Q':
                std::cout << "Non Hai detto:" << c <<std::endl;
                return 0;
            case 'c':
                std::cout << "Hai detto:" << c <<std::endl;
                return 0;
            default:
                return 0;
        }
    }
}
