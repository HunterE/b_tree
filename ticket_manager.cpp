#include "ticket_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string filepath = "TicketsInfo.txt";

void ticket_manager::writeToFile(){
   std::ofstream fstream;
   fstream.open(filepath);

   bool corrupted = false;

   for(int i = 1; i<sequence; ++i){
      ticket * t ;
      if(!tree->retrieve(i,t)){
         corrupted = true;
         continue;
      }
      fstream << "Ticket #"<<i<<"\n";
      fstream << "  Submitter: " << t->name << "\n";
      fstream << "      Email: " << t->email << "\n";
      fstream << "Description: " << t->description << "\n";
      fstream << "     Status: " << (t->pending ? "Pending":"Processed") << "\n";
   }
   if(corrupted){
      fstream << "ATTENTION: While retrieving tickets an error was encountered. This list may not be complete.";
   }
}

ticket_manager::ticket_manager(){
   tree = new b_tree<int,ticket*,4>();
}

ticket_manager::~ticket_manager(){
   writeToFile();

   delete tree;
}

ticket * deserialize(std::string data){
   std::stringstream stream;
   std::string str;
   stream << data;

   ticket * t = new ticket();
   std::getline(stream, str);
   t->name = str;

   std::getline(stream, str);
   t->email = str;

   std::getline(stream, str);
   t->description = str;

   return t;
}

int ticket_manager::createNewTicket(std::string str){
   ticket * t = deserialize(str);
   tree->insert(sequence++,t);
   return sequence - 1;
}

void displayTicket(ticket * t){
   std::cout << "  Submitter: " << t->name << "\n";
   std::cout << "      Email: " << t->email << "\n";
   std::cout << "Description: " << t->description << "\n";
   std::cout << "     Status: " << (t->pending ? "Pending":"Processed") << "\n";
}

void ticket_manager::processTicket(){
   if(currentlyServing >= sequence){
      std::cout << "No unprocessed tickets!\n";
      return;
   }

   ticket * t;
   if(!tree->retrieve(currentlyServing++,t)){
      std::cout << "ERROR: Could not find ticket with ID " << currentlyServing << ".\n";
      currentlyServing--;
   }
   std::cout << "Ticket #" << currentlyServing-1 << "\n";
   displayTicket(t);
   t->pending = false;
}

void ticket_manager::viewTicket(int id){
   if(id >= sequence || id < 1){
      std::cout << "Ticket ID "<<id << " is invalid.\n";
      return;
   }

   ticket * t;
   if(!tree->retrieve(id,t)){
      std::cout << "Could not find a ticket with ID " << id << ".\n";
      return;
   }

   std::cout << "Ticket #" << id << "\n";
   displayTicket(t);
}


