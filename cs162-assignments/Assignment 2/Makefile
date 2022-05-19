CC = g++
exe_file = library_cart

$(exe_file): book.o cart.o patron.o librarian.o library.o
	$(CC) -std=c++98 -g main.cpp -o $(exe_file) book.o cart.o patron.o librarian.o library.o

book.o: book.cpp
	$(CC) -c -g book.cpp

cart.o: cart.cpp
	$(CC) -c -g cart.cpp

patron.o: patron.cpp
	$(CC) -c -g patron.cpp

librarian.o: librarian.cpp
	$(CC) -c -g librarian.cpp

library.o: library.cpp
	$(CC) -c -g library.cpp



clean:
	rm cart.o patron.o librarian.o library.o book.o $(exe_file)

clean_o:
	rm cart.o patron.o librarian.o library.o book.o
