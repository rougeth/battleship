HEADERS = lib/util.h lib/map.h lib/ship.h
OBJECTS = lib/ship.o lib/map.o lib/util.o server.o

default: program

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

program: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f program