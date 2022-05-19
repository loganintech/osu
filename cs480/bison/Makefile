all: parser parser-push

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

# scanner: scanner.cpp
# 	g++ scanner.cpp -o scanner

parser: parser.cpp parser.hpp scanner.cpp
	g++ parser.cpp scanner.cpp -o parser

scanner-push.cpp: scanner-push.l
	flex -o scanner-push.cpp scanner-push.l

parser-push.cpp parser-push.hpp: parser-push.y
	bison -d -o parser-push.cpp parser-push.y

parser-push: parser-push.cpp parser-push.hpp scanner-push.cpp
	g++ parser-push.cpp scanner-push.cpp -o parser-push

clean:
	rm -f scanner scanner.cpp
