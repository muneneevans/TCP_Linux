/***************** SERVER CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>


int main(){
	//client();
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
	  if(listen(welcomeSocket,5)==0)
		printf("Listening\n");
	  else
		printf("Error\n");


	  //accept connections
	  addr_size = sizeof serverStorage;
	  while( newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size)){
	  
	  clientcount ++ ; 
	  
	  //read message
	  recv(newSocket, buffer, 1024, 0);
	  printf("received: %s" , buffer);
	  clientports[clientcount] = atoi(buffer);
	  //printf("port is: %d", clientports[clientcount]);


		for( i = 0 ; i < 4 ; i++)
			{
				
				printf("members %d\n" ,clientports[i]);
				}
	  //send respose
	  strcpy(buffer,clientports);
	  send(newSocket,buffer,14,0);
  }
	
  return 0;
}


