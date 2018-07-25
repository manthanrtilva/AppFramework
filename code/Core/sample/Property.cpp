
#include "AppFramework/Core/Property.h"
#include "AppFramework/Core/PropertyException.h"

#include <iostream>

// class Handle1 : public AppFramework::Interface::InterfacePropertyEventHandler {
// public:
//   virtual void onPropertyEvent(AppFramework::Interface::InterfacePropertyEventHandler::EventType type, const std::string &name,
//                                const AppFramework::Interface::InterfaceProperty &oProperty) override {
//                                  std::cout<<"onPropertyEvent:"<<type<<":"<<name<<std::endl;
//                                }
// };
int main(int argc, char const *argv[]) {
  // using AppFramework::Core::Property;
  // Property oProp;
  // std::shared_ptr<AppFramework::Interface::InterfacePropertyEventHandler> sPtrHandler = std::make_shared<Handle1>();
  // oProp.addPropertyListner(sPtrHandler);
  // try {
  //   oProp.addBoolProperty("bool1", false);
  //   oProp.setBoolProperty("bool1", true);
  //   // oProp.setBoolProperty("bool11", true);
  //   // std::cout << oProp.getBoolProperty("bool1") << std::endl;
  //   // std::cout << oProp.getBoolProperty("bool11") << std::endl;
  // } catch (AppFramework::Core::PropertyException &ex) {
  //   std::cout <<"PropertyException:"<< ex.what() << std::endl;
  // } catch (std::exception &ex) {
  //   std::cout << ex.what() << std::endl;
  // }
  //
  // try {
  //   oProp.addBoolProperty("bool1", false);
  //   oProp.setBoolProperty("bool1", true);
  //   // std::cout << oProp.getBoolProperty("bool1") << std::endl;
  //   // std::cout << oProp.getBoolProperty("bool11") << std::endl;
  // } catch (AppFramework::Core::PropertyException &ex) {
  //   std::cout <<"PropertyException:"<< ex.what() << std::endl;
  // } catch (std::exception &ex) {
  //   std::cout << ex.what() << std::endl;
  // }
  return 0;
}
