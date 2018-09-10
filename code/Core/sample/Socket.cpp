
#include "AppFramework/Core/DataFragment.h"
#include "AppFramework/Core/Socket.h"
#include "AppFramework/Core/SocketException.h"

#include <iostream>

using AppFramework::Core::DataFragment;
using AppFramework::Core::Socket;

int main(int argc, char **argv) {
  try {
    auto socket2 = Socket::create("b", 1, Socket::Direction::OUT_DIRECTION);
    auto socket1 = Socket::create("a", 1, Socket::Direction::IN_DIRECTION);
    class EventHandler : public Socket::EventHandler {
    public:
      virtual void onEvent(EventType type, const std::weak_ptr<Socket>& wpFrom,  const std::weak_ptr<Socket>& wpTo, std::uint8_t dataType, std::any pData) override final {
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "type:" << type << std::endl;
        auto pFrom = wpFrom.lock();
        auto pTo = wpTo.lock();
        if (pFrom)
          std::cout << "pFrom.name:" << pFrom->getName() << std::endl;
        if (pTo)
          std::cout << "pTo.name:" << pTo->getName() << std::endl;
        std::cout << pData.has_value() <<std::endl;
        std::cout<<"dataType:"<<static_cast<int>(dataType)<<std::endl;
        if(pData.has_value() && dataType == 1){
          auto dataFrag = std::any_cast<std::shared_ptr<DataFragment<int>>>(pData);
          std::cout<<*dataFrag->getData()<<std::endl;
        }
        std::cout << pData.type().name() <<std::endl;
      }
    };
    auto intData = std::make_shared<int>(12);
    auto intDataFrag = DataFragment<int>::create();
    intDataFrag->updateData(intData);
    std::shared_ptr<Socket::EventHandler> sPtrHandler = std::make_shared<EventHandler>();
    socket1->connect(socket2);
    socket1->addListner(sPtrHandler);
    socket2->addListner(sPtrHandler);
    socket1->sendData<int>(intDataFrag);
    socket1->disconnect(socket2);
  } catch (std::exception &ex) {
    std::cout << "std::exception:" << ex.what() << std::endl;
  } catch (...) {
    std::cout << "unknown exeption" << std::endl;
  }
  return 0;
}
