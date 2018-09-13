
#include <iostream>
#include <string>
#include <vector>

#include <boost/dll/import.hpp>
#include <boost/function.hpp>

#include "AppFramework/Core/Component.h"

using AppFramework::Core::Component;

int main(int argc, char **argv) {
  std::vector<std::string> vecStrPlugin{"QtPlugin.plug"};
  std::vector<boost::function<Component::component_create_t>> vecCreator;
  std::vector<std::shared_ptr<Component>> vecComponent;
  for (auto &str : vecStrPlugin) {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    std::cout << std::string(argv[1]).append(str) << std::endl;
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    auto creator = boost::dll::import_alias<Component::component_create_t>(
        std::string(argv[1]).append(str), "create_component", boost::dll::load_mode::append_decorations);
        std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    vecComponent.push_back(std::move(creator(str)));
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    vecCreator.push_back(std::move(creator));
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
  }
  for(auto &comp:vecComponent) {
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    comp->setState(Component::State::CONFIGURE);
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    comp->setState(Component::State::RUN);
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
    comp->setState(Component::State::STOP);
    std::cout << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << std::endl;
  }
  return 0;
}
