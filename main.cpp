#include <iostream>
#include <memory>

#include "User.h"
#include "PrimaryUser.h"
#include "SentMessage.h"
#include "ReceivedMessage.h"

enum class Action {
    getReg, create, remove, select, favourites, block, write, setImp, quit, noAction
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
            case 'B':
                return Action::block;
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

unsigned int convertChar(std::string s) {
    char c = s.front();
    switch (c) {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'i':
            return 10;
        default:
            return 11;
    }
}

void tellInstructions(std::shared_ptr<ChatRegister> &reg) {
    if (!reg->isEmpty()) {
        std::cout << "\nDigitare:" << std::endl;
        std::cout << "- R| per la lista chat" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- S| per selezionare una chat" << std::endl;
        std::cout << "- D| per eliminare l'attuale chat" << std::endl;
        std::cout << "- B| per bloccare/sbloccare l'attuale chat" << std::endl;
        std::cout << "- F| per impostare la preferenza dell'attuale chat" << std::endl;
        std::cout << "- I| per impostare l'importanza di un messaggio" << std::endl;
        std::cout << "- 'messaggio'| per scrivere un messaggio nella chat" << std::endl;
        std::cout << "- Q| per uscire" << std::endl;
    } else {
        std::cout << "\n Il registro al momento e' vuoto. Digitare:" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- Q| per ucire" << std::endl;
    }
}

void writeMessages(std::shared_ptr<PrimaryUser> &user, std::list<std::string> &message, std::shared_ptr<Chat> currentChat) {
    if (message.front().front() != '|') {
        std::string lastWord = message.back();
        message.pop_back();
        lastWord.pop_back();
        message.push_back(lastWord);

        if(currentChat->getWriter() == user) {
            std::shared_ptr<Message> sentMess = std::make_shared<SentMessage>(message, currentChat->getUser()->getName());
            currentChat->writeMessage(sentMess);

            std::shared_ptr<SecondaryUser> newWriter = currentChat->getUser();
            currentChat->setWriter(newWriter);
        } else {
            std::shared_ptr<Message> receivedMess = std::make_shared<ReceivedMessage>(message, currentChat->getUser()->getName());
            currentChat->writeMessage(receivedMess);

            currentChat->setWriter(user);
        }
    }
}


bool doUserAction(std::shared_ptr<PrimaryUser> &user, Action &action, std::shared_ptr<ChatRegister> reg, std::list<std::string> &message) {
    if (reg->getCurrent() != nullptr && reg->getCurrent()->getWriter() != user) {
        if (!reg->getCurrent()->isBlocked())
            writeMessages(user, message, reg->getCurrent());
        else
            std::cout << "\nLa chat '" << reg->getCurrent()->getName() << "_' e' bloccata. Non puoi scriverci messaggi." << std::endl;
    } else {
        switch (action) {
            case Action::create: {
                std::cout << "\nInserire nome utente della persona con cui vuoi parlare:" << std::flush;
                std::string person;
                std::cin >> person;
                std::shared_ptr<SecondaryUser> aPerson = std::make_shared<SecondaryUser>(person);

                std::shared_ptr<Chat> aChat = std::make_shared<Chat>(aPerson, user);
                reg->addInChatList(aChat);

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
                                std::cout << "\nLa Chat '" << nameChat << "_' non esiste nel registro." << std::flush;
                            std::cout << "\nChat '" << reg->getCurrent()->getName() << "_' selezionata." << std::endl;

                            tellInstructions(reg);
                            reg->getCurrent()->getChatMessages();
                            if (reg->getCurrent()->isBlocked())
                                std::cout << "La Chat e' bloccata." << std::endl;

                            break;
                        }
                        case Action::remove: {
                            if (!reg->isEmpty()) {
                                std::shared_ptr<Chat> currentChat = reg->getCurrent();
                                std::cout << "\nChat '" << currentChat->getName() << "_' eliminata." << std::endl;

                                reg->removeChat(currentChat);
                                currentChat.reset();

                                if (reg->getCurrent() != nullptr) {
                                    std::cout << "\nSei nella chat '" << reg->getCurrent()->getName() << "_'." << std::endl;
                                    tellInstructions(reg);
                                    reg->getCurrent()->getChatMessages();
                                } else
                                    tellInstructions(reg);
                            }
                            break;
                        }
                        case Action::favourites: {
                            std::shared_ptr<Chat> currentChat = reg->getCurrent();
                            reg->addInFavourites(currentChat);
                            break;
                        }
                        case Action::block: {
                            if (reg->getCurrent()->isBlocked()) {
                                reg->getCurrent()->setBlock(false);
                                std::cout << "\nLa chat '" << reg->getCurrent()->getName() << "_' e' stata sbloccata." << std::endl;
                            } else {
                                reg->getCurrent()->setBlock(true);
                                std::cout << "\nLa chat '" << reg->getCurrent()->getName() << "_' e' stata bloccata." << std::endl;
                            }
                            break;
                        }
                        case Action::setImp: {
                            bool req;
                            do {
                                std::string s;
                                std::cout
                                        << "\nInserire il n. del messaggio (0-9) o i per la lista dei messaggi importanti:"
                                        << std::flush;
                                std::cin >> s;

                                unsigned int n = convertChar(s);
                                if (n >= 0 && n < 10) {
                                    reg->getCurrent()->setMessImportance(n);
                                    req = false;
                                } else if (n == 10) {
                                    reg->getCurrent()->getImportantMessages();
                                    req = false;
                                } else {
                                    std::cout << "n. non valido." << std::endl;
                                    req = true;
                                }
                            } while (req);

                            break;
                        }
                        case Action::write: {
                            if (!reg->getCurrent()->isBlocked())
                                writeMessages(user, message, reg->getCurrent());
                            else
                                std::cout << "\nLa chat '" << reg->getCurrent()->getName() << "_' e' bloccata. Non puoi scriverci messaggi." << std::endl;
                            break;
                        }
                        case Action::noAction:
                            break;
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    std::shared_ptr<ChatRegister> WhatsApp(new ChatRegister());
    //ChatRegister* WhatsApp = new ChatRegister();
    std::shared_ptr<PrimaryUser> Diego = std::make_shared<PrimaryUser>(WhatsApp);

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
            Diego.reset();
            return 0;
        }
    }
}
