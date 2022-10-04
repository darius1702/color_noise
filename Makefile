CPP=g++
CPPFLAGS=-std=c++14 -Wall -Werror -Wextra

noise: noise.cpp noise.h
	${CPP} ${CPPFLAGS} noise.cpp -o noise
	@echo --------
	./noise

.PHONY: clean

clean:
	rm -f noise *.ppm *.pbm
