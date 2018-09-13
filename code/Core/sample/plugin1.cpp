
#include "AppFramework/Core/Component.h"

#include <boost/config.hpp>

using AppFramework::Core::Component;
// #define __FUNCTION__ __FUNCTION__

class Comp1 : public Component {
public:
  Comp1(const std::string &str) : Component(str) {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
  }
  ~Comp1(){
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
  }
protected:
  virtual void doConfigureImpl() override {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
  }
  virtual void doRunImpl() override { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl; }
  virtual void doStopImpl() override { std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl; }
};

CREATE_COMPONENT(Comp1)
// BOOST_DLL_ALIAS(
//     Component::create<Comp1>, create_component
// )
