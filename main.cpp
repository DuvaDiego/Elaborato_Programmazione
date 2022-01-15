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
    getReg, create, remove, select, favourites, write, setImp, quit, noAction
};

Action getUserAction(std::string firstWord) {  //FIXME: considerare che non tutte le azioni si possono fare sempre
    if (firstWord[1] == '|') {
        char c = firstWord[0];
        switch (c) {
            case 'Q':
                return Action::quit;
            case 'I':
                return Action::setImp;
            case 'F':
                return Action::favourites;
            case 'C':
                return Action::create;
            case 'D':
                return Action::remove;
            case 'S':
                return Action::select;
            case 'R':
                return Action::getReg;
            default:
                return Action::noAction;
        }
    } else {
        return Action::write;
    }
}

bool doUserAction(Action &action, std::list<std::string> &message) { //TODO: sviluppare ogni azione
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
        case Action::select:
            std::cout << "Chat selezionata." << std::endl;
            break;
        case Action::getReg:
            std::cout << "Registro: ..." << std::endl;
            break;
        case Action::write: {
            if (message.front().front() != '|') {
                std::string lastWord = message.back();
                message.pop_back();
                lastWord.pop_back();
                message.push_back(lastWord);

                std::cout << "Diego: " << std::flush;
                for (auto &word: message) {
                    std::cout << word << ' ' << std::flush;
                    if (word.back() == '|')
                        break;
                }
                std::cout << std::endl;
            }
            break;
        }
        case Action::noAction:
            std::cout << "..." << std::endl;
            break;
    }

    return false;
}

void tellInstructions(ChatRegister* reg) {
    bool notEmpty = reg->getChatList();
    if (notEmpty) {
        std::cout << "Digitare:" << std::endl;
        std::cout << "- R| per la lista chat" << std::endl;
        std::cout << "- S| per selezionare una chat" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- D| per eliminare una chat" << std::endl;
        std::cout << "- F| per mettere una chat tra i preferiti" << std::endl;
        std::cout << "- Q| per uscire" << std::endl;
    }  //TODO: aggiungere istruzioni per quando ci si trova dentro una chat
}

int main() {
    std::list<Chat*> chatList;
    ChatRegister* WhatsApp = new ChatRegister(chatList);
    std::unique_ptr<PrimaryUser> Diego (new PrimaryUser(WhatsApp));

    tellInstructions(WhatsApp);
    while (true) {
        std::list<std::string> message;
        std::string input;
        bool stop = false;

        while (!stop) {
            std::cin >> input;
            message.push_back(input);
            if (input.back() == '|')
                stop = true;
        }

        Action action = getUserAction(message.front());
        bool quit =doUserAction(action, message);

        if (quit)
            return 0;
    }
}
