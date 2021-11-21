#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

  int port = 8888;
  int sock;
  struct sockaddr_in addr;
  char buffer[1024];

  //Create Socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0){
    perror("[-]Socket error");
    exit(1);
  }
  printf("[+]TCP server socket created.\n");


  addr.sin_family = AF_INET;
  addr.sin_port = port;
  addr.sin_addr.s_addr = inet_addr("192.168.56.6");

  //Connect to Server
  if(connect(sock, (struct sockaddr*)&addr, sizeof(addr))<0)
  {
  	printf("[-]Connect Error");
  }
  else
  {
  	printf("[+]Connected to the server.\n");
  }

  //Send Message to Server
  bzero(buffer, 1024);
  printf("Client: ");
  scanf("%s", buffer);
  if(send(sock, buffer, strlen(buffer), 0)<0)
  {
	printf("[-]Send Failed");
	return 1;
  }
  else
  {
	printf("[+]Message Sent.\n");
  }

  //Receive Message from Server
  bzero(buffer, 1024);
  if(recv(sock, buffer, sizeof(buffer), 0)<0)
  {
	printf("[-]Receive Failed");
  }
  else
  {
  	printf("Server: %s\n", buffer);
  }
  
  //Close Socket
  close(sock);
  printf("[+]Disconnected from the server.\n");

  return 0;

}
