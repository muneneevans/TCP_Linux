
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>



void *StartListening(void *port)
{
	int clients[10], myport;
	int welcomeSocket, newSocket , clientcount ;
	char buffer[1024] , peerport[4];
	struct sockaddr_in serverAddr , cli_addr;
	struct sockaddr_storage serverStorage;
	socklen_t clilen;
	socklen_t addr_size;
	
	
	myport = (int) port ;
	//create server socket and configure
	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
	memset(serverAddr.sin_zero, '0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(myport);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	//bind to socket
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	//listen
	if(listen(welcomeSocket,5)==0)
	printf("peer is listening \n");
	else
	printf("Error\n");

	//accept connections
	addr_size = sizeof serverStorage;
	cli_addr.sin_family = AF_INET ;
	clilen = sizeof(cli_addr);
	while(1){
	newSocket = accept(welcomeSocket, (struct sockaddr *) &cli_addr, &clilen);
		//diplay the client port
		printf("\n peer on port: %d" , cli_addr.sin_port 	);
					
		//reply with client port
		sprintf(peerport , "%d" , cli_addr.sin_port  );
		strcpy(buffer, "acl");
		send(newSocket,buffer,strlen(buffer),0);
		
		//read message
		while(recv(newSocket, buffer, 1024, 0)){
		printf("%s" , buffer);}

  }

	return NULL ; 
	}


void SendMessage(void *port )
{
	int n  , senderport ;   
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	senderport = (int) port ; 
	//client socket
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	//set server values
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(senderport);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	//connect to server
	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	
	//get a  message and send to the server
	printf("plase enter the message: ");
	bzero(buffer, 256) ; 
	fgets(buffer, 255, stdin);

	//n = write(clientSocket , buffer , strlen(buffer));
	
	//read response
	recv(clientSocket, buffer, 1024, 0);
	printf("response: %s",buffer);   
	return NULL ; 
	}

int ConnectToServer(){
	int n , myport , peers[10]	,peercount ;   
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	char* token;
	char* string;
	char* tofree;


		peercount = 0 ;
	//client socket
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	//set server values
	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(5504);	
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	//connect to server
	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
	
	//read response
	recv(clientSocket, buffer, 1024, 0);		 
	printf("peers: %s\n"  , buffer);
	
	//split the input
	token = strtok(buffer, ",");
	while(token != NULL)
	{
		printf("token %s" , token);
		token = strtok(NULL, ",");
		}
	
	//myport = (int) atoi(buffer);
	//get a  message and send to the server
	printf("plase enter the message: ");
	bzero(buffer, 256) ; 
	fgets(buffer, 255, stdin);

	//n = write(clientSocket , buffer , strlen(buffer));

	return 10;
}




int main()
{
	pthread_t pth , pth2; 
	int myport ; 
	myport = ConnectToServer();
	printf("my port %d" , myport);
	
	pthread_create(&pth , NULL , StartListening , (void*)myport);
	
	//pthread_create(&pth2 , NULL , SendMessage , 5500);
	//SendMessage(5504);
	
	
	
	
	
	}


