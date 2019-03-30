#For local build configuration MinGW, Dynrpg, etc..
-include local.mk
DYNRPG ?= dynrpg
CXX ?= g++.exe

CPPFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 -I$(DYNRPG)/include
CXXFLAGS=-std=c++11
LDFLAGS=-L$(DYNRPG)/lib -lDynRPG

eventtrace.dll: eventtrace.o
	$(CXX) -shared -o $@ $^ -Wl,--out-implib,lib$(basename $@).a $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $^

all: eventtrace.dll
	
clean:
	rm *.a || del *.a
	rm *.o || del *.o
	rm *.dll || del *.dll

install: all
	install eventtrace.dll $(DESTDIR)
