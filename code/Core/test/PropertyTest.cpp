
#include "gtest/gtest.h"

#include <map>
#include <memory>

#include "AppFramework/Core/Property.h"
#include "AppFramework/Core/PropertyException.h"

using AppFramework::Core::Property;
TEST(PropertyTest, Constructor) {
  try {
    Property oProp;
  } catch (...) {
    FAIL();
  }
}

/// adding property
TEST(PropertyTest, AddProperty) {
  try {
    Property oProp;
    oProp.addProperty<bool>("bool", true);
    oProp.addProperty<std::int8_t>("int8", 1);
    oProp.addProperty<std::int16_t>("int16", 2);
    oProp.addProperty<std::int32_t>("int32", 3);
    oProp.addProperty<std::int64_t>("int64", 4);
    oProp.addProperty<std::string>("string", "string");
  } catch (...) {
    FAIL();
  }
}

/// adding duplicate property of same type
TEST(PropertyTest, AddDuplicateProperty1) {
  try {
    Property oProp;
    oProp.addProperty<bool>("bool", true);
    oProp.addProperty<bool>("bool", false);
    FAIL();
  } catch (const AppFramework::Core::PropertyAlreadyAdded &ex) {
  } catch (...) {
    FAIL();
  }
}

/// adding duplicate property of different type
TEST(PropertyTest, AddDuplicateProperty2) {
  try {
    Property oProp;
    oProp.addProperty<bool>("bool", true);
    oProp.addProperty<std::int8_t>("bool", false);
  } catch (...) {
    FAIL();
  }
}

/// add/set property
TEST(PropertyTest, AddSetProperty) {
  try {
    Property oProp;
    oProp.addProperty<bool>("bool", true);
    oProp.addProperty<std::int8_t>("int8", 1);
    oProp.addProperty<std::int16_t>("int16", 2);
    oProp.addProperty<std::int32_t>("int32", 3);
    oProp.addProperty<std::int64_t>("int64", 4);
    oProp.addProperty<std::string>("string", "string");
    oProp.setProperty<bool>("bool", false);
    oProp.setProperty<std::int8_t>("int8", 11);
    oProp.setProperty<std::int16_t>("int16", 21);
    oProp.setProperty<std::int32_t>("int32", 31);
    oProp.setProperty<std::int64_t>("int64", 41);
    oProp.setProperty<std::string>("string", "string1");
  } catch (...) {
    FAIL();
  }
}

/// set property
TEST(PropertyTest, SetProperty) {
  try {
    Property oProp;
    oProp.setProperty<bool>("bool", false);
    oProp.setProperty<std::int8_t>("int8", 11);
    oProp.setProperty<std::int16_t>("int16", 21);
    oProp.setProperty<std::int32_t>("int32", 31);
    oProp.setProperty<std::int64_t>("int64", 41);
    oProp.setProperty<std::string>("string", "string1");
    FAIL();
  } catch (const AppFramework::Core::PropertyNotAdded &ex) {
  } catch (...) {
    FAIL();
  }
}

/// add/get property
TEST(PropertyTest, AddGetProperty) {
  try {
    Property oProp;
    oProp.addProperty<bool>("bool", true);
    oProp.addProperty<std::int8_t>("int8", 1);
    oProp.addProperty<std::int16_t>("int16", 2);
    oProp.addProperty<std::int32_t>("int32", 3);
    oProp.addProperty<std::int64_t>("int64", 4);
    oProp.addProperty<std::string>("string", "string");
    oProp.setProperty<bool>("bool", false);
    oProp.setProperty<std::int8_t>("int8", 11);
    oProp.setProperty<std::int16_t>("int16", 21);
    oProp.setProperty<std::int32_t>("int32", 31);
    oProp.setProperty<std::int64_t>("int64", 41);
    oProp.setProperty<std::string>("string", "string1");
    EXPECT_EQ(oProp.getProperty<bool>("bool"), false);
    EXPECT_EQ(oProp.getProperty<std::int8_t>("int8"), 11);
    EXPECT_EQ(oProp.getProperty<std::int16_t>("int16"), 21);
    EXPECT_EQ(oProp.getProperty<std::int32_t>("int32"), 31);
    EXPECT_EQ(oProp.getProperty<std::int64_t>("int64"), 41);
    EXPECT_EQ(oProp.getProperty<std::string>("string"), "string1");
  } catch (...) {
    FAIL();
  }
}

