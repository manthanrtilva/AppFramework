
/// File: InterfaceProperty.h
/// Author : Manthan R. Tilva
/// Date : 17/07/2018
/// Brief : Interface to interacte with propery class

#include <cstdint>
#include <string>
namespace AppFramework {
namespace Interface {
class InterfaceProperty;
class InterfacePropertyEventHandler {
public:
  enum EventType { ADDING, REMOVING, UPDATING };
  virtual void onPropertyEvent(EventType type, const std::string &name,
                               const InterfaceProperty &oProperty) = 0;
};
class InterfaceProperty {
public:
  virtual void addBoolProperty(const std::string &name, bool value) = 0;
  virtual void addInt8Property(const std::string &name,
                               const std::int8_t &value) = 0;
  virtual void addInt16Property(const std::string &name,
                                const std::int16_t &value) = 0;
  virtual void addInt32Property(const std::string &name,
                                const std::int32_t &value) = 0;
  virtual void addInt64Property(const std::string &name,
                                const std::int64_t &value) = 0;
  virtual void addStringProperty(const std::string &name,
                                 const std::string &value) = 0;
  virtual void setBoolProperty(const std::string &name, bool value) = 0;
  virtual void setInt8Property(const std::string &name,
                               const std::int8_t &value) = 0;
  virtual void setInt16Property(const std::string &name,
                                const std::int16_t &value) = 0;
  virtual void setInt32Property(const std::string &name,
                                const std::int32_t &value) = 0;
  virtual void setInt64Property(const std::string &name,
                                const std::int64_t &value) = 0;
  virtual void setStringProperty(const std::string &name,
                                 const std::string &value) = 0;
  virtual bool getBoolProperty(const std::string &name) const = 0;
  virtual std::int8_t getInt8Property(const std::string &name) const = 0;
  virtual std::int16_t getInt16Property(const std::string &name) const = 0;
  virtual std::int32_t getInt32Property(const std::string &name) const = 0;
  virtual std::int64_t getInt64Property(const std::string &name) const = 0;
  virtual std::string getStringProperty(const std::string &name) const = 0;
  virtual void removeProperty(const std::string &name) = 0;
};
} // namespace Interface
} // namespace AppFramework
