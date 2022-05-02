#include <gtest/gtest.h>
#include "../SentMessage.h"
#include "../ReceivedMessage.h"

std::string p = "Persona";

TEST(Message, SentMessCtor) {
    std::string w1 = "Inviato";
    std::list<std::string> sendText;
    sendText.push_front(w1);
    std::shared_ptr<SentMessage> sm = std::make_shared<SentMessage>(sendText, p, true);

    sm->getText();
    ASSERT_EQ(regOwner, sm->getSender());
    ASSERT_EQ("Persona", sm->getRecipient());
    ASSERT_EQ(true, sm->getImportance());
}

TEST(Message, ReceivedMessCtor) {
    std::string w2 = "Ricevuto";
    std::list<std::string> receivedText;
    receivedText.push_front(w2);
    std::shared_ptr<ReceivedMessage> rm = std::make_shared<ReceivedMessage>(receivedText, p);

    rm->getText();
    ASSERT_EQ("Persona", rm->getSender());
    ASSERT_EQ(regOwner, rm->getRecipient());
    ASSERT_EQ(false, rm->getImportance());
}