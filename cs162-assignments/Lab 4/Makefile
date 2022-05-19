CC = g++
exe_file = library_cart

$(exe_file): cart.o  library.o #patron.o librarian.o
	$(CC) -g main.cpp -o $(exe_file)

cart.o: cart.cpp
	$(CC) -c cart.cpp

# patron.o: patron.cpp
# 	$(CC) -c patron.cpp

# librarian.o: librarian.cpp
# 	$(CC) -c librarian.cpp

library.o: library.cpp
	$(CC) -c library.cpp

clean:
	rm cart.o patron.o librarian.o library.o $(exe_file)

