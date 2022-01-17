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

Action getUserAction(std::string firstWord) {
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

void tellInstructions(ChatRegister* reg) {
    bool empty = reg->isEmptyList();
    if (!empty) {
        std::cout << "\nDigitare:" << std::endl;
        std::cout << "- R| per la lista chat" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- S| per selezionare una chat" << std::endl;
        std::cout << "- D| per eliminare una chat" << std::endl;
        std::cout << "- F| per mettere una chat tra i preferiti" << std::endl;
        std::cout << "- I| per mettere tra i messaggi importanti un messaggio" << std::endl;
        std::cout << "- 'messaggio'| per scrivere un messaggio nella chat" << std::endl;
        std::cout << "- Q| per uscire" << std::endl;

        //TODO: aggiungere nome della Chat in cui ci si trova
    }
}

bool doUserAction(User* user, Action &action, ChatRegister* reg, std::list<std::string> &message) { //TODO: sviluppare ogni azione
    switch (action) {
        case Action::create: {
            std::cout << "\nInserire nome utente della persona con cui vuoi parlare:" << std::flush;
            std::string person;
            std::cin >> person;
            SecondaryUser* aPerson = new SecondaryUser(person);

            Chat* aChat = new Chat(aPerson);
            reg->addInChatList(aChat);

            tellInstructions(reg);
            break;
        }
        case Action::quit: {
            std::cout << "\nProgramma chiuso, registro eliminato." << std::endl;
            return true;
        }
        default: {
            bool empty = reg->isEmptyList();
            if (!empty) {
                switch (action) {
                    case Action::getReg: {
                        reg->getChatList();
                        break;
                    }
                    case Action::select:
                        std::cout << "Chat selezionata." << std::endl;
                        break;
                    case Action::remove:
                        std::cout << "Chat eliminata." << std::endl;
                        break;
                    case Action::favourites:
                        std::cout << "Messo tra i preferiti." << std::endl;
                        break;
                    case Action::setImp:
                        std::cout << "Importanza impostata." << std::endl;
                        break;
                    case Action::write: {
                        if (message.front().front() != '|') {
                            std::string lastWord = message.back();
                            message.pop_back();
                            lastWord.pop_back();
                            message.push_back(lastWord);

                            std::cout << user->getName() << ": " << std::flush;
                            for (auto &word: message) {
                                std::cout << word << ' ' << std::flush;
                            }
                            std::cout << std::endl;
                        }
                        break;
                    }
                    case Action::noAction:
                        std::cout << "..." << std::endl;
                        break;
                }
            }
        }
    }
    return false;
}

int main() {
    std::list<Chat*> chatList;
    ChatRegister* WhatsApp = new ChatRegister(chatList);
    PrimaryUser* Diego (new PrimaryUser(WhatsApp));

    tellInstructions(WhatsApp);
    while (true) {
        std::list<std::string> message;
        std::string input;
        bool stop = false;

        //TODO: impostare sistema di chatting alternato tra le due persone
        while (!stop) {
            std::cin >> input;
            message.push_back(input);
            if (input.back() == '|')
                stop = true;
        }

        Action action = getUserAction(message.front());
        bool quit =doUserAction(Diego ,action, WhatsApp, message);

        if (quit)
            return 0;
    }
}
