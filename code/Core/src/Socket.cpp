
/// File: Socket.cpp
/// Author : Manthan R. Tilva
/// Date : 30/07/2018
/// Brief : Defination to Socket class

#include "AppFramework/Core/Socket.h"
#include "AppFramework/Core/SocketException.h"

#include <algorithm>
#include <iostream>

namespace AppFramework {
namespace Core {
std::shared_ptr<Socket> Socket::create(const std::string &name, std::uint8_t type,Direction dir) {
  return std::shared_ptr<Socket>(new Socket(name, type,dir));
}
// Socket::Socket(const std::string &name) {}
Socket::~Socket() {
  for(auto& wPtrSocket : mListConnectedSocket) {
    if(wPtrSocket.expired() == false){
      auto sPtrSocket = wPtrSocket.lock();
      disconnect(sPtrSocket);
    }
  }
  mListConnectedSocket.clear();
}
void Socket::connect(std::shared_ptr<Socket> sPtrSocket) {
  if (sPtrSocket == nullptr) {
    throw NullSocket();
  }
  if(mUIntDataType != sPtrSocket->getDataType()){
    throw SocketException("Mismatch in datatype of socket");
  }
  auto fromDir = getDirection();
  auto toDir = sPtrSocket->getDirection();
  if ((fromDir == FlowDirection::UNKNOWN_DIRECTION) || (toDir == FlowDirection::UNKNOWN_DIRECTION) ||
      (fromDir == toDir)) {
    throw InvalidSocketConnection(getDirectionString(), sPtrSocket->getDirectionString());
  }
  const auto &it = std::find_if(std::begin(mListConnectedSocket), std::end(mListConnectedSocket),
                                [&sPtrSocket](const decltype(mListConnectedSocket)::const_reference ref) {
                                  if (ref.lock() == sPtrSocket)
                                    return true;
                                  return false;
                                });
  if (it != std::end(mListConnectedSocket)) {
    throw SocketAlreadyConnected();
  }
  mListConnectedSocket.push_back(sPtrSocket);
  onDataEvent(EventHandler::EventType::CONNECT,sPtrSocket,std::shared_ptr<DataFragment<void>>());
  sPtrSocket->onDataEvent<void>(EventHandler::EventType::CONNECT,shared_from_this(),std::shared_ptr<DataFragment<void>>(nullptr));
}
void Socket::disconnect(std::shared_ptr<Socket> sPtrSocket) {
  const auto &it = std::find_if(std::begin(mListConnectedSocket), std::end(mListConnectedSocket),
                                [&sPtrSocket](const decltype(mListConnectedSocket)::const_reference ref) {
                                  if (ref.lock() == sPtrSocket)
                                    return true;
                                  return false;
                                });
  if (it == std::end(mListConnectedSocket)) {
    throw SocketNotConnected();
  }
  onDataEvent(EventHandler::EventType::DISCONNECT,sPtrSocket,std::shared_ptr<DataFragment<void>>());
  sPtrSocket->onDataEvent<void>(EventHandler::EventType::DISCONNECT,shared_from_this(),std::shared_ptr<DataFragment<void>>(nullptr));
  mListConnectedSocket.erase(it);
}
bool Socket::isConnected() { return !mListConnectedSocket.empty(); }
void Socket::addListner(std::shared_ptr<EventHandler> sPtrHandler) {
  const auto &it = std::find_if(std::begin(mListEventHandler), std::end(mListEventHandler),
                                [&sPtrHandler](const decltype(mListEventHandler)::const_reference ref) {
                                  if (ref.lock() == sPtrHandler)
                                    return true;
                                  return false;
                                });
  if (it != std::end(mListEventHandler)) {
    throw SocketException("Listner already added.");
  }
  mListEventHandler.push_back(sPtrHandler);
}
void Socket::removeListner(std::shared_ptr<EventHandler> sPtrHandler) {
  const auto &it = std::find_if(std::begin(mListEventHandler), std::end(mListEventHandler),
                                [&sPtrHandler](const decltype(mListEventHandler)::const_reference ref) {
                                  if (ref.lock() == sPtrHandler)
                                    return true;
                                  return false;
                                });
  if (it == std::end(mListEventHandler)) {
    throw SocketException("Listner not added.");
  }
  mListEventHandler.erase(it);
}
} // namespace Core
} // namespace AppFramework
