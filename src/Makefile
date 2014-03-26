HEADERS = lib/util.h lib/map.h lib/ship.h
OBJECTS = lib/map.o lib/ship.o lib/util.o server.o

default: main clean

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

main: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)