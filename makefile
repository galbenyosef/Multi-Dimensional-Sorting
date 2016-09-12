simCombinatorics: main.o MultiDimensionalSorting.o
	g++ main.o MultiDimensionalSorting.o -o simCombinatorics
main.o: main.cpp MultiDimensionalSorting.h myElement.h
	g++ -Wall -pedantic-errors -ansi -c main.cpp
MultiDimensionalSorting.o: MultiDimensionalSorting.cpp \
 MultiDimensionalSorting.h myElement.h
	g++ -Wall -pedantic-errors -ansi -c MultiDimensionalSorting.cpp
