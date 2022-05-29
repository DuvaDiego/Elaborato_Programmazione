cmake_minimum_required(VERSION 3.20)
project(Elaborato_Programmazione)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        User.cpp  User.h
        PrimaryUser.cpp  PrimaryUser.h
        SecondaryUser.cpp  SecondaryUser.h
        Register.cpp Register.h
        RegisterView.cpp RegisterView.h
        Chat.cpp  Chat.h
        ChatView.cpp ChatView.h
        Message.cpp  Message.h)
add_executable(Elaborato_Programmazione main.cpp)
add_library(core ${SOURCE_FILES})
add_subdirectory(test)
target_link_libraries(Elaborato_Programmazione core)