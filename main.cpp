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
    if (!reg->isEmpty()) {
        std::cout << "\nDigitare:" << std::endl;
        std::cout << "- R| per la lista chat" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- S| per selezionare una chat" << std::endl;
        std::cout << "- D| per eliminare l'attuale chat" << std::endl;
        std::cout << "- F| per mettere una chat tra i preferiti" << std::endl;
        std::cout << "- I| per mettere tra i messaggi importanti un messaggio" << std::endl;
        std::cout << "- 'messaggio'| per scrivere un messaggio nella chat" << std::endl;
        std::cout << "- Q| per uscire" << std::endl;
    } else {
        std::cout << "\n Il registro al momento e' vuoto. Digitare:" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- Q| per ucire" << std::endl;
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
            aChat->setWriter(user);

            tellInstructions(reg);
            break;
        }
        case Action::quit: {
            std::cout << "\nProgramma chiuso, registro eliminato." << std::endl;
            return true;
        }
        default: {
            if (!reg->isEmpty()) {
                switch (action) {
                    case Action::getReg: {
                        reg->getChatList();
                        break;
                    }
                    case Action::select: {
                        reg->getChatList();
                        std::cout << "Seleziona una Chat dal registro, scrivendo il suo nome:" << std::flush;
                        std::string nameChat;
                        std::cin >> nameChat;

                        bool chatFound = reg->searchChat(nameChat);
                        if (!chatFound)
                            std::cout << "\nLa chat '" << nameChat << "_' non esiste nel registro." << std::flush;
                        std::cout << "\nChat '" << reg->getCurrent()->getName() << "_' selezionata." << std::endl;

                        tellInstructions(reg);
                        reg->getCurrent()->getChatMessages();

                        break;
                    }
                    case Action::remove: {
                        if(!reg->isEmpty()) {
                            Chat* current = reg->getCurrent();
                            std::cout << "\nChat '" << current->getName() << "_' eliminata." << std::endl;

                            reg->removeChat(current);
                            delete current;

                            if (reg->getCurrent() != nullptr)
                                std::cout << "\nSei nella chat '" << reg->getCurrent()->getName() << "_'." << std::endl;
                        }

                        tellInstructions(reg);
                        break;
                    }
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

                            //FIXME: quando risponde l'altra persona l'unica azione possibile da fare è scrivere
                            if(reg->getCurrent()->getWriter() == user) {
                                SentMessage* sentMess = new SentMessage(message, reg->getCurrent()->getUser()->getName());
                                reg->getCurrent()->writeMessage(sentMess);

                                SecondaryUser* newWriter = reg->getCurrent()->getUser();
                                reg->getCurrent()->setWriter(newWriter);
                            } else {
                                ReceivedMessage* receivedMess = new ReceivedMessage(message, reg->getCurrent()->getUser()->getName());
                                reg->getCurrent()->writeMessage(receivedMess);

                                reg->getCurrent()->setWriter(user);
                            }
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
    ChatRegister* WhatsApp = new ChatRegister();
    PrimaryUser* Diego = new PrimaryUser(WhatsApp);

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
        bool quit =doUserAction(Diego ,action, WhatsApp, message);

        if (quit) {
            delete Diego;
            return 0;
        }
    }
}
