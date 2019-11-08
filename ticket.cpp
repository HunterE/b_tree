#include "ticket.h"
#include <string>
#include <sstream>

ticket::ticket(){
   pending = true;
}

ticket::ticket(std::string data){
   pending = true;
}

ticket::~ticket(){

}

void ticket::deserialize(std::string data){
   std::stringstream stream;
   std::string str;
   stream << data;

   std::getline(stream, str);
   this->name = str;
   std::getline(stream, str);
   this->email = str;
   std::getline(stream, str);
   this->description = str;
}
