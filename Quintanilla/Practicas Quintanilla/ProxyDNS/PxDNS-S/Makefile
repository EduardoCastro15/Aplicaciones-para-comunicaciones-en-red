run: bin
	./bin

bin: main.o read_Dom.o socket_local.o socket_remote.o wait_cliente.o wait_replay.o
	gcc main.o read_Dom.o socket_local.o socket_remote.o wait_cliente.o wait_replay.o -o bin

main.o: main.c
	gcc -c main.c

read_Dom.o: Analisis/read_Dom.c
	gcc -c Analisis/read_Dom.c

socket_local.o: Sockets/socket_local.c
	gcc -c Sockets/socket_local.c

socket_remote.o: Sockets/socket_remote.c
	gcc -c Sockets/socket_remote.c

wait_cliente.o: Waits/wait_cliente.c
	gcc -c Waits/wait_cliente.c

wait_replay.o: Waits/wait_replay.c
	gcc -c Waits/wait_replay.c

clean:
	rm *.o
