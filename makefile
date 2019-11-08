CC=g++
CXXFLAGS=-O
ASN = pex2
SRC = main.cpp b_tree.cpp ticket_manager.cpp ticket.cpp
TST = test.cpp b_tree.cpp

OBJ = $(SRC:.cpp = .o)
TBJ = $(TST:.cpp = .o)

Asn1: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(ASN) $(OBJ)

clean:
	rm -f core *.o

test:
	$(CC) $(CXXFLAGS) -o pex2test $(TBJ)



