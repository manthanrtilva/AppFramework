
/// File: Property.cpp
/// Author : Manthan R. Tilva
/// Date : 17/07/2018
/// Brief : Defination to interacte with propery class

#include "AppFramework/Core/Property.h"

#include <algorithm>
#include <iostream>

#include "AppFramework/Core/PropertyException.h"

namespace AppFramework {
namespace Core {
Property::Property() {}
Property::~Property() {}
void Property::addBoolProperty(const std::string &name, bool value) {
  addProperty<bool, ValueType::BOOL>(name, value, "bool");
}
void Property::addInt8Property(const std::string &name, const std::int8_t &value) {
  addProperty<std::int8_t, ValueType::INT8>(name, value, "std::int8_t");
}
void Property::addInt16Property(const std::string &name, const std::int16_t &value) {
  addProperty<std::int16_t, ValueType::INT16>(name, value, "std::int16_t");
}
void Property::addInt32Property(const std::string &name, const std::int32_t &value) {
  addProperty<std::int32_t, ValueType::INT32>(name, value, "std::int32_t");
}
void Property::addInt64Property(const std::string &name, const std::int64_t &value) {
  addProperty<std::int64_t, ValueType::INT64>(name, value, "std::int64_t");
}
void Property::addStringProperty(const std::string &name, const std::string &value) {
  addProperty<std::string, ValueType::STRING>(name, value, "std::string");
}
void Property::setBoolProperty(const std::string &name, bool value) {
  setProperty<bool, ValueType::BOOL>(name, value, "bool");
}
void Property::setInt8Property(const std::string &name, const std::int8_t &value) {
  setProperty<std::int8_t, ValueType::INT8>(name, value, "std::int8_t");
}
void Property::setInt16Property(const std::string &name, const std::int16_t &value) {
  setProperty<std::int16_t, ValueType::INT16>(name, value, "std::int16_t");
}
void Property::setInt32Property(const std::string &name, const std::int32_t &value) {
  setProperty<std::int32_t, ValueType::INT32>(name, value, "std::int32_t");
}
void Property::setInt64Property(const std::string &name, const std::int64_t &value) {
  setProperty<std::int64_t, ValueType::INT64>(name, value, "std::int64_t");
}
void Property::setStringProperty(const std::string &name, const std::string &value) {
  setProperty<std::string, ValueType::STRING>(name, value, "std::string");
}
bool Property::getBoolProperty(const std::string &name) const {
  return getProperty<bool, ValueType::BOOL>(name, "bool");
}
std::int8_t Property::getInt8Property(const std::string &name) const {
  return getProperty<std::int8_t, ValueType::INT8>(name, "std::int8_t");
}
std::int16_t Property::getInt16Property(const std::string &name) const {
  return getProperty<std::int16_t, ValueType::INT16>(name, "std::int16_t");
}
std::int32_t Property::getInt32Property(const std::string &name) const {
  return getProperty<std::int32_t, ValueType::INT32>(name, "std::int32_t");
}
std::int64_t Property::getInt64Property(const std::string &name) const {
  return getProperty<std::int64_t, ValueType::INT64>(name, "std::int64_t");
}
std::string Property::getStringProperty(const std::string &name) const {
  return getProperty<std::string, ValueType::STRING>(name, "std::string");
}
void Property::removeBoolProperty(const std::string &name) { removeProperty<ValueType::BOOL>(name, "bool"); }
void Property::removeInt8Property(const std::string &name) { removeProperty<ValueType::INT8>(name, "std::int8_t"); }
void Property::removeInt16Property(const std::string &name) { removeProperty<ValueType::INT16>(name, "std::int16_t"); }
void Property::removeInt32Property(const std::string &name) { removeProperty<ValueType::INT32>(name, "std::int32_t"); }
void Property::removeInt64Property(const std::string &name) { removeProperty<ValueType::INT64>(name, "std::int64_t"); }
void Property::removeStringProperty(const std::string &name) { removeProperty<ValueType::STRING>(name, "std::string"); }
} // namespace Core
} // namespace AppFramework
