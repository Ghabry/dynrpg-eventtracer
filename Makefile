CC ?= g++
DYNRPG ?= dynrpg

eventtrace: eventtrace.o
	$(CC) -shared -o eventtrace.dll eventtrace.o -Wl,--out-implib,libeventtrace.a

eventtrace.o:
	$(CC) -c -I$(DYNRPG)/include -L$(DYNRPG)/lib -lDynRPG eventtrace.cpp

all: eventtrace
	
clean:
	rm *.a || del *.a
	rm *.o || del *.o
	rm *.dll || del *.dll