#include "RegisterView.h"

RegisterView::RegisterView(std::shared_ptr<Register> r) : aRegister(move(r)) {
}

RegisterView::~RegisterView() {
    aRegister.reset();
}

void RegisterView::tellInstruction(int parameter) {
    if (parameter == 0) {                                                                                               // Caso registro vuoto
        std::cout << "\nIl registro al momento e' vuoto. Digitare:" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- Q| per uscire" << std::endl;
    } else if (parameter == 1) {                                                                                        // Caso registro con chat
        std::cout << "\nDigitare:" << std::endl;
        std::cout << "- R| per la lista chat" << std::endl;
        std::cout << "- C| per creare una chat" << std::endl;
        std::cout << "- S| per selezionare una chat" << std::endl;
        std::cout << "- D| per eliminare l'attuale chat" << std::endl;
        std::cout << "- B| per bloccare/sbloccare l'attuale chat" << std::endl;
        std::cout << "- P| per impostare la preferenza dell'attuale chat" << std::endl;
        std::cout << "- F| per cercare un messaggio nella chat" << std::endl;
        std::cout << "- E| per eliminare un messaggio della chat" << std::endl;
        std::cout << "- I| per impostare l'importanza di un messaggio nella chat" << std::endl;
        std::cout << "- 'messaggio'| per scrivere un messaggio nella chat" << std::endl;
        std::cout << "- Q| per uscire" << std::endl;
    } else if (parameter == 2) {
        std::cout << "Carattere non valido." << std::endl;                                                              // Caso carattere non previsto
    }

}

std::string RegisterView::chooseChat(int parameter) {
    if (parameter == 0)
        std::cout << "\nInserire nome utente della persona con cui vuoi parlare:" << std::flush;
    else if (parameter == 1)
        std::cout << "Seleziona una Chat dal registro, scrivendo il suo nome:" << std::flush;
    std::string name;
    std::cin >> name;
    return name;
}

void RegisterView::getChatList() {
    int quantity = aRegister->getChatQuantity();
    std::shared_ptr<Chat> chat;

    std::cout << "\nRegistro Chat:" << std::endl;
    for (int i = 0; i < quantity; i++) {
        chat = aRegister->getChat(i);
        std::cout << "- " << chat->getName() << std::flush;
        if (chat->getUser()->isFavourite()) {
            char ch = (char) 3;                                                                                         // Aggiunge un cuore dopo il nome della chat se sta tra i preferiti.
            std::cout << "  " << ch << std::flush;
        }
        std::cout << std::endl;
    }
}

void RegisterView::tellCurrentChat(std::string name) {
    std::cout << "\nSei nella Chat '" << name << "_'." << std::endl;
}

void RegisterView::tellStateChat(std::string name, int parameter, bool parValue) {
    if (parameter == 0) {                                                                                               // Caso cancellazione chat = true; caso ricerca senza successo = false.
        if (parValue)
            std::cout << "\nChat '" << name << "_' eliminata." << std::endl;
        else
            std::cout << "\nLa Chat '" << name << "_' non esiste nel registro." << std::flush;
    }
    else if (parameter == 1) {                                                                                          // Caso settaggio preferenza.
        if (parValue)
            std::cout << "\nChat '" << name <<"_' rimossa dai Preferiti." << std::endl;
        else
            std::cout << "\nChat '" << name <<"_' aggiunta ai Preferiti." << std::endl;
    }
    else if (parameter == 2) {                                                                                          // Caso blocco chat.
        if (parValue)
            std::cout << "\nLa Chat '" << name <<"_' e' stata sbloccata." << std::endl;
        else
            std::cout << "\nLa Chat '" << name <<"_' e' bloccata, non e' possibile scriverci messaggi." << std::endl;
    }
}

std::shared_ptr<Register> RegisterView::getRegister() {
    return aRegister;
}
void RegisterView::closeRegister() {
    std::cout << "\nProgramma chiuso, registro eliminato." << std::endl;
}