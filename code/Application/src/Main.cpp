/// File: Main.cpp
/// Author : Manthan R. Tilva
/// Date : 08/08/2018
/// Brief :

#include <csignal>
#include <chrono>
#include <iostream>
#include <thread>

#include "AppFramework/Core/CommandLine.h"

static bool gSignalStatus = true;
void signal_handler(int signal)
{
  gSignalStatus = false;
}

int main(int argc, char const *argv[]) {
  std::signal(SIGINT, signal_handler);
  using AppFramework::Core::CommandLine;
  try {
    CommandLine cl(argc, argv);
    cl.addDefault<std::string>("config", "path to json config file","config.json");
    // cl.addRequired<int>("int", "I am int");
    // cl.addOptional<bool>("boolO", "I am boolOptional");
    // cl.addOptional<double>("doubleO", "I am doubleOptional");
    // cl.addDefault<int>("intD", "I am intDefault",10);
    cl.run();
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  catch(...) { std::cout << "unknown exception" << std::endl; }
  // while(gSignalStatus){
  //   std::this_thread::sleep_for(std::chrono::seconds(1));
  // }
  std::cout<<"Leaving loop"<<std::endl;
  return 0;
}
