
/// File: Property.h
/// Author : Manthan R. Tilva
/// Date : 17/07/2018
/// Brief : Declaration to interacte with propery class

#ifndef AppFramework_Core_Property_h_
#define AppFramework_Core_Property_h_
#include "interface/InterfaceProperty.h"

#include <list>
#include <memory>
#include <unordered_map>

#include "PropertyValue.h"

namespace AppFramework {
namespace Core {
// class InterfaceProperty;
// class InterfacePropertyEvent {
// public:
//   enum EventType {
//     ADDING,
//     REMOVING,
//     UPDATING
//   };
//   virtual void OnPropertyEvent(EventType type,const std::string& name,const
//   InterfaceProperty& oProperty) = 0;
// };
class Property : public Interface::InterfaceProperty {
private:
public:
  Property();
  ~Property();
  virtual void addBoolProperty(const std::string &name, bool value) final;
  virtual void addInt8Property(const std::string &name, const std::int8_t &value) final;
  virtual void addInt16Property(const std::string &name, const std::int16_t &value) final;
  virtual void addInt32Property(const std::string &name, const std::int32_t &value) final;
  virtual void addInt64Property(const std::string &name, const std::int64_t &value) final;
  virtual void addStringProperty(const std::string &name, const std::string &value) final;

  virtual void setBoolProperty(const std::string &name, bool value) final;
  virtual void setInt8Property(const std::string &name, const std::int8_t &value) final;
  virtual void setInt16Property(const std::string &name, const std::int16_t &value) final;
  virtual void setInt32Property(const std::string &name, const std::int32_t &value) final;
  virtual void setInt64Property(const std::string &name, const std::int64_t &value) final;
  virtual void setStringProperty(const std::string &name, const std::string &value) final;
  virtual bool getBoolProperty(const std::string &name) const final;
  virtual std::int8_t getInt8Property(const std::string &name) const final;
  virtual std::int16_t getInt16Property(const std::string &name) const final;
  virtual std::int32_t getInt32Property(const std::string &name) const final;
  virtual std::int64_t getInt64Property(const std::string &name) const final;
  virtual std::string getStringProperty(const std::string &name) const final;
  virtual void removeProperty(const std::string &name) final;
  void addPropertyListner(std::shared_ptr<Interface::InterfacePropertyEventHandler> sPtrHandler) {
    mVecPropertyListner.push_back(sPtrHandler);
  }
  void removePropertyListner(std::shared_ptr<Interface::InterfacePropertyEventHandler> sPtrHandler) {
    mVecPropertyListner.remove_if([&sPtrHandler](const decltype(mVecPropertyListner)::reference ref) {
      auto handler = ref.lock();
      return handler == sPtrHandler;
    });
  }
  void notifyUpdate(const std::string &name) {
    notifyEvent(Interface::InterfacePropertyEventHandler::EventType::UPDATING, name);
  }
  void notifyRemove(const std::string &name) {
    notifyEvent(Interface::InterfacePropertyEventHandler::EventType::REMOVING, name);
  }
  void notifyAdd(const std::string &name) {
    notifyEvent(Interface::InterfacePropertyEventHandler::EventType::ADDING, name);
  }
  void notifyEvent(Interface::InterfacePropertyEventHandler::EventType event, const std::string &name) {
    mVecPropertyListner.remove_if([](const decltype(mVecPropertyListner)::reference ref) {
      return ref.use_count() == 0;
      return true;
    });
    for (auto &&wHandler : mVecPropertyListner) {
      auto handler = wHandler.lock();
      handler->onPropertyEvent(event, name, *this);
    }
  }

private:
  template <typename NativeType, ValueType enumType>
  void addProperty(const std::string &name, NativeType value, const std::string &strType) {
    if (mUMulMapProperty.empty() == false) {
      auto &it = std::find_if(std::begin(mUMulMapProperty), std::end(mUMulMapProperty),
                              [&name](const decltype(mUMulMapProperty)::reference pair) {
                                if (pair.first.compare(name) == 0 && pair.second->mType == enumType)
                                  return true;
                                return false;
                              });
      if (it != std::end(mUMulMapProperty)) {
        throw PropertyAlreadyAdded(name, strType);
      }
    }
    std::unique_ptr<PropertyValue> pValue = std::unique_ptr<PropertyValue>(new PropertyValue(enumType));
    pValue->setValue<NativeType>(value);
    mUMulMapProperty.insert({name, std::move(pValue)});
    notifyEvent(Interface::InterfacePropertyEventHandler::EventType::ADDING, name);
  }
  template <typename NativeType, ValueType enumType>
  void setProperty(const std::string &name, NativeType value, const std::string &strType) {
    auto &it = std::find_if(std::begin(mUMulMapProperty), std::end(mUMulMapProperty),
                            [&name](const decltype(mUMulMapProperty)::reference pair) {
                              if (pair.first.compare(name) == 0 && pair.second->mType == enumType)
                                return true;
                              return false;
                            });
    if (it == std::end(mUMulMapProperty)) {
      throw PropertyNotAdded(name, strType);
    } else {
      it->second->setValue<NativeType>(value);
      notifyEvent(Interface::InterfacePropertyEventHandler::EventType::UPDATING, name);
    }
  }
  template <typename NativeType, ValueType enumType>
  NativeType getProperty(const std::string &name, const std::string &strType) const{
    auto &it = std::find_if(std::begin(mUMulMapProperty), std::end(mUMulMapProperty),
                            [&](const decltype(mUMulMapProperty)::value_type &pair) {
                              if (pair.first.compare(name) == 0 && pair.second->mType == enumType)
                                return true;
                              return false;
                            });
    if (it == std::end(mUMulMapProperty)) {
      throw PropertyNotAdded(name, strType);
    }
    return it->second->getValue<NativeType>();
  }

private:
  std::unordered_multimap<std::string, std::unique_ptr<PropertyValue>> mUMulMapProperty;
  std::list<std::weak_ptr<Interface::InterfacePropertyEventHandler>> mVecPropertyListner;
};
} // namespace Core
} // namespace AppFramework

#endif // AppFramework_Core_Property_h_
