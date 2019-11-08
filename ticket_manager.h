#ifndef TICKET_MANAGER_H
#define TICKET_MANAGER_H

#include "b_tree.h"
#include <string>

class ticket_manager {
   public:
      ticket_manager();
      ~ticket_manager();
      int createNewTicket(std::string);
      void processTicket();
      void viewTicket(int);
   private:
      void writeToFile();
      int sequence = 1;
      int currentlyServing = 1;
      b_tree<int,ticket*,4> * tree;
};


#endif