/// add/set/get property
TEST(PropertyTest, AddSetGetProperty) {
  try {
    Property oProp;
    oProp.addProperty<bool>("bool", true);
    oProp.addProperty<std::int8_t>("int8", 1);
    oProp.addProperty<std::int16_t>("int16", 2);
    oProp.addProperty<std::int32_t>("int32", 3);
    oProp.addProperty<std::int64_t>("int64", 4);
    oProp.addProperty<std::string>("string", "string");
    EXPECT_EQ(oProp.getProperty<bool>("bool"), true);
    EXPECT_EQ(oProp.getProperty<std::int8_t>("int8"), 1);
    EXPECT_EQ(oProp.getProperty<std::int16_t>("int16"), 2);
    EXPECT_EQ(oProp.getProperty<std::int32_t>("int32"), 3);
    EXPECT_EQ(oProp.getProperty<std::int64_t>("int64"), 4);
    EXPECT_EQ(oProp.getProperty<std::string>("string"), "string");
  } catch (...) {
    FAIL();
  }
}

TEST(PropertyTest, PropertyEventHandler1) {
  try {
    class handler : public Property::EventHandler {
      virtual void onPropertyEvent(EventType type, const std::string &name, const std::type_info &info,
                                   const Property &oProperty) override {
        eventCount[type]++;
      }

    public:
      std::map<int, int> eventCount;
    };
    auto spHandler = std::make_shared<handler>();
    Property oProp;
    oProp.addPropertyListner(spHandler);
    oProp.addProperty<bool>("bool", true);
    oProp.addProperty<std::int8_t>("int8", 1);
    oProp.addProperty<std::int16_t>("int16", 2);
    oProp.addProperty<std::int32_t>("int32", 3);
    oProp.addProperty<std::int64_t>("int64", 4);
    oProp.addProperty<std::string>("string", "string");
    EXPECT_EQ(spHandler->eventCount[handler::EventType::ADDING], 6);
    oProp.setProperty<bool>("bool", false);
    oProp.setProperty<std::int8_t>("int8", 11);
    oProp.setProperty<std::int16_t>("int16", 21);
    oProp.setProperty<std::int32_t>("int32", 31);
    oProp.setProperty<std::int64_t>("int64", 41);
    oProp.setProperty<std::string>("string", "string1");
    EXPECT_EQ(spHandler->eventCount[handler::EventType::UPDATING], 6);
    oProp.removeProperty<bool>("bool");
    oProp.removeProperty<std::int8_t>("int8");
    oProp.removeProperty<std::int16_t>("int16");
    oProp.removeProperty<std::int32_t>("int32");
    oProp.removeProperty<std::int64_t>("int64");
    oProp.removeProperty<std::string>("string");
    EXPECT_EQ(spHandler->eventCount[handler::EventType::REMOVING], 6);
  } catch (...) {
    FAIL();
  }
}

