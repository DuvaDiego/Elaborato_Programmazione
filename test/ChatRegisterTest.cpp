#include <gtest/gtest.h>
#include "../ChatRegister.h"
#include "../User.h"

std::shared_ptr<ChatRegister> reg = std::make_shared<ChatRegister>();

TEST(Register, RegisterCtor) {
    ASSERT_EQ(regOwner, reg->getOwner());
    ASSERT_EQ(nullptr, reg->getCurrent());
    ASSERT_EQ(true, reg->isEmpty());
}

TEST(Register,EmptyRegisterTest) {
    std::shared_ptr<User> u = std::make_shared<User>("Utente");
    std::shared_ptr<SecondaryUser> s = std::make_shared<SecondaryUser>("Persona");
    std::shared_ptr<Chat> c = std::make_shared<Chat>(s, u);

    reg->addInChatList(c);
    ASSERT_EQ(false, reg->isEmpty());

    reg->removeChat();
    ASSERT_EQ(true, reg->isEmpty());
}
