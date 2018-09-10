
/// File: Property.h
/// Author : Manthan R. Tilva
/// Date : 17/07/2018
/// Brief : Declaration to interacte with propery class

#ifndef AppFramework_Core_Property_h_
#define AppFramework_Core_Property_h_

#include <algorithm>
#include <any>
#include <list>
#include <memory>
#include <typeinfo>
#include <unordered_map>

#include "AppFramework/Core/PropertyException.h"

namespace AppFramework {
namespace Core {
class Property {
public:
  class EventHandler {
  public:
    enum EventType { ADDING, REMOVING, UPDATING };
    virtual void onPropertyEvent(EventType type, const std::string &name, const std::type_info &info,
                                 const Property &oProperty) = 0;
  };
  Property();
  ~Property();
  template <typename type> void setProperty(const std::string &name, const type &value);
  template <typename type> type getProperty(const std::string &name) const;
  void addPropertyListner(std::shared_ptr<EventHandler> spHandler);
  void removePropertyListner(std::shared_ptr<EventHandler> spHandler);

protected:
  template <typename type> void addProperty(const std::string &name, const type &value);
  template <typename type> void removeProperty(const std::string &name);

private:
  template <typename type> void notifyEvent(EventHandler::EventType type, const std::string &name);

private:
  std::unordered_map<std::string, std::any> mUMapProperty;
  std::list<std::weak_ptr<EventHandler>> mListEventListner;
};
template <typename type> void Property::addProperty(const std::string &name, const type &value) {
  auto &it = std::find_if(std::begin(mUMapProperty), std::end(mUMapProperty),
                          [&name](decltype(mUMapProperty)::const_reference ref) {
                            if (ref.first.compare(name) == 0 && typeid(type) == ref.second.type())
                              return true;
                            return false;
                          });
  if (it != std::end(mUMapProperty)) {
    throw PropertyAlreadyAdded(name, typeid(type).name());
  }
  mUMapProperty.emplace(std::make_pair(name, std::any(value)));
  notifyEvent<type>(EventHandler::EventType::ADDING, name);
}
template <typename type> void Property::setProperty(const std::string &name, const type &value) {
  auto &it = std::find_if(std::begin(mUMapProperty), std::end(mUMapProperty),
                          [&name](decltype(mUMapProperty)::const_reference ref) {
                            if (ref.first.compare(name) == 0 && typeid(type) == ref.second.type())
                              return true;
                            return false;
                          });
  if (it == std::end(mUMapProperty)) {
    throw PropertyNotAdded(name, typeid(type).name());
  }
  it->second = std::any(value);
  notifyEvent<type>(EventHandler::EventType::UPDATING, name);
}
template <typename type> type Property::getProperty(const std::string &name) const {
  auto &it = std::find_if(std::begin(mUMapProperty), std::end(mUMapProperty),
                          [&name](const decltype(mUMapProperty)::const_reference ref) {
                            if (ref.first.compare(name) == 0 && typeid(type) == ref.second.type())
                              return true;
                            return false;
                          });
  if (it == std::end(mUMapProperty)) {
    throw PropertyNotAdded(name, typeid(type).name());
  }
  return std::any_cast<type>(it->second);
}
template <typename type> void Property::removeProperty(const std::string &name) {
  auto &it = std::find_if(std::begin(mUMapProperty), std::end(mUMapProperty),
                          [&name](const decltype(mUMapProperty)::const_reference ref) {
                            if (ref.first.compare(name) == 0 && typeid(type) == ref.second.type())
                              return true;
                            return false;
                          });
  if (it == std::end(mUMapProperty)) {
    throw PropertyNotAdded(name, typeid(type).name());
  }
  mUMapProperty.erase(it);
  notifyEvent<type>(EventHandler::EventType::REMOVING, name);
}
inline void Property::addPropertyListner(std::shared_ptr<EventHandler> spHandler) {
  if (spHandler != nullptr) {
    if (mListEventListner.size() > 0) {
      const auto &it = std::find_if(std::begin(mListEventListner), std::end(mListEventListner),
                                    [&spHandler](const decltype(mListEventListner)::const_reference ref) {
                                      if (ref.lock() == spHandler)
                                        return true;
                                      return false;
                                    });
      if (it->lock() == spHandler) {
        return;
      }
    }
    mListEventListner.push_back(spHandler);
  }
}
inline void Property::removePropertyListner(std::shared_ptr<EventHandler> spHandler) {
  if (spHandler != nullptr) {
    mListEventListner.remove_if([&spHandler](const decltype(mListEventListner)::const_reference ref) {
      if (ref.lock() == spHandler)
        return true;
      return false;
    });
  }
}
template <typename NativeType> void Property::notifyEvent(EventHandler::EventType type, const std::string &name) {
  bool bExpiredPresent{false};
  for (auto &&wListner : mListEventListner) {
    if (wListner.expired() == false) {
      auto &listner = wListner.lock();
      listner->onPropertyEvent(type, name, typeid(NativeType), *this);
    } else {
      bExpiredPresent = true;
    }
  }
}
} // namespace Core
} // namespace AppFramework

#endif // AppFramework_Core_Property_h_
