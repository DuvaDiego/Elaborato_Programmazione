#include <iostream>
#include <memory>

#include "User.h"
#include "PrimaryUser.h"

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

unsigned int convertInInt(std::string s) {
    char c;
    if (s == "10")
        c = '0';
    else if (s.size() > 1)
        c = 'x';
    else
        c = s.front();
    switch (c) {
        case '1':
            return 0;
        case '2':
            return 1;
        case '3':
            return 2;
        case '4':
            return 3;
        case '5':
            return 4;
        case '6':
            return 5;
        case '7':
            return 6;
        case '8':
            return 7;
        case '9':
            return 8;
        case '0':
            return 9;
        case 'l':
            return 10;
        case 'd':
            return 11;
        default:
            return 12;
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
    } else {
        std::cout << "\n Il registro al momento e' vuoto. Digitare:" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
    }
    std::cout << "- Q| per uscire" << std::endl;
}

void writeMessages(std::shared_ptr<PrimaryUser> &user, std::list<std::string> &message, std::shared_ptr<Chat> currentChat) {
    if (!currentChat->isBlocked()) {
        if (message.front().front() != '|') {
            std::string lastWord = message.back();                                                                      // Toglie dal messaggio il simbolo '|' di chiusura
            message.pop_back();
            lastWord.pop_back();
            message.push_back(lastWord);

            if (currentChat->getWriter() == user) {
                std::shared_ptr<Message> sentMess = std::make_shared<Message>(message, user->getName(),currentChat->getUser()->getName());
                currentChat->writeMessage(sentMess);

                currentChat->setWriter(currentChat->getUser());
            } else {
                std::shared_ptr<Message> receivedMess = std::make_shared<Message>(message,currentChat->getUser()->getName(), user->getName());
                currentChat->writeMessage(receivedMess);

                currentChat->setWriter(user);
            }
        }
    }
    else
        std::cout << "\nLa chat '" << currentChat->getName() << "_' e' bloccata. Non puoi scriverci messaggi." << std::endl;
}


bool doUserAction(std::shared_ptr<PrimaryUser> &user, Action &action, std::shared_ptr<ChatRegister> reg, std::list<std::string> &message) { //TODO: aggiungere ricerca e cancellazione di un messaggio nella chat
    if (reg->getCurrent() != nullptr && reg->getCurrent()->getWriter() != user) {                                       // quando è il turno dell'altra persona parlare non si può eseguire alcuna azione
        writeMessages(user, message, reg->getCurrent());
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
            case Action::noAction:
                break;
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

                            reg->searchChat(nameChat);
                            std::cout << "\nChat '" << reg->getCurrent()->getName() << "_' selezionata." << std::endl;  // se la chat che si sta cercando non è nel registro
                                                                                                                        // si rimane nella chat dove ci si trovava
                            tellInstructions(reg);
                            reg->getCurrent()->getChatMessages();
                            if (reg->getCurrent()->isBlocked())
                                std::cout << "La Chat e' bloccata." << std::endl;
                            break;
                        }
                        case Action::remove: {
                            if (!reg->isEmpty()) {
                                reg->removeChat();

                                tellInstructions(reg);
                                if (reg->getCurrent() != nullptr) {
                                    reg->getCurrent()->getChatMessages();
                                }
                            }
                            break;
                        }
                        case Action::favourites: {
                            reg->addInFavourites();
                            break;
                        }
                        case Action::block: {
                            reg->blockChat();
                            break;
                        }
                        case Action::setImp: {
                            bool req;
                            do {
                                std::string s;
                                std::cout << "\nInserire:" << std::endl;
                                std::cout << "- un numero da 1 a 10, per rendere un messaggio importante" << std::endl;
                                std::cout << "- 'l', per ottenere la lista dei messaggi importanti" << std::endl;
                                std::cout << "- 'd', per svuotare la lista dei messaggi importanti" << std::endl;
                                std::cin >> s;

                                unsigned int n = convertInInt(s);
                                req = reg->getCurrent()->setMessImportance(n);
                            } while (req);

                            break;
                        }
                        case Action::write: {
                            writeMessages(user, message, reg->getCurrent());
                             break;
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    std::shared_ptr<ChatRegister> WhatsApp(new ChatRegister());
    std::shared_ptr<PrimaryUser> Diego = std::make_shared<PrimaryUser>(WhatsApp);

    tellInstructions(WhatsApp);
    while (true) {
        std::list<std::string> message;
        std::string input;
        bool stop = false;

        while (!stop) {                                                                                                 // Il ciclo while permette la scrittura di una frase
            std::cin >> input;                                                                                          // std::cin permette di scrivere una parola alla volta,
            message.push_back(input);                                                                                   // altrimenti genera due azioni consecutive.
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
