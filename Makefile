CPP = g++
CXXFLAGS = -std=c++14 -I./include -Wall -Werror -Wextra
LDFLAGS = -lSDL2 -I/usr/include/SDL2

OBJECTS = main.o noise.o colors.o

main: $(OBJECTS)
	$(CPP) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(OBJECTS): ./include/*

.PHONY: clean

clean:
	rm -f main *.ppm *.pbm *.o
