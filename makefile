client:client.o process.o
	gcc -o client client.o process.o -lpthread
client.o:client.c
	gcc -c client.c -o client.o
process.o:process.c
	gcc -c process.c -o process.o

server:server.o process.o
	gcc -o server server.o process.o -lpthread
server.o:server.c
	gcc -c server.c -o server.o

clean:
	rm -f *.o
	rm -f client server 
