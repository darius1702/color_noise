CPP = g++
CXXFLAGS = -std=c++14 -Wall -Werror -Wextra

OBJECTS = main.o noise.o

main: $(OBJECTS)
	$(CPP) $(CXXFLAGS) -o $@ $^

$(OBJECTS): noise.h

.PHONY: clean

clean:
	rm -f main *.ppm *.pbm *.o
