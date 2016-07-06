
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

int myport = 2400;
int callserver(){
	int n  ; 
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	//client socket
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	//set server values
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(5500);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	//connect to server
	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	//get a  message and send to the server
	printf("plase enter the message: ");
	bzero(buffer, 256) ; 
	fgets(buffer, 255, stdin);

	n = write(clientSocket , buffer , strlen(buffer));


	//read response
	//recv(clientSocket, buffer, 1024, 0);
	//printf("Data received: %s",buffer);   


	return 0;
}

void *callpeer()
{
	
	return NULL ;
	}


int main(){	
	int peers[5] ; 
	int welcomeSocket, newSocket, peerscount;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	
	callserver();

	//create socket
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	//configure server
	serverAddr.sin_family = AF_INET;  
	serverAddr.sin_port = htons(myport); 
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	//bind to socket
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	if(listen(welcomeSocket,50)==0)
	printf("Listening\n");
	else
	printf("Error\n");

	//accept connections
	addr_size = sizeof serverStorage;
	while(newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size))
	{
		//read message
		recv(newSocket, buffer, 1024, 0);
		printf("\nclient has received: %s" , buffer);

		//send response
		//strcpy(buffer,"client 1\n");
		//send(newSocket,buffer,10,0);


		//read response
		recv(newSocket, buffer, 1024, 0);
		printf("Data received: %s",buffer);   
	}

	return 0;
}

