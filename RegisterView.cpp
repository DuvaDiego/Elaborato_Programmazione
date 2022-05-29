#include "RegisterView.h"

void RegisterView::tellInstruction(int parameter) {
    if (parameter == 1) {
        std::cout << "\nDigitare:" << std::endl;
        std::cout << "- R| per la lista chat" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- S| per selezionare una chat" << std::endl;
        std::cout << "- D| per eliminare l'attuale chat" << std::endl;
        std::cout << "- B| per bloccare/sbloccare l'attuale chat" << std::endl;
        std::cout << "- F| per impostare la preferenza dell'attuale chat" << std::endl;
        std::cout << "- I| per impostare l'importanza di un messaggio" << std::endl;
        std::cout << "- 'messaggio'| per scrivere un messaggio nella chat" << std::endl;
    } else if (parameter == 0) {
        std::cout << "\n Il registro al momento e' vuoto. Digitare:" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
    }
    std::cout << "- Q| per uscire" << std::endl;
}

std::string RegisterView::writeNameChat(int parameter) {
    if (parameter == 0)
        std::cout << "\nInserire nome utente della persona con cui vuoi parlare:" << std::flush;
    else if (parameter == 1)
        std::cout << "Seleziona una Chat dal registro, scrivendo il suo nome:" << std::flush;
    std::string name;
    std::cin >> name;
    return name;
}

void RegisterView::writeChats(std::list<std::shared_ptr<Chat>> list) {
    std::cout << "\nRegistro Chat:" << std::endl;
    for (auto &chat: list) {
        std::cout << "- " << chat->getName() << std::flush;
        if (chat->getUser()->isFavourite()) {
            char ch = (char) 3;                                                                                     // aggiunge un cuore dopo il nome della chat
            std::cout << "  " << ch << std::flush;
        }
        std::cout << std::endl;
    }
}

void RegisterView::tellCurrentChat(std::string name) {
    std::cout << "\nSei nella Chat '" << name << "_'." << std::endl;
}

void RegisterView::tellStateChat(std::string name, int parameter, bool parValue) {
    if (parameter == 0) {
        if (parValue)
            std::cout << "\nChat '" << name << "_' eliminata." << std::endl;
        else
            std::cout << "\nLa Chat '" << name << "_' non esiste nel registro." << std::flush;
    }
    else if (parameter == 1) {
        if (parValue)
            std::cout << "\nChat '" << name <<"_' rimossa dai Preferiti." << std::endl;
        else
            std::cout << "\nChat '" << name <<"_' aggiunta ai Preferiti." << std::endl;
    }
    else if (parameter == 2) {
        if (parValue)
            std::cout << "\nLa Chat '" << name <<"_' e' stata sbloccata." << std::endl;
        else
            std::cout << "\nLa Chat '" << name <<"_' e' bloccata, non e' possibile scriverci messaggi." << std::endl;
    }
}

void RegisterView::closeRegister() {
    std::cout << "\nProgramma chiuso, registro eliminato." << std::endl;
}
