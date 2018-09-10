/// File: Main.cpp
/// Author : Manthan R. Tilva
/// Date : 08/08/2018
/// Brief :

#include <csignal>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "AppFramework/Core/CommandLine.h"

#include "json/json.h"

static bool gSignalStatus = true;
void signal_handler(int signal)
{
  gSignalStatus = false;
}

int main(int argc, char **argv) {
  std::signal(SIGINT, signal_handler);
  using AppFramework::Core::CommandLine;
  try {
    CommandLine cl(argc, argv);
    cl.addDefault<std::string>("config", "path to json config file","config.json");
    cl.run();
    std::string strConfFile = cl.get<std::string>("config");
    Json::Value oConfig;
    Json::Reader reader;
    std::ifstream ifs{strConfFile};
    if(reader.parse(ifs,oConfig)){
      std::cout<<oConfig<<std::endl;
    }
    else{
      std::cout<<reader.getFormattedErrorMessages()<<std::endl;
    }
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  catch(...) { std::cout << "unknown exception" << std::endl; }
  std::cout<<"Leaving loop"<<std::endl;
  return 0;
}
