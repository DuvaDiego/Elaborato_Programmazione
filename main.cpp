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

enum class Action {
    getReg, create, remove, favourites, write, setImp, quit, noAction
};

Action getUserAction(std::string str) {  //FIXME: considerare che non tutte le azioni si possono fare sempre
    if (str[1] == '.') {
        char c = str[0];
        switch (c) {
            case 'q':
                return Action::quit;
            case 's':
                return Action::setImp;
            case 'f':
                return Action::favourites;
            case 'c':
                return Action::create;
            case 'r':
                return Action::remove;
            case 'g':
                return Action::getReg;
            default:
                return Action::noAction;
        }
    } else {
        return Action::write;
    }
}

bool doUserAction(Action &action, std::string &str) { //TODO: sviluppare ogni azione
    switch (action) {
        case Action::quit:
            return true;
        case Action::setImp:
            std::cout << "Importanza impostata." << std::endl;
            break;
        case Action::favourites:
            std::cout << "Messo tra i preferiti." << std::endl;
            break;
        case Action::create:
            std::cout << "Nuova Chat creata." << std::endl;
            break;
        case Action::remove:
            std::cout << "Chat eliminata." << std::endl;
            break;
        case Action::getReg:
            std::cout << "Registro: ..." << std::endl;
            break;
        case Action::write:
            std::cout << "Diego: " << str << std::endl;
            break;
        case Action::noAction:
            std::cout << "..." << std::endl;
            break;
    }

    return false;
}

int main() {
    //std::list<Chat*> chatList;
    //ChatRegister* WhatsApp = new ChatRegister(chatList);
    //std::unique_ptr<PrimaryUser> Diego (new PrimaryUser(WhatsApp));

    while (true) {
        std::string input;  //FIXME: se scrivo due parole mi considera due stringhe diverse
        std::cin >> input;  //capire come funziona std::cin altrimenti usare _ al posto degli spazi

        Action action = getUserAction(input);
        bool quit =doUserAction(action, input);

        if (quit)
            return 0;
    }
}
