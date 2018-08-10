#include "gtest/gtest.h"

#include "AppFramework/Core/Socket.h"
#include "AppFramework/Core/SocketException.h"

using AppFramework::Core::Socket;

TEST(SocketTest,ConstructorTest){
  try{
    auto sPtrSocket = Socket::create("sock1",1);
  }
  catch(...){
    FAIL();
  }
}
TEST(SocketTest,NameDirectionDataTypeTest){
  try{
    auto sPtrSocket = Socket::create("sock1",1);
    EXPECT_EQ(sPtrSocket->getName(),"sock1");
    EXPECT_EQ(sPtrSocket->getDataType(),1);
    EXPECT_EQ(sPtrSocket->getDirection(),Socket::Direction::UNKNOWN_DIRECTION);
    auto sPtrSocket1 = Socket::create("sock2",2,Socket::Direction::IN_DIRECTION);
    EXPECT_EQ(sPtrSocket1->getName(),"sock2");
    EXPECT_EQ(sPtrSocket1->getDataType(),2);
    EXPECT_EQ(sPtrSocket1->getDirection(),Socket::Direction::IN_DIRECTION);
  }
  catch(...){
    FAIL();
  }
}
TEST(SocketTest,ConnectTest1){
  ///unknown direction
  try{
    auto sPtrSocket1 = Socket::create("sock1",1);
    auto sPtrSocket2 = Socket::create("sock2",1);
    sPtrSocket1->connect(sPtrSocket2);
    FAIL();
  }
  catch(AppFramework::Core::SocketException& ex){
    ex;
  }
  catch(...){
    FAIL();
  }
  ///datatype mismatch
  try{
    auto sPtrSocket1 = Socket::create("sock1",1,Socket::Direction::IN_DIRECTION);
    auto sPtrSocket2 = Socket::create("sock2",2,Socket::Direction::OUT_DIRECTION);
    sPtrSocket1->connect(sPtrSocket2);
    FAIL();
  }
  catch(AppFramework::Core::SocketException& ex){
    ex;
  }
  catch(...){
    FAIL();
  }
  ///null socket
  try{
    auto sPtrSocket1 = Socket::create("sock1",1,Socket::Direction::IN_DIRECTION);
    // auto sPtrSocket2 = Socket::create("sock2",2,Socket::Direction::OUT_DIRECTION);
    sPtrSocket1->connect(nullptr);
    FAIL();
  }
  catch(AppFramework::Core::SocketException& ex){
    ex;
  }
  catch(...){
    FAIL();
  }
  ///null socket
  try{
    auto sPtrSocket1 = Socket::create("sock1",1,Socket::Direction::IN_DIRECTION);
    auto sPtrSocket2 = std::shared_ptr<Socket>();
    sPtrSocket1->connect(sPtrSocket2);
    FAIL();
  }
  catch(AppFramework::Core::SocketException& ex){
    ex;
  }
  catch(...){
    FAIL();
  }
  ///direction invalid
  try{
    auto sPtrSocket1 = Socket::create("sock1",1,Socket::Direction::IN_DIRECTION);
    auto sPtrSocket2 = Socket::create("sock2",1,Socket::Direction::IN_DIRECTION);
    sPtrSocket1->connect(sPtrSocket2);
    FAIL();
  }
  catch(AppFramework::Core::SocketException& ex){
    ex;
  }
  catch(...){
    FAIL();
  }
}
TEST(SocketTest,ConnectTest2){
  try{
    auto sPtrSocket1 = Socket::create("sock1",1,Socket::Direction::IN_DIRECTION);
    auto sPtrSocket2 = Socket::create("sock2",1,Socket::Direction::OUT_DIRECTION);
    sPtrSocket1->connect(sPtrSocket2);
  }
  catch(...){
    FAIL();
  }
}
TEST(SocketTest,EventHandlerTest1){
  try{
    auto sPtrSocket1 = Socket::create("sock1",1,Socket::Direction::IN_DIRECTION);
    auto sPtrSocket2 = Socket::create("sock2",1,Socket::Direction::OUT_DIRECTION);
    class EventHandler : public Socket::EventHandler {
    public:
      virtual void onEvent(EventType type, const std::shared_ptr<Socket> &pFrom, const std::shared_ptr<Socket> &pTo,
                           std::uint8_t dataType, std::any pData) override final {
                           }
                           EventType mType;

    };
    sPtrSocket1->connect(sPtrSocket2);
  }
  catch(...){
    FAIL();
  }
}
