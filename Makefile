.PHONY: clean

all:
	g++ -std=c++20 -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion -g Raytracer.cpp Vec3.cpp -o raytracer

clean:
	mv *.ppm renders/
