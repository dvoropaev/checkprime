all: server client

server: server.o checkprime.o
	gcc server.o checkprime.o -lpthread -lm -o server

client: client.o
	gcc client.o -o client

server.o: server.c
	gcc -c server.c

checkprime.o: checkprime.c
	gcc -c checkprime.c

client.o: client.c
	gcc -c client.c

clean:
	rm -rf *.o server client

#gcc ./checkprime.c -lpthread -lm -o checkprime
