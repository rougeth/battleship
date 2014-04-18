HEADERS = lib/map.h lib/ship.h lib/socket.h lib/util.h lib/config.h
SERVER_OBJECTS = lib/map.o lib/ship.o lib/socket.o lib/util.o lib/config.o server.o
CLIENT_OBJECTS = lib/map.o lib/ship.o lib/socket.o lib/util.o lib/config.o client.o

default: main clean

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

main: $(SERVER_OBJECTS) $(CLIENT_OBJECTS)
	gcc $(SERVER_OBJECTS) -o server
	gcc $(CLIENT_OBJECTS) -o client

clean:
	rm -f $(SERVER_OBJECTS) $(CLIENT_OBJECTS)
