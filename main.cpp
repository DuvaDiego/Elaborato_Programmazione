#include <iostream>
#include <memory>

#include "User.h"
#include "PrimaryUser.h"

enum class Action {
    getReg, create, remove, select, favourites, block, write, find, setImp, quit, noAction
};

Action getUserAction(std::string firstWord) {
    if (firstWord[1] == '|') {
        char c = firstWord[0];
        switch (c) {
            case 'Q':
                return Action::quit;
            case 'F':
                return Action::find;
            case 'I':
                return Action::setImp;
            case 'P':
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
    int i = Max + 2;                                                                                                         // caso valore non valido
    if (s.size() <= 2) {
        unsigned char c0 = s.back();
        unsigned char c1 = '0';
        if (s.size() == 2)
            c1 = s.front();

        int i0 = (int) c0;
        int i1 = (int) c1;

        if ((i0 >= 48 && i0 <= 57) && (i1 >= 48 && i1 <= 57)) {                                                         // caso scelta tra 1 e Max
            i0 -= 48;
            i1 -= 48;

            i = i1 * 10 + i0 - 1;

            if (i >= Max)                                                                                               // caso scelta tra Max + 1 e 99
                i = Max + 2;
        } else if (c0 == 108 && s.size() == 1) {                                                                        // caso 'i'
            i = Max;
        } else if (c0 == 100 && s.size() == 1) {                                                                        // caso 'd'
            i = Max + 1;
        }
    }
    return i;
}

void tellInstructions(std::shared_ptr<Register> &reg) {
    if (!reg->isEmpty()) {
        RegisterView::tellInstruction(1);
    } else {
        RegisterView::tellInstruction(0);
    }
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
        RegisterView::tellStateChat(currentChat->getName(), 2, false);
}


bool doUserAction(std::shared_ptr<PrimaryUser> &user, Action &action, std::shared_ptr<Register> reg, std::list<std::string> &message) {
    if (reg->getCurrent() != nullptr && reg->getCurrent()->getWriter() != user) {                                       // quando è il turno dell'altra persona parlare non si può eseguire alcuna azione
        writeMessages(user, message, reg->getCurrent());
    } else {
        switch (action) {
            case Action::create: {
                std::string person = RegisterView::writeNameChat(0);
                std::shared_ptr<SecondaryUser> aPerson = std::make_shared<SecondaryUser>(person);

                std::shared_ptr<Chat> aChat = std::make_shared<Chat>(aPerson, user);
                reg->addInChatList(aChat);

                tellInstructions(reg);
                break;
            }
            case Action::noAction:
                break;
            case Action::quit: {
                RegisterView::closeRegister();
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
                            std::string nameChat = RegisterView::writeNameChat(1);

                            reg->searchChat(nameChat);
                            RegisterView::tellCurrentChat(reg->getCurrent()->getName());                          // se la chat che si sta cercando non è nel registro si rimane nella chat dove ci si trovava

                            tellInstructions(reg);
                            reg->getCurrent()->getChatMessages();
                            if (reg->getCurrent()->isBlocked())
                                RegisterView::tellStateChat(reg->getCurrent()->getName(), 2, false);
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
                        case Action::find: {
                            std::string s = ChatView::writeResearchCommand();
                            reg->getCurrent()->searchMessages(s);
                            break;
                        }
                        case Action::setImp: {
                            std::string s = ChatView::writeResearchCommand();
                            reg->getCurrent()->searchMessages(s);

                            bool req;
                            do {
                                std::string i = ChatView::writeImportanceCommand();
                                unsigned int n = convertInInt(i);
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
    std::shared_ptr<Register> WhatsApp(new Register());
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
