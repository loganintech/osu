CC = g++
flags = -g
link_flags = $(flags) -c
exe_file = game

$(exe_file): creature.o demon.o cyberdemon.o human.o elf.o balrog.o paladin.o
	$(CC) $(flags) main.cpp -o $(exe_file) creature.o demon.o cyberdemon.o human.o elf.o balrog.o paladin.o

creature.o: creature.cpp
	$(CC) $(link_flags) creature.cpp

demon.o: demon.cpp
	$(CC) $(link_flags) demon.cpp

cyberdemon.o: cyberdemon.cpp
	$(CC) $(link_flags) cyberdemon.cpp

human.o: human.cpp
	$(CC) $(link_flags) human.cpp

elf.o: elf.cpp
	$(CC) $(link_flags) elf.cpp

balrog.o: balrog.cpp
	$(CC) $(link_flags) balrog.cpp

paladin.o: paladin.cpp
	$(CC) $(link_flags) paladin.cpp


clean:
	rm balrog.o elf.o human.o cyberdemon.o demon.o creature.o paladin.o $(exe_file)

cleandev:
	rm balrog.o elf.o human.o cyberdemon.o demon.o creature.o paladin.o