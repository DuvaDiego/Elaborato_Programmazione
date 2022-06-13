#include "ChatView.h"

ChatView::ChatView(std::shared_ptr<Chat> c) : aChat(move(c)) {
}

void ChatView::writeMessage(std::shared_ptr<Message> &m) {
    if (m->isRead()) {
        char ch = (char) 175;                                                                                           // aggiunge ">>" prima del messaggio se è stato letto
        std::cout << ch << " " << std::flush;
    } else {
        std::cout << "> " << std::flush;                                                                                // aggiunge ">" prima del messaggio se non è stato ancora letto
    }

    std::cout << m->getSender() << ": " << std::flush;

    m->getText();

    if (m->getImportance()) {
        char ch = (char) 19;                                                                                            // aggiunge "!!" in fondo al messaggio è importante
        std::cout << "  " << ch << std::flush;
    }
    std::cout << std::endl;
}

void ChatView::getMessages() {
    int quantity = aChat->getMessageQuantity();
    if (quantity != 0) {
        std::shared_ptr<Message> message;

        std::cout << "\nUltimi " << quantity << " messaggi della Chat:" << std::endl;
        for (int i = 0; i < quantity; i++) {
            message = aChat->getMessage(i);
            writeMessage(message);
        }
    } else
        std::cout << "\nLa Chat e' vuota." << std::endl;
}

std::string ChatView::writeResearchCommand() {
    std::string s;
    std::cout << "\nScrivere la parola da ricercare nei messaggi:" << std::endl;
    std::cin >> s;
    return s;
}

void ChatView::getFoundMessages() {
    int quantity = aChat->getFoundQuantity();
    if (quantity != 0) {
        std::shared_ptr<Message> message;

        std::cout << "Ci sono " << quantity << " messaggi che contengono la parola cercata:" << std::endl;
        for (int i = 0; i < quantity; i++) {
            message = aChat->getFoundMessage(i);
            std::cout << i + 1 << ") " << std::flush;
            writeMessage(message);
        }
    } else
        std::cout << "Non ci sono messaggi che contengono la parola cercata" << std::endl;
}

std::string ChatView::writeGeneralCommand() {
    std::string s;
    std::cout << "\nInserire:" << std::endl;
    std::cout << "- un numero da 1 a " << Max << ", per selezionare il messaggio" << std::endl;
    std::cout << "- 'b', per annullare l'azione'" << std::endl;
    std::cin >> s;
    return s;
}

void ChatView::selectionCase(int parameter, unsigned int messageQuantity) {
    if (parameter == 0) {
        std::cout << "\nI messaggi trovati sono " << messageQuantity << "." << std::endl;
        std::cout << "Il numero massimo che puoi inserire e' " << messageQuantity << std::endl;
    }
    else if (parameter == 1)
        std::cout << "Messaggio eliminato " << std::endl;
    else if (parameter == 2)
        std::cout << "Messaggio non piu' importante " << std::flush;
    else if (parameter == 3)
        std::cout << "Messaggio importante " << std::flush;
    else if (parameter == 4)
        std::cout << "Non ci sono messaggi importanti in questa Chat." << std::endl;
    else if (parameter == 5)
        std::cout << "Lista messaggi importanti svuotata." << std::endl;
    else if (parameter == 6)
        std::cout << "Operazione annullata." << std::endl;
    else
        std::cout << "Carattere non valido." << std::endl;
}

std::string ChatView::writeImportanceCommand() {
    std::string s;
    std::cout << "\nInserire:" << std::endl;
    std::cout << "- 's', per cercare un messaggio da rendere importante" << std::endl;
    std::cout << "- 'l', per ottenere la lista dei messaggi importanti" << std::endl;
    std::cout << "- 'd', per svuotare la lista dei messaggi importanti" << std::endl;
    std::cin >> s;
    return s;
}

void ChatView::associateChat(std::shared_ptr<Chat> newChat) {
    aChat = newChat;
}