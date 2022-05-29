#include "ChatView.h"


void ChatView::writeMessage(std::shared_ptr<Message> &m) {
    m->getText();
    if (m->getImportance()) {
        char ch = (char) 19;
        std::cout << "  " << ch << std::flush;
    }
    std::cout << std::endl;
}

void ChatView::getMessages(std::list<std::shared_ptr<Message>> list, bool parameter) {
    if (parameter) {
        std::cout << "\nUltimi 10 messaggi della Chat:" << std::endl;
        for (auto &message: list)
            writeMessage(message);
    }
    else
        std::cout << "\nLa Chat e' vuota." << std::endl;
}

std::string ChatView::writeImportanceCommand() {
    std::string s;
    std::cout << "\nInserire:" << std::endl;
    std::cout << "- un numero da 1 a 10, per rendere un messaggio importante" << std::endl;
    std::cout << "- 'l', per ottenere la lista dei messaggi importanti" << std::endl;
    std::cout << "- 'd', per svuotare la lista dei messaggi importanti" << std::endl;
    std::cin >> s;
    return s;
}

void ChatView::sayImportance(int parameter, unsigned int messageQuantity) {
    if (parameter == 0) {
        std::cout << "\nNella Chat ci sono " << messageQuantity << " messaggi." << std::endl;
        std::cout << "Il numero massimo che puoi inserire e' " << messageQuantity << std::endl;
    }
    else if (parameter == 1)
        std::cout << "Messaggio non piu' importante -" << std::flush;
    else if (parameter == 2)
        std::cout << "Messaggio importante -" << std::flush;
    else if (parameter == 3)
        std::cout << "Non ci sono messaggi importanti in questa Chat." << std::endl;
    else if (parameter == 4)
        std::cout << "Lista messaggi importanti svuotata." << std::endl;
    else if (parameter == 5)
        std::cout << "Carattere non valido." << std::endl;
    else
        std::cout << "La Chat e' vuota, non ci sono messaggi da rendere importanti." << std::endl;
}