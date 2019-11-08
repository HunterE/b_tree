#include "ticket_manager.h"
#include <iostream>
#include <sstream>
#include <string>

enum class Command {submit=1, process=2, view=3, quit=4, help=5, invalid=6};

std::string buildHelpMenu(){
   std::stringstream stream;
   stream << "HELP" << std::endl;
   stream << "[submit] a new service request" << std::endl;
   stream << "[process] the earliest ticket" <<std::endl;
   stream << "[view] a ticket" << std::endl;
   stream << "[quit] the program" <<std::endl;

   return stream.str();
}
std::string helpMenu = buildHelpMenu();

std::string getUserString(std::string prompt){
   std::cout << prompt;
   std::string input;
   std::getline(std::cin,input);

   return input;
}

std::string toLowerCase(std::string string){
   for(int i = 0; i<string.length(); i++){
      string[i] = tolower(string[i]);
   }
   return string;
}

Command getCommand(){
   std::string command = getUserString("Enter a command: ");
   command = toLowerCase(command);
   if(command == "submit") {return Command::submit;}
   if(command == "process") return Command::process;
   if(command == "view") return Command::view;
   if(command == "quit") return Command::quit;
   if(command == "help") return Command::help;
   return Command::invalid;
}



int main(){
   ticket_manager * manager = new ticket_manager();
   std::cout << helpMenu;
   bool running = true;

   while(running){
      Command c = getCommand();
      switch(c){
         case Command::submit : {
            std::stringstream ss;
            ss << getUserString("                   Enter your name: ") << std::endl;
            ss << getUserString("          Enter your email address: ") << std::endl;
            ss << getUserString("Enter a description of the problem: ") << std::endl;

            int id = manager->createNewTicket(ss.str());
            std::cout << "Ticket submitted. Your confirmation number is "<<id<<"\n";
            //promptCreateEntry(manager);
            break;
         }
         case Command::process : {
            manager->processTicket();
            break;
         }
         case Command::view : {
            manager->viewTicket(std::stoi(getUserString("Enter the ticket number you want to view: ")));
            break;
         }
         case Command::quit : {
            std::cout << "Good bye.\n";
            running = false;
            break;
         }
         case Command::help : {
            std::cout << helpMenu;
            break;
         }
         case Command::invalid : {
            std::cout << "Invalid command. Type 'help' for commands.\n";
         }
      }
   }
   delete manager;
}
