HEADERS = lib/map.h lib/ship.h lib/socket.h lib/util.h
SERVER_OBJECTS = lib/map.o lib/ship.o lib/socket.o lib/util.o server.o

default: main clean

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

main: $(SERVER_OBJECTS) $(CLIENT_OBJECTS)
	gcc $(SERVER_OBJECTS) -o server

clean:
	-rm -f $(OBJECTS)
