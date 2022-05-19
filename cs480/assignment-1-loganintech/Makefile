SCAN = flex -o src/scanner.cpp src/python.l

all: scanner exe pall

scanner:
	$(SCAN)

exe: scanner
	g++ src/main.cpp src/scanner.cpp

clean:
	rm src/scanner.cpp
	rm *.out

p1:
	./a.out < testing_code/p1.py > p1text.out
p2:
	./a.out < testing_code/p2.py > p2text.out
p3:
	./a.out < testing_code/p3.py > p3text.out
p4:
	./a.out < testing_code/p4.py > p4text.out

diff1:
	git diff --no-index ./example_output/p1.out ./p1text.out

diff2:
	git diff --no-index ./example_output/p2.out ./p2text.out

diff3:
	git diff --no-index ./example_output/p3.out ./p3text.out

diff4:
	git diff --no-index ./example_output/p4.out ./p4text.out

pall: p1 p2 p3 p4

diffall: diff1 diff2 diff3 diff4

diff:
	make diffall | bat --language diff

cdiff1:
	code --diff ./example_output/p1.out ./p1text.out

cdiff2:
	code --diff ./example_output/p2.out ./p2text.out

cdiff3:
	code --diff ./example_output/p3.out ./p3text.out

cdiff4:
	code --diff ./example_output/p4.out ./p4text.out

cdiffall: cdiff1 cdiff2 cdiff3 cdiff4
