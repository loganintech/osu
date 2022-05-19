all: scan output

scan: scanner parser
	g++ src/scanner.cpp src/parser.cpp -o scan

scanner:
	flex -o src/scanner.cpp src/scanner.l

parser:
	bison --debug -d -o src/parser.cpp src/parser.y

clean:
	rm -f scan src/scanner.cpp src/parser.cpp src/parser.hpp
	rm -r out

test1:
	./scan < testing_code/p1.py

test2:
	./scan < testing_code/p2.py

test3:
	./scan < testing_code/p3.py

error1:
	./scan < testing_code/error1.py

error2:
	./scan < testing_code/error2.py

error3:
	./scan < testing_code/error3.py

testerrors: error1 error2 error3

output:
	mkdir out
	./scan < testing_code/p1.py > out/py1.cpp
	./scan < testing_code/p2.py > out/py2.cpp
	./scan < testing_code/p3.py > out/py3.cpp

testout:
	g++ out/py1.cpp -o out/p1
	g++ out/py2.cpp -o out/p2
	g++ out/py3.cpp -o out/p3
	./out/p1
	./out/p2
	./out/p3
