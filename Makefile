#For local build configuration MinGW, Dynrpg, etc..
-include local.mk
MINGW ?= mingw
DYNRPG ?= dynrpg

eventtrace: eventtrace.o
	$(CXX) -shared -o eventtrace.dll eventtrace.o -Wl,--out-implib,libeventtrace.a -L$(DYNRPG)/lib -lDynRPG

eventtrace.o:
	$(CXX) -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0 -c -I$(DYNRPG)/include eventtrace.cpp

all: eventtrace
	
clean:
	rm *.a || del *.a
	rm *.o || del *.o
	rm *.dll || del *.dll
