CPP = g++
CXXFLAGS = -std=c++14 -I./include -Wall -Werror -Wextra

OBJECTS = main.o noise.o colors.o

main: $(OBJECTS)
	$(CPP) $(CXXFLAGS) -o $@ $^

$(OBJECTS): ./include/*

.PHONY: clean

clean:
	rm -f main *.ppm *.pbm *.o
