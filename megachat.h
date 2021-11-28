#ifndef MEGACHAT_FNCTNS_H
#define MEGACHAT_FNCTNS_H

#include <iostream>
#include "base64.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <stdio.h>
#include <cstring>

namespace MegaChat{
  namespace Sys{

    // from https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
    std::string Exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


  }
  namespace Radio{
    // recieve and transmit messages
    typedef enum {LOCAL, ABROAD}Origin;
    class Message{
    public:
      std::string username;
      std::string message;
      Origin origin;
    };
    class Client{
    public:
      std::string username;
Origin origin;
    };


void SendMessage(std::string url, Message msg, std::string separator){
  std::string tempstring;
  tempstring = msg.username + separator + msg.message;
  tempstring = base64::encode(tempstring);
  std::string tempstring2 = "curl --insecure '" + url + "/mega.php?try=send&msg=";
  tempstring = tempstring2 + tempstring+"'";


  system(tempstring.c_str());
}

void GetLog(std::string address){
  system("clear");
  std::string temp = "curl --insecure " + address + "/mega.php?try=get";
  std::cout<<Sys::Exec(temp.c_str());
}

  }
  namespace UI{
    class Log{
    public:
      std::string log;
      void UpdateLog(Radio::Message msg, std::string separator);
    };
    class MegaContext{
    public:
      Log log;
      Radio::Client user;
      std::string address;
      void UpdateRender();
    };
    void Log::UpdateLog(Radio::Message msg, std::string separator){
      log = log + "\n" + msg.username + separator + msg.message;
    }
    void MegaContext::UpdateRender(){
      // this code is platform dependent as it uses command prompt instructions
      system("clear");
      std::cout << log.log;
    }

  }
}

#endif
