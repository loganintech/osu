CC = g++
flags = -g
part_flags = $(flags) -c

main: event.o pokemon.o pokemon_encounter.o trainer.o flying.o psychic.o rock.o cave.o location.o pokestop.o world.o
	$(CC) $(flags) main.cpp pokemon.o pokemon_encounter.o trainer.o flying.o psychic.o rock.o cave.o location.o pokestop.o world.o -o game

event.o: event.h

pokemon.o: pokemon.cpp
	$(CC) $(part_flags) pokemon.cpp

flying.o: flying.cpp
	$(CC) $(part_flags) flying.cpp

rock.o: rock.cpp
	$(CC) $(part_flags) rock.cpp

psychic.o: psychic.cpp
	$(CC) $(part_flags) psychic.cpp

location.o: location.cpp
	$(CC) $(part_flags) location.cpp

pokemon_encounter.o: pokemon_encounter.cpp
	$(CC) $(part_flags) pokemon_encounter.cpp

cave.o: cave.cpp
	$(CC) $(part_flags) cave.cpp

pokestop.o: pokestop.cpp
	$(CC) $(part_flags) pokestop.cpp

trainer.o: trainer.cpp
	$(CC) $(part_flags) trainer.cpp

world.o: world.cpp
	$(CC) $(part_flags) world.cpp

clean:
	rm *.o *.stackdump