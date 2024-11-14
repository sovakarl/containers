
CC = c++ -std=c++17
TESTFLAGS = -pthread -lgmock -lgmock_main -lgtest_main -lgtest -I/Users/$(USER)/.brew/include -L/Users/$(USER)/.brew/lib
GCCFLAGS = -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage

all: test

test: clean
	$(CC) $(GCCFLAGS) $(TESTFLAGS) -g tests/*.cpp -o containers_test
	./containers_test

clang:
 
	clang-format -i include/*.h templates/*.tpp tests/*.cpp tests/*.h s21_containersplus.hpp

clean:
	rm -rf containers_test

main:clean
	$(CC) $(GCCFLAGS) -Wno-error -g main.cpp template/*.cpp -o test