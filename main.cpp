#include <iostream>
#include <memory>

#include "PrimaryUser.h"
#include "RegisterView.h"
#include "ChatView.h"

enum class Action {
    getReg, create, remove, select, favourites, block, write, find, cancel, setImp, quit, noAction
};

Action getUserAction(std::string firstWord) {
    if (firstWord[1] == '|') {
        char c = firstWord[0];
        switch (c) {
            case 'Q':
                return Action::quit;
            case 'F':
                return Action::find;
            case 'E':
                return Action::cancel;
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

unsigned int convertInInt(std::string s, bool parameter) {
    int i = Max + 4;                                                                                                    // caso valore non valido
    if (s.size() <= 2) {
        unsigned char c0 = s.back();
        unsigned char c1 = '0';
        if (s.size() == 2)
            c1 = s.front();

        int i0 = (int) c0;
        int i1 = (int) c1;

        if (!parameter) {
            if ((i0 >= 48 && i0 <= 57) && (i1 >= 48 && i1 <= 57)) {                                                     // caso scelta tra 1 e Max
                i0 -= 48;
                i1 -= 48;

                i = i1 * 10 + i0 - 1;

                if (i >= Max)                                                                                           // caso scelta tra Max + 1 e 99
                    i = Max + 4;
            } else if (c0 == 98 && s.size() == 1) {                                                                     // caso 'b'
                i = Max + 2;
            }
        } else {
            if (c0 == 108 && s.size() == 1) {                                                                           // caso 'l'
                i = Max;
            } else if (c0 == 100 && s.size() == 1) {                                                                    // caso 'd'
                i = Max + 1;
            } else if (c0 == 115 && s.size() == 1) {                                                                    // caso 's'
                i = Max + 3;
            }
        }
    }
    return i;
}

void tellInstructions(std::shared_ptr<RegisterView> &regView) {
    if (!regView->getRegister()->isEmpty()) {
        regView->tellInstruction(1);
    } else {
        regView->tellInstruction(0);
    }
}

void writeMessages(std::shared_ptr<PrimaryUser> &user, std::shared_ptr<RegisterView> &regView, std::list<std::string> &message, std::shared_ptr<Chat> currentChat) {
    if (!currentChat->isBlocked()) {
        if (message.front().front() != '|') {
            std::string lastWord = message.back();                                                                      // Toglie dal messaggio il simbolo '|' di chiusura
            message.pop_back();
            lastWord.pop_back();
            message.push_back(lastWord);

            std::shared_ptr<ChatView> chatView = std::make_shared<ChatView>(currentChat);

            if (currentChat->getWriter() == user) {                                                                     // Turno del proprietario del registro
                std::shared_ptr<Message> sentMess = std::make_shared<Message>(message, user->getName(),currentChat->getUser()->getName());
                currentChat->writeMessage(sentMess);
                chatView->writeTextMessage(sentMess);

                currentChat->setWriter(currentChat->getUser());
            } else {                                                                                                    // Turno dell'altro utente
                std::shared_ptr<Message> receivedMess = std::make_shared<Message>(message,currentChat->getUser()->getName(), user->getName());
                currentChat->writeMessage(receivedMess);
                chatView->writeTextMessage(receivedMess);

                currentChat->setWriter(user);
            }
        }
    }
    else
        regView->tellStateChat(currentChat->getName(), 2, false);
}


bool doUserAction(std::shared_ptr<PrimaryUser> &user, Action &action, std::shared_ptr<RegisterView> &regView, std::list<std::string> &message) {
    std::shared_ptr<Register> reg = regView->getRegister();
    if (reg->getCurrent() != nullptr && reg->getCurrent()->getWriter() != user) {                                       // quando è il turno dell'altra persona parlare non si può eseguire alcuna azione
        writeMessages(user, regView, message, reg->getCurrent());
    } else {
        switch (action) {
            case Action::create: {
                std::string person = regView->chooseChat(0);
                std::shared_ptr<SecondaryUser> aPerson = std::make_shared<SecondaryUser>(person);

                std::shared_ptr<Chat> aChat = std::make_shared<Chat>(aPerson, user);
                reg->addInChatList(aChat);
                regView->tellCurrentChat(person);

                tellInstructions(regView);
                break;
            }
            case Action::noAction: {
                regView->tellInstruction(2);
                break;
            }
            case Action::quit: {
                regView->closeRegister();
                return true;
            }
            default: {
                if (!reg->isEmpty()) {
                    std::shared_ptr<Chat> currentChat = reg->getCurrent();
                    std::shared_ptr<ChatView> chatView = std::make_shared<ChatView>(currentChat);
                    switch (action) {
                        case Action::getReg: {
                            regView->getChatList();
                            break;
                        }
                        case Action::select: {
                            regView->getChatList();
                            std::string nameChat = regView->chooseChat(1);

                            bool found = reg->searchChat(nameChat);
                            if (!found)
                                regView->tellStateChat(nameChat, 0, false);
                            else {
                                currentChat = reg->getCurrent();
                                chatView->associateChat(currentChat);
                            }


                            regView->tellCurrentChat(currentChat->getName());                                     // se la chat che si sta cercando non è nel registro si rimane nella chat dove ci si trovava

                            tellInstructions(regView);
                            chatView->getAllMessages();
                            if (currentChat->isBlocked())
                                regView->tellStateChat(currentChat->getName(), 2, false);
                            break;
                        }
                        case Action::remove: {
                            if (!reg->isEmpty()) {
                                regView->tellStateChat(currentChat->getName(), 0, true);
                                reg->removeChat();
                                currentChat = reg->getCurrent();

                                if (currentChat != nullptr)
                                    regView->tellCurrentChat(currentChat->getName());
                                tellInstructions(regView);
                                if (currentChat != nullptr) {
                                    chatView->getAllMessages();
                                }
                            }
                            break;
                        }
                        case Action::favourites: {
                            if (currentChat->getUser()->isFavourite())
                                regView->tellStateChat(currentChat->getName(), 1, true);
                            else
                                regView->tellStateChat(currentChat->getName(), 1, false);
                            reg->addInFavourites();
                            break;
                        }
                        case Action::block: {
                            if (currentChat->isBlocked())
                                regView->tellStateChat(currentChat->getName(), 2, true);
                            else
                                regView->tellStateChat(currentChat->getName(), 2, false);
                            reg->blockChat();
                            break;
                        }
                        case Action::find: {
                            if (currentChat->getMessQuantity() == 0)
                                chatView->getAllMessages();
                            else {
                                std::string s = chatView->chooseResCommand();
                                currentChat->searchMessages(s);
                                chatView->getFoundMessages();
                            }
                            break;
                        }
                        case Action::cancel: {
                            if (currentChat->getMessQuantity() == 0)
                                chatView->getAllMessages();
                            else {
                                std::string s = chatView->chooseResCommand();
                                bool goOn = currentChat->searchMessages(s);
                                chatView->getFoundMessages();

                                while (goOn) {
                                    std::string i = chatView->chooseGenCommand();
                                    unsigned int n = convertInInt(i, false);

                                    chatView->selectCase((int) n, 0);
                                    goOn = currentChat->cancelMessage(n);
                                }
                            }
                            break;
                        }
                        case Action::setImp: {
                            if (currentChat->getMessQuantity() == 0)
                                chatView->getAllMessages();
                            else {
                                std::string s = chatView->chooseImpCommand();
                                unsigned int n = convertInInt(s, true);

                                if (n == Max + 3) {
                                    s = chatView->chooseResCommand();
                                    bool goOn = currentChat->searchMessages(s);
                                    chatView->getFoundMessages();

                                    while (goOn) {
                                        std::string i = chatView->chooseGenCommand();
                                        unsigned int m = convertInInt(i, false);

                                        chatView->selectCase((int) m, 1);
                                        goOn = currentChat->setMessImportance(m);
                                    }
                                } else {
                                    chatView->selectCase((int) n, 1);
                                    currentChat->setMessImportance(n);
                                }
                            }
                            break;
                        }
                        case Action::write: {
                            writeMessages(user, regView, message, currentChat);
                             break;
                        }
                    }
                }
                else
                    regView->tellInstruction(2);
            }
        }
    }
    return false;
}

int main() {
    std::shared_ptr<Register> WhatsApp(new Register());
    std::shared_ptr<PrimaryUser> Diego = std::make_shared<PrimaryUser>(WhatsApp);
    std::shared_ptr<RegisterView> regView = std::make_shared<RegisterView>(WhatsApp);

    tellInstructions(regView);
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
        bool quit =doUserAction(Diego ,action, regView, message);

        if (quit) {
            Diego.reset();
            return 0;
        }
    }
}
