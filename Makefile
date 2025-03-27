# Project: Project3
# Makefile created by Dev-C++ 4.9.9.2

CPP  = g++.exe
CC   = gcc.exe
WINDRES = windres.exe
RES  = 
OBJ  = AvisClient.o Chaine.o Chambre.o Clients.o Date.o Facture.o Hotel.o Main.o Nourritures.o Reservation.o $(RES)
LINKOBJ  = AvisClient.o Chaine.o Chambre.o Clients.o Date.o Facture.o Hotel.o Main.o Nourritures.o Reservation.o $(RES)
LIBS =  -L"C:/Dev-Cpp/lib"  
INCS =  -I"C:/Dev-Cpp/include" 
CXXINCS =  -I"C:/Dev-Cpp/lib/gcc/mingw32/3.4.2/include"  -I"C:/Dev-Cpp/include/c++/3.4.2/backward"  -I"C:/Dev-Cpp/include/c++/3.4.2/mingw32"  -I"C:/Dev-Cpp/include/c++/3.4.2"  -I"C:/Dev-Cpp/include" 
BIN  = Project3.exe
CXXFLAGS = $(CXXINCS)  
CFLAGS = $(INCS)  
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before Project3.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) $(LINKOBJ) -o "Project3.exe" $(LIBS)

AvisClient.o: AvisClient.c
	$(CC) -c AvisClient.c -o AvisClient.o $(CFLAGS)

Chaine.o: Chaine.c
	$(CC) -c Chaine.c -o Chaine.o $(CFLAGS)

Chambre.o: Chambre.c
	$(CC) -c Chambre.c -o Chambre.o $(CFLAGS)

Clients.o: Clients.c
	$(CC) -c Clients.c -o Clients.o $(CFLAGS)

Date.o: Date.c
	$(CC) -c Date.c -o Date.o $(CFLAGS)

Facture.o: Facture.c
	$(CC) -c Facture.c -o Facture.o $(CFLAGS)

Hotel.o: Hotel.c
	$(CC) -c Hotel.c -o Hotel.o $(CFLAGS)

Main.o: Main.c
	$(CC) -c Main.c -o Main.o $(CFLAGS)

Nourritures.o: Nourritures.c
	$(CC) -c Nourritures.c -o Nourritures.o $(CFLAGS)

Reservation.o: Reservation.c
	$(CC) -c Reservation.c -o Reservation.o $(CFLAGS)
