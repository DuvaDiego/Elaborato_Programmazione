#include <gtest/gtest.h>
#include "../Chat.h"
#include "../User.h"
#include "../ReceivedMessage.h"

std::shared_ptr<User> u = std::make_shared<User>("Utente");
std::shared_ptr<SecondaryUser> s = std::make_shared<SecondaryUser>("Persona");
std::shared_ptr<Chat> c = std::make_shared<Chat>(s, u);

TEST(Chat, ChatCtor) {
    ASSERT_EQ(s, c->getUser());
    ASSERT_EQ(u, c->getWriter());
    ASSERT_EQ("Persona", c->getName());
    ASSERT_EQ(false, c->isBlocked());
}

TEST(Chat, SetImportanceTest) {
    std::string s = "Persona";
    std::string w = "Test";
    std::list<std::string> t;
    t.push_front(w);
    std::shared_ptr<Message> m = std::make_shared<ReceivedMessage>(t, s);
    c->writeMessage(m);

    int n = 0;
    ASSERT_EQ(false, c->setMessImportance(n));

    n = 4;
    ASSERT_EQ(true, c->setMessImportance(n));

    n = 10;
    ASSERT_EQ(false, c->setMessImportance(n));

    n = 11;
    ASSERT_EQ(false, c->setMessImportance(n));

    n = 100;
    ASSERT_EQ(true, c->setMessImportance(n));
}