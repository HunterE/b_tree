#ifndef TICKET_H
#define TICKET_H

#include <string>

struct ticket {
   public:
      ticket();
      ticket(std::string);
      ~ticket();
      std::string name;
      std::string email;
      std::string description;
      bool pending;
   private:
      void deserialize(std::string);
};

#endif
