
#include "AppFramework/Core/CommandLine.h"

int main(int argc, char **argv) {
  using AppFramework::Core::CommandLine;
  try {
    CommandLine cl(argc, argv);
    cl.addRequired<bool>("bool", "I am bool");
    cl.addRequired<int>("int", "I am int");
    cl.addOptional<bool>("boolO", "I am boolOptional");
    cl.addOptional<double>("doubleO", "I am doubleOptional");
    cl.addDefault<int>("intD", "I am intDefault",10);
    // cl.addOptional<int>("intOptional", "I am intOptional");
    cl.run();
    std::cout<<cl.get<bool>("bool")<<std::endl;
    std::cout<<cl.get<bool>("boolO")<<std::endl;
    std::cout<<cl.get<int>("int")<<std::endl;
    std::cout<<cl.get<int>("intD")<<std::endl;
    std::cout<<cl.get<double>("doubleO")<<std::endl;
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  catch(...) { std::cout << "unknown exception" << std::endl; }
  return 0;
}
