#include "ChatView.h"

ChatView::ChatView(std::shared_ptr<Chat> c) : aChat(move(c)) {
}

void ChatView::writeTextMessage(std::shared_ptr<Message> &m) {
    if (m->isRead()) {
        char ch = (char) 175;                                                                                           // Aggiunge ">>" prima del messaggio se è stato letto.
        std::cout << ch << " " << std::flush;
    } else {
        std::cout << "> " << std::flush;                                                                                // Aggiunge ">" prima del messaggio se non è stato ancora letto.
    }

    std::cout << m->getSender() << ": " << std::flush;

    m->getText();

    if (m->getImportance()) {
        char ch = (char) 19;                                                                                            // Aggiunge "!!" in fondo al messaggio è importante.
        std::cout << "  " << ch << std::flush;
    }
    std::cout << std::endl;
}

void ChatView::getAllMessages() {                                                                                       // Prende tutti i messaggi scritti nella chat.
    int quantity = aChat->getMessQuantity();
    if (quantity != 0) {
        std::shared_ptr<Message> message;

        std::cout << "\nUltimi " << quantity << " messaggi della Chat:" << std::endl;
        for (int i = 0; i < quantity; i++) {
            message = aChat->getMessage(i);
            writeTextMessage(message);
        }
    } else
        std::cout << "\nLa Chat e' vuota." << std::endl;
}

void ChatView::getSavedMessages() {                                                                                     // Prende tutti i messaggi importanti,
    int quantity = aChat->getSavedQuantity();
    if (quantity != 0) {
        std::shared_ptr<Message> message;
        for (int i = 0; i < quantity; i++) {
            message = aChat->getSavedMessage(i);
            writeTextMessage(message);
        }
    }
}

void ChatView::getFoundMessages() {                                                                                     // Prende tutti i messaggi trovati nella ricerca di un messaggio.
    int quantity = aChat->getFoundQuantity();
    if (quantity != 0) {
        std::shared_ptr<Message> message;

        std::cout << "Ci sono " << quantity << " messaggi che contengono la parola cercata:" << std::endl;
        for (int i = 0; i < quantity; i++) {
            message = aChat->getFoundMessage(i);
            std::cout << i + 1 << ") " << std::flush;
            writeTextMessage(message);
        }
    } else
        std::cout << "Non ci sono messaggi che contengono la parola cercata." << std::endl;
}

std::string ChatView::chooseGenCommand() {
    std::string s;
    std::cout << "\nInserire:" << std::endl;
    std::cout << "- un numero da 1 a " << Max << ", per selezionare il messaggio" << std::endl;
    std::cout << "- 'b', per annullare l'azione'" << std::endl;
    std::cin >> s;
    return s;
}

std::string ChatView::chooseResCommand() {
    std::string s;
    std::cout << "\nScrivere la parola da ricercare nei messaggi:" << std::endl;
    std::cin >> s;
    return s;
}

std::string ChatView::chooseImpCommand() {
    std::string s;
    std::cout << "\nInserire:" << std::endl;
    std::cout << "- 's', per cercare un messaggio da rendere importante" << std::endl;
    std::cout << "- 'l', per ottenere la lista dei messaggi importanti" << std::endl;
    std::cout << "- 'd', per svuotare la lista dei messaggi importanti" << std::endl;
    std::cin >> s;
    return s;
}

void ChatView::selectCase(int n, int parameter) {
    int quantity;

    if (n >= 0 && n < Max) {                                                                                            // Caso scelta messaggio oltre la quantità presente
        quantity =  aChat->getFoundQuantity();
        if (n > quantity - 1) {
            std::cout << "\nI messaggi trovati sono " << quantity << "." << std::endl;
            std::cout << "Il numero massimo che puoi inserire e' " << quantity << "." << std::endl;
        }
        else {
            std::shared_ptr<Message> message = aChat->getFoundMessage(n);
            std::cout << "Messaggio " << std::flush;
            if (parameter == 0) {                                                                                       // Caso eliminazione messaggio
                std::cout << "eliminato " << std::flush;
            } else if (parameter == 1) {                                                                                // Caso azione settaggio importanza
                if (message->getImportance())
                    std::cout << "non piu' importante " << std::flush;
                else
                    std::cout << "importante " << std::flush;
            }
            writeTextMessage(message);
        }
    }
    else if (n == Max && parameter == 1) {
        quantity = aChat->getSavedQuantity();
        if (quantity == 0)
            std::cout << "Non ci sono messaggi importanti in questa Chat." << std::endl;
        else
            getSavedMessages();
    }
    else if (n == Max + 1 && parameter == 1)
        std::cout << "Lista messaggi importanti svuotata." << std::endl;
    else if (n == Max + 2)
        std::cout << "Operazione annullata." << std::endl;
    else
        std::cout << "Carattere non valido." << std::endl;
}

void ChatView::associateChat(std::shared_ptr<Chat>& newChat) {
    aChat = newChat;
}