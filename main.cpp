#include <stdio.h>
#include <iostream>
#include "megachat.h"

bool Connected = true;

std::string address;

int main(){


std::string str; // This is the ONLY VARIABLE responsible for user input.
// Don't ask me how I'mma pull this off, I'mma pull this off.


// Init a context and shit
std::cout<<"What's your username? : ";
std::cin >> str;
MegaChat::UI::MegaContext context;
MegaChat::Radio::Client clitmp;
clitmp.username = str;
clitmp.origin = MegaChat::Radio::Origin::LOCAL;

MegaChat::Radio::Message broadcast;
broadcast.username = "\033[32;1;1mGENERAL BROADCAST";

context.user = clitmp;
MegaChat::Radio::Message msg;
msg.username = context.user.username;
std::string sep = " : ";

std::cout<<"What will you connect to? : ";
std::cin >> str;
context.address = str;

while(Connected){
  // context.UpdateRender();
  MegaChat::Radio::GetLog(context.address);
  std::cout<<"\n>> ";
   std::getline(std::cin, str);


// Let's define some commands!

   if(str.rfind("!", 0) == 0){
     if(str.rfind("!broad ", 0) == 0){
       str.erase(0,7);
       str = str+"\033[0m";
       broadcast.message = str;
     }
     if(str.rfind("!changename ", 0) == 0){
       str.erase(0,12);
       context.user.username = str;

     }
     if(str.rfind("!flags", 0)==0) {
     }
     if(str == "!quit" || str == "!exit" || str == "!logout"){
       Connected = false;
     }
   }//Now, this is if NO COMMANDS were entered.
   else{
  msg.message = str;
  SendMessage(context.address, msg, " : ");
  }

msg.username = context.user.username;

}

return 0;

}
