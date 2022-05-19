# all: scan output

scan: scanner parser
	g++ -g src/scanner.cpp src/tree.cpp src/parser.cpp src/main.cpp -o scan

scanner:
	flex -o src/scanner.cpp src/scanner.l

parser:
	bison --debug -d -o src/parser.cpp src/parser.y

clean:
	-rm -f scan src/scanner.cpp src/parser.cpp src/parser.hpp
	-rm *.png
	-rm -r out

test1:
	./scan.exe < testing_code/p1.py

test2:
	./scan.exe < testing_code/p2.py

test3:
	./scan.exe < testing_code/p3.py

error1:
	./scan.exe < testing_code/error1.py

error2:
	./scan.exe < testing_code/error2.py

error3:
	./scan.exe < testing_code/error3.py

testerrors: error1 error2 error3

output: scan
	-mkdir out
	./scan.exe < testing_code/p1.py > out/p1_source.gv
	./scan.exe < testing_code/p2.py > out/p2_source.gv
	./scan.exe < testing_code/p3.py > out/p3_source.gv
	dot -Tpng -o out/t1.png out/p1_source.gv
	dot -Tpng -o out/t2.png out/p2_source.gv
	dot -Tpng -o out/t3.png out/p3_source.gv