TEST(PropertyTest, PropertyEventHandler2) {
  try {
    class handler : public Property::EventHandler {
      virtual void onPropertyEvent(EventType type, const std::string &name, const std::type_info &info,
                                   const Property &oProperty) override {
        mType = type;
        mName = name;
        mTypeName = info.name();
      }

    public:
      // std::map<int, int> eventCount;
      EventType mType;
      std::string mName;
      std::string mTypeName;
    };
    auto spHandler = std::make_shared<handler>();
    Property oProp;
    oProp.addPropertyListner(spHandler);
    oProp.addProperty<bool>("bool", true);
    EXPECT_EQ(spHandler->mType, handler::EventType::ADDING);
    EXPECT_EQ(spHandler->mName, "bool");
    EXPECT_EQ(spHandler->mTypeName, typeid(bool).name());
    oProp.addProperty<std::int8_t>("int8", 1);
    EXPECT_EQ(spHandler->mType, handler::EventType::ADDING);
    EXPECT_EQ(spHandler->mName, "int8");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int8_t).name());
    oProp.addProperty<std::int16_t>("int16", 2);
    EXPECT_EQ(spHandler->mType, handler::EventType::ADDING);
    EXPECT_EQ(spHandler->mName, "int16");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int16_t).name());
    oProp.addProperty<std::int32_t>("int32", 3);
    EXPECT_EQ(spHandler->mType, handler::EventType::ADDING);
    EXPECT_EQ(spHandler->mName, "int32");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int32_t).name());
    oProp.addProperty<std::int64_t>("int64", 4);
    EXPECT_EQ(spHandler->mType, handler::EventType::ADDING);
    EXPECT_EQ(spHandler->mName, "int64");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int64_t).name());
    oProp.addProperty<std::string>("string", "string");
    EXPECT_EQ(spHandler->mType, handler::EventType::ADDING);
    EXPECT_EQ(spHandler->mName, "string");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::string).name());
    oProp.setProperty<bool>("bool", false);
    EXPECT_EQ(spHandler->mType, handler::EventType::UPDATING);
    EXPECT_EQ(spHandler->mName, "bool");
    EXPECT_EQ(spHandler->mTypeName, typeid(bool).name());
    oProp.setProperty<std::int8_t>("int8", 1);
    EXPECT_EQ(spHandler->mType, handler::EventType::UPDATING);
    EXPECT_EQ(spHandler->mName, "int8");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int8_t).name());
    oProp.setProperty<std::int16_t>("int16", 2);
    EXPECT_EQ(spHandler->mType, handler::EventType::UPDATING);
    EXPECT_EQ(spHandler->mName, "int16");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int16_t).name());
    oProp.setProperty<std::int32_t>("int32", 3);
    EXPECT_EQ(spHandler->mType, handler::EventType::UPDATING);
    EXPECT_EQ(spHandler->mName, "int32");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int32_t).name());
    oProp.setProperty<std::int64_t>("int64", 4);
    EXPECT_EQ(spHandler->mType, handler::EventType::UPDATING);
    EXPECT_EQ(spHandler->mName, "int64");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int64_t).name());
    oProp.setProperty<std::string>("string", "string");
    EXPECT_EQ(spHandler->mType, handler::EventType::UPDATING);
    EXPECT_EQ(spHandler->mName, "string");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::string).name());
    oProp.removeProperty<bool>("bool");
    EXPECT_EQ(spHandler->mType, handler::EventType::REMOVING);
    EXPECT_EQ(spHandler->mName, "bool");
    EXPECT_EQ(spHandler->mTypeName, typeid(bool).name());
    oProp.removeProperty<std::int8_t>("int8");
    EXPECT_EQ(spHandler->mType, handler::EventType::REMOVING);
    EXPECT_EQ(spHandler->mName, "int8");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int8_t).name());
    oProp.removeProperty<std::int16_t>("int16");
    EXPECT_EQ(spHandler->mType, handler::EventType::REMOVING);
    EXPECT_EQ(spHandler->mName, "int16");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int16_t).name());
    oProp.removeProperty<std::int32_t>("int32");
    EXPECT_EQ(spHandler->mType, handler::EventType::REMOVING);
    EXPECT_EQ(spHandler->mName, "int32");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int32_t).name());
    oProp.removeProperty<std::int64_t>("int64");
    EXPECT_EQ(spHandler->mType, handler::EventType::REMOVING);
    EXPECT_EQ(spHandler->mName, "int64");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::int64_t).name());
    oProp.removeProperty<std::string>("string");
    EXPECT_EQ(spHandler->mType, handler::EventType::REMOVING);
    EXPECT_EQ(spHandler->mName, "string");
    EXPECT_EQ(spHandler->mTypeName, typeid(std::string).name());
  } catch (...) {
    FAIL();
  }
}
