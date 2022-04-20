cmake_minimum_required(VERSION 3.20)
project(Elaborato_Programmazione)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)
set(SOURCE_FILES User.cpp User.h ChatRegister.cpp ChatRegister.h Chat.cpp Chat.h Message.cpp Message.h PrimaryUser.cpp PrimaryUser.h SecondaryUser.cpp SecondaryUser.h SentMessage.cpp SentMessage.h ReceivedMessage.cpp ReceivedMessage.h)
add_executable(Elaborato_Programmazione main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(Elaborato_Programmazione core)