
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>

#include "AppFramework/Core/Component.h"
#include "AppFramework/Core/DataFragment.h"
#include "AppFramework/Core/Socket.h"
#include "AppFramework/Core/SocketException.h"
#include "SinWaveData.h"

using AppFramework::Core::DataFragment;
using AppFramework::Core::Socket;

using AppFramework::Core::Component;

int main(int argc, char **argv) {
  class EventHandler : public Socket::EventHandler {
  public:
    bool bIsFirstRx{true};
    bool bHasMetaData{false};
    double a,b,c;
    std::shared_ptr<MetaData> metaData;
    virtual void onEvent(EventType type, const std::weak_ptr<Socket> &wpFrom, const std::weak_ptr<Socket> &wpTo,
                         std::uint8_t dataType, std::any pData) override final {
      // std::cout << "----------------------------------------------------" << std::endl;
      if (dataType != 1)
        return;
      auto pFrom = wpFrom.lock();
      auto pTo = wpTo.lock();
      // if (pFrom)
      //   std::cout << "pFrom.name:" << pFrom->getName() << std::endl;
      // if (pTo)
      //   std::cout << "pTo.name:" << pTo->getName() << std::endl;
      switch (type) {
        case EventType::CONNECT:
          std::cout << "Event:CONNECT" << std::endl;
          break;
        case EventType::DISCONNECT:
          std::cout << "Event:DISCONNECT" << std::endl;
          break;
        case EventType::RECIEVED:
          // std::cout << "Event:RECIEVED\t" << static_cast<int>(dataType) << std::endl;
          // std::cout << pData.type().name() << std::endl;
          if (bIsFirstRx) {
            try {
              auto dataFrag = std::any_cast<std::shared_ptr<DataFragment<MetaData>>>(pData);
              metaData = dataFrag->getData();
              std::cout << "mMaxValue:" << metaData->mMaxValue << std::endl;
              std::cout << "mMinValue:" << metaData->mMinValue << std::endl;
              std::cout << "mPeriod:" << metaData->mPeriod << std::endl;
              bHasMetaData = true;
              a = metaData->mMaxValue - metaData->mMinValue;
            } catch (const std::bad_any_cast &e) {
              std::cout << e.what() << '\n';
            }
            bIsFirstRx = false;
          } else {
            if (!bHasMetaData) {
              std::cout << "Don't have metadata" << std::endl;
            } else {
              try {
                auto dataFrag = std::any_cast<std::shared_ptr<DataFragment<double>>>(pData);
                auto x = std::round((*dataFrag->getData() - metaData->mMinValue));
                std::cout << std::setw(x) <<"."<< std::endl;
              } catch (const std::bad_any_cast &e) {
                std::cout << e.what() << '\n';
              }
            }
          }
          break;
        case EventType::SENT:
          std::cout << "Event:SENT" << std::endl;
          break;
        default:
          std::cout << "Unknown event type" << std::endl;
          break;
      }
    }
  };
  try {
    auto creator = boost::dll::import_alias<Component::component_create_t>(
        std::string(argv[1]).append("SinWaveGenerator.plug"), "create_component",
        boost::dll::load_mode::append_decorations);
    auto comp = creator("MySinWaveGenerator");
    comp->setProperty<std::uint32_t>("pollInterval", 1);
    comp->setProperty<double>("period", 1000);
    comp->setProperty<double>("maxValue", 167);
    comp->setProperty<double>("minValue", 1);
    comp->setState(Component::State::CONFIGURE);
    auto socket1 = Socket::create("a", 1, Socket::Direction::IN_DIRECTION);
    std::shared_ptr<Socket::EventHandler> sPtrHandler = std::make_shared<EventHandler>();
    socket1->addListner(sPtrHandler);
    auto wSocket2 = comp->getSocket("SinWaveData", 1, AppFramework::Core::Socket::Direction::OUT_DIRECTION);
    if (auto socket2 = wSocket2.lock()) {
      socket2->connect(socket1);
    }
    comp->setState(Component::State::RUN);
    std::cout << __LINE__ << ":" << __FUNCTION__ << std::endl;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(static_cast<std::int64_t>(comp->getProperty<double>("period")*3)));
    std::cout << __LINE__ << ":" << __FUNCTION__ << std::endl;
    comp->setState(Component::State::STOP);
    std::cout << __LINE__ << ":" << __FUNCTION__ << std::endl;
    if (auto socket2 = wSocket2.lock()) {
      socket2->disconnect(socket1);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  } catch (...) {
    std::cout << "unknown exception" << std::endl;
  }
  return 0;
}
