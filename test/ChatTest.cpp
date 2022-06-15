#include <gtest/gtest.h>
#include "../Chat.h"
#include "../User.h"

std::shared_ptr<User> u = std::make_shared<User>("Utente");
std::shared_ptr<SecondaryUser> s = std::make_shared<SecondaryUser>("Persona");
std::shared_ptr<Chat> c = std::make_shared<Chat>(s, u);

std::string w = "Test";
std::string w1 = "Parola";

TEST(Chat, ChatCtor) {
    ASSERT_EQ(s, c->getUser());
    ASSERT_EQ(u, c->getWriter());
    ASSERT_EQ("Persona", c->getName());
    ASSERT_EQ(false, c->isBlocked());
    ASSERT_EQ(0, c->getMessQuantity());
    ASSERT_EQ(0, c->getFoundQuantity());
    ASSERT_EQ(0, c->getSavedQuantity());
}

TEST(Chat, SetImportanceTest) {
    std::string p = "Mittente";
    std::string r = "Destinatario";
    std::list<std::string> t;

    t.push_front(w);
    std::shared_ptr<Message> m = std::make_shared<Message>(t, p, r);
    c->writeMessage(m);

    c->searchMessages(w);
    ASSERT_EQ(1, c->getFoundQuantity());

    ASSERT_EQ(false, c->setMessImportance(Max));                                                              // test lista messaggi importanti vuota

    ASSERT_EQ(false, c->setMessImportance(0));                                                                // test importanza del messaggio impostata
    ASSERT_EQ(1, c->getSavedQuantity());
    ASSERT_EQ(false, c->setMessImportance(0));
    ASSERT_EQ(0, c->getSavedQuantity());

    ASSERT_EQ(true, c->setMessImportance(4));                                                                 // test scelta numero messaggio sbagliato

    ASSERT_EQ(false, c->setMessImportance(Max));                                                              // test lettura lista messaggi importanti

    ASSERT_EQ(false, c->setMessImportance(Max + 1));                                                          // test pulizia messaggi importanti

    ASSERT_EQ(false, c->setMessImportance(Max + 2));                                                          // test annulla operazione

    ASSERT_EQ(true, c->setMessImportance(Max + 4));                                                           // test carattere non valido
}

TEST(Chat, FoundMessageTest) {
    ASSERT_EQ(true, c->searchMessages(w));
    ASSERT_EQ(false, c->searchMessages(w1));
}

TEST(Chat, messageRead) {
    std::string p = "Mittente";
    std::string r = "Destinatario";
    std::string w = "Test 1";
    std::list<std::string> t;

    t.push_front(w);
    std::shared_ptr<Message> m1 = std::make_shared<Message>(t, p, r);
    c->writeMessage(m1);

    ASSERT_EQ(2, c->getMessQuantity());
    ASSERT_EQ(false, m1->isRead());

    p = "Destinatario";
    r = "Mittente";
    w = "Test 2";

    t.push_front(w);
    std::shared_ptr<Message> m2 = std::make_shared<Message>(t, p, r);
    c->writeMessage(m2);

    ASSERT_EQ(3, c->getMessQuantity());
    ASSERT_EQ(true, m1->isRead());
    ASSERT_EQ(false, m2->isRead());
}

TEST(Chat, CancelMessageTest) {
    c->searchMessages(w);
    c->setMessImportance(0);

    ASSERT_EQ(true, c->cancelMessage(10));                                                                    // test scelta numero sbagliato

    ASSERT_EQ(false, c->cancelMessage(0));                                                                    // test eliminazione messaggio

    ASSERT_EQ(false, c->cancelMessage(Max + 2));                                                              // test annulla operazione

    ASSERT_EQ(true, c->cancelMessage(Max + 4));                                                               // test carattere non valido
}