run: bin
	./bin

bin: main.o header.o registro_recursos.o wait_replay.o struct_request.o socket_local.o socket_remote.o
	gcc main.o header.o registro_recursos.o wait_replay.o struct_request.o socket_local.o socket_remote.o -o bin

main.o: main.c
	gcc -c main.c

header.o: Respuesta/Analyzer/header.c
	gcc -c Respuesta/Analyzer/header.c

registro_recursos.o: Respuesta/Analyzer/registro_recursos.c
	gcc -c Respuesta/Analyzer/registro_recursos.c

wait_replay.o: Respuesta/Reciv/wait_replay.c
	gcc -c Respuesta/Reciv/wait_replay.c

struct_request.o: Solicitud/Estructs/struct_request.c
	gcc -c Solicitud/Estructs/struct_request.c

socket_local.o: Solicitud/Sockets/socket_local.c
	gcc -c Solicitud/Sockets/socket_local.c

socket_remote.o: Solicitud/Sockets/socket_remote.c
	gcc -c Solicitud/Sockets/socket_remote.c

clean:
	rm *.o
