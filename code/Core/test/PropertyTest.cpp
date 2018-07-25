
#include "gtest/gtest.h"

#include <map>
#include <memory>
//
// #include "AppFramework/Core/Property.h"
// #include "AppFramework/Core/PropertyException.h"
// //
// // #include <iostream>
// //${gtest_SOURCE_DIR}/include
// using AppFramework::Core::Property;
// using AppFramework::Interface::InterfacePropertyEventHandler;
// // using AppFramework::Interface::InterfacePropertyEventHandler::EventType;
// using AppFramework::Interface::InterfaceProperty;
// /// should pass without any exception
// TEST(PropertyTest, Constructor) {
//   try {
//     Property oProp;
//   } catch (...) {
//     FAIL();
//   }
// }
//
// /// adding property
// TEST(PropertyTest, AddProperty) {
//   try {
//     Property oProp;
//     oProp.addBoolProperty("bool", true);
//     oProp.addInt8Property("int8", 1);
//     oProp.addInt16Property("int16", 2);
//     oProp.addInt32Property("int32", 3);
//     oProp.addInt64Property("int64", 4);
//     oProp.addStringProperty("string", "string");
//   } catch (...) {
//     FAIL();
//   }
// }
//
// /// adding duplicate property of same type
// TEST(PropertyTest, AddDuplicateProperty1) {
//   try {
//     Property oProp;
//     oProp.addBoolProperty("bool", true);
//     oProp.addBoolProperty("bool", false);
//     FAIL();
//   } catch (const AppFramework::Core::PropertyAlreadyAdded &ex) {
//   } catch (...) {
//     FAIL();
//   }
// }
//
// /// adding duplicate property of different type
// TEST(PropertyTest, AddDuplicateProperty2) {
//   try {
//     Property oProp;
//     oProp.addBoolProperty("bool", true);
//     oProp.addInt8Property("bool", false);
//   } catch (...) {
//     FAIL();
//   }
// }
//
// /// add/set property
// TEST(PropertyTest, AddSetProperty) {
//   try {
//     Property oProp;
//     oProp.addBoolProperty("bool", true);
//     oProp.addInt8Property("int8", 1);
//     oProp.addInt16Property("int16", 2);
//     oProp.addInt32Property("int32", 3);
//     oProp.addInt64Property("int64", 4);
//     oProp.addStringProperty("string", "string");
//     oProp.setBoolProperty("bool", false);
//     oProp.setInt8Property("int8", 11);
//     oProp.setInt16Property("int16", 21);
//     oProp.setInt32Property("int32", 31);
//     oProp.setInt64Property("int64", 41);
//     oProp.setStringProperty("string", "string1");
//   } catch (...) {
//     FAIL();
//   }
// }
//
// /// set property
// TEST(PropertyTest, SetProperty) {
//   try {
//     Property oProp;
//     oProp.setBoolProperty("bool", false);
//     oProp.setInt8Property("int8", 11);
//     oProp.setInt16Property("int16", 21);
//     oProp.setInt32Property("int32", 31);
//     oProp.setInt64Property("int64", 41);
//     oProp.setStringProperty("string", "string1");
//     FAIL();
//   } catch (const AppFramework::Core::PropertyNotAdded &ex) {
//   } catch (...) {
//     FAIL();
//   }
// }
//
// /// add/get property
// TEST(PropertyTest, AddGetProperty) {
//   try {
//     Property oProp;
//     oProp.addBoolProperty("bool", true);
//     oProp.addInt8Property("int8", 1);
//     oProp.addInt16Property("int16", 2);
//     oProp.addInt32Property("int32", 3);
//     oProp.addInt64Property("int64", 4);
//     oProp.addStringProperty("string", "string");
//     EXPECT_EQ(oProp.getBoolProperty("bool"), true);
//     EXPECT_EQ(oProp.getInt8Property("int8"), 1);
//     EXPECT_EQ(oProp.getInt16Property("int16"), 2);
//     EXPECT_EQ(oProp.getInt32Property("int32"), 3);
//     EXPECT_EQ(oProp.getInt64Property("int64"), 4);
//     EXPECT_EQ(oProp.getStringProperty("string"), "string");
//   } catch (...) {
//     FAIL();
//   }
// }
//
// /// add/set/get property
// TEST(PropertyTest, AddSetGetProperty) {
//   try {
//     Property oProp;
//     oProp.addBoolProperty("bool", true);
//     oProp.addInt8Property("int8", 1);
//     oProp.addInt16Property("int16", 2);
//     oProp.addInt32Property("int32", 3);
//     oProp.addInt64Property("int64", 4);
//     oProp.addStringProperty("string", "string");
//     oProp.setBoolProperty("bool", false);
//     oProp.setInt8Property("int8", 11);
//     oProp.setInt16Property("int16", 21);
//     oProp.setInt32Property("int32", 31);
//     oProp.setInt64Property("int64", 41);
//     oProp.setStringProperty("string", "string1");
//     EXPECT_EQ(oProp.getBoolProperty("bool"), false);
//     EXPECT_EQ(oProp.getInt8Property("int8"), 11);
//     EXPECT_EQ(oProp.getInt16Property("int16"), 21);
//     EXPECT_EQ(oProp.getInt32Property("int32"), 31);
//     EXPECT_EQ(oProp.getInt64Property("int64"), 41);
//     EXPECT_EQ(oProp.getStringProperty("string"), "string1");
//   } catch (...) {
//     FAIL();
//   }
// }
//
// TEST(PropertyTest, PropertyEventHandler1) {
//   try {
//     Property oProp;
//     class handler : public InterfacePropertyEventHandler {
//       virtual void onPropertyEvent(EventType type, const std::string &name,
//                                    const InterfaceProperty &oProperty) override {
//         eventCount[type]++;
//       }
//
//     public:
//       std::map<int, int> eventCount;
//     };
//     std::shared_ptr<handler> spHandler = std::make_shared<handler>();
//     oProp.addPropertyListner(spHandler);
//     oProp.addBoolProperty("bool", true);
//     oProp.addInt8Property("int8", 1);
//     oProp.addInt16Property("int16", 2);
//     oProp.addInt32Property("int32", 3);
//     oProp.addInt64Property("int64", 4);
//     oProp.addStringProperty("string", "string");
//     EXPECT_EQ(spHandler->eventCount[handler::EventType::ADDING], 6);
//     oProp.setBoolProperty("bool", false);
//     oProp.setInt8Property("int8", 11);
//     oProp.setInt16Property("int16", 21);
//     oProp.setInt32Property("int32", 31);
//     oProp.setInt64Property("int64", 41);
//     oProp.setStringProperty("string", "string1");
//     EXPECT_EQ(spHandler->eventCount[handler::EventType::UPDATING], 6);
//     oProp.removeBoolProperty("bool");
//     oProp.removeInt8Property("int8");
//     oProp.removeInt16Property("int16");
//     oProp.removeInt32Property("int32");
//     oProp.removeInt64Property("int64");
//     oProp.removeStringProperty("string");
//     EXPECT_EQ(spHandler->eventCount[handler::EventType::REMOVING], 6);
//   } catch (...) {
//     FAIL();
//   }
// }
//
// TEST(PropertyTest, PropertyEventHandler2) {
//   try {
//     Property oProp;
//     class handler : public InterfacePropertyEventHandler {
//       virtual void onPropertyEvent(EventType type, const std::string &name,
//                                    const InterfaceProperty &oProperty) override {
//         // eventCount[type]++;
//         mName = name;
//       }
//
//     public:
//       // std::map<int, int> eventCount;
//       std::string mName;
//     };
//     std::shared_ptr<handler> spHandler = std::make_shared<handler>();
//     oProp.addPropertyListner(spHandler);
//     oProp.addBoolProperty("bool", true);
//     oProp.addInt8Property("int8", 1);
//     oProp.addInt16Property("int16", 2);
//     oProp.addInt32Property("int32", 3);
//     oProp.addInt64Property("int64", 4);
//     oProp.addStringProperty("string", "string");
//     EXPECT_EQ(spHandler->eventCount[handler::EventType::ADDING], 6);
//     oProp.setBoolProperty("bool", false);
//     oProp.setInt8Property("int8", 11);
//     oProp.setInt16Property("int16", 21);
//     oProp.setInt32Property("int32", 31);
//     oProp.setInt64Property("int64", 41);
//     oProp.setStringProperty("string", "string1");
//     EXPECT_EQ(spHandler->eventCount[handler::EventType::UPDATING], 6);
//     oProp.removeBoolProperty("bool");
//     oProp.removeInt8Property("int8");
//     oProp.removeInt16Property("int16");
//     oProp.removeInt32Property("int32");
//     oProp.removeInt64Property("int64");
//     oProp.removeStringProperty("string");
//     EXPECT_EQ(spHandler->eventCount[handler::EventType::REMOVING], 6);
//   } catch (...) {
//     FAIL();
//   }
// }
