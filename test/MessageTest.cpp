#include <gtest/gtest.h>
#include "../Message.h"

std::string s = "Mittente";
std::string r = "Destinatario";

TEST(Message, SentMessCtor) {
    std::string w1 = "Inviato";
    std::list<std::string> sendText;
    sendText.push_front(w1);
    std::shared_ptr<Message> sm = std::make_shared<Message>(sendText, s, r, true);

    sm->getText();
    ASSERT_EQ("Mittente", sm->getSender());
    ASSERT_EQ("Destinatario", sm->getRecipient());
    ASSERT_EQ(true, sm->getImportance());
}

TEST(Message, ReceivedMessCtor) {
    std::string w2 = "Ricevuto";
    std::list<std::string> receivedText;
    receivedText.push_front(w2);
    std::shared_ptr<Message> rm = std::make_shared<Message>(receivedText, r, s);

    rm->getText();
    ASSERT_EQ("Destinatario", rm->getSender());
    ASSERT_EQ("Mittente", rm->getRecipient());
    ASSERT_EQ(false, rm->getImportance());
}