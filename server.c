/***************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>

int sendpeerports( int port)
{

	int n ,i ;
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;


	printf("sending ports");
	//client socket
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	//set server values
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);


		//connect to server
		addr_size = sizeof serverAddr;
		connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
for( i = 0 ; i < 5 ; i++){

		printf("plase enter the message: ");
		bzero(buffer, 256) ;
		fgets(buffer, 255, stdin);

		n = write(clientSocket , buffer , strlen(buffer));
	}

	return 0;
	}




int main(){
	//client();
	pthread_t pth ;
	int clientports[5] , i ;
	char clientports_char[5] ;
	int welcomeSocket, newSocket , clientcount;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	clientcount = 0 ;

	//create server socket and configure
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5500);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	//bind to socket
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));


	//listen
	if(listen(welcomeSocket,50)==0)
	clilen = sizeof(cli_addr);
	printf("Listening\n");
	else
	printf("Error\n");


	//accept connections
	addr_size = sizeof serverStorage;
	while( newSocket = accept(welcomeSocket, (struct sockaddr *) &cli_addr, &clilen)){

	clientcount ++ ;

	//read message
	recv(newSocket, buffer, 1024, 0);
	printf("\n new client on port: %s" , buffer);
	clientports[clientcount] = atoi(buffer);
	//printf("port is: %d", clientports[clientcount]);

	//sendpeerports(clientports[clientcount]);
	//strcpy(buffer,"client 2\n");
	//send(newSocket,buffer,10,0);

  }

  return 0;
}
