#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>
#define BUFFER_SIZE 1048
#define NAME_SIZE   20

char name[NAME_SIZE];

void *Send_Message(void *arg);
void *Receive_Message(void *arg);

int main(){

  pthread_t sendThreadID;
  pthread_t recvThreadID;

  //Create Socket
  int clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocketFD == -1){
    printf("[-]Socket error");
    exit(1);
  }
  else
  {
	printf("CLient Socket: %d \n", clientSocketFD);
  }


  //Connect to server
  struct sockaddr_in passiveServerAddress;
  memset(&passiveServerAddress, 0, sizeof(passiveServerAddress));
  passiveServerAddress.sin_family = AF_INET;
  passiveServerAddress.sin_port = htons(8888);
  passiveServerAddress.sin_addr.s_addr = inet_addr("192.168.56.6");

  if(connect(clientSocketFD, (struct sockaddr*)&passiveServerAddress, sizeof(passiveServerAddress)) != 0)
  {
	printf("Error connect()\n");
	exit(-1);
  }
  else
  {
	printf("Connected....\n");
	printf("Enter your name: ");

	fgets(name, NAME_SIZE, stdin);
	name[strlen(name)-1] = '\0';

	pthread_create(&sendThreadID, NULL, Send_Message,(void*)&clientSocketFD);
        pthread_create(&recvThreadID, NULL, Receive_Message,(void*)&clientSocketFD);
  }

  pthread_join(sendThreadID, NULL);
  pthread_join(recvThreadID, NULL);
  
  close(clientSocketFD);

  return 0;
}

void *Send_Message(void *arg)
{
        int connectedClient = *((int*)arg);
        char message[BUFFER_SIZE] = {0};
        char NameMessage[BUFFER_SIZE+NAME_SIZE+30] = {0};

        while(1)
        {
                fgets(message,BUFFER_SIZE, stdin);
                if(message[0] == 'x' || message[0] == 'X')
                {
                        close(connectedClient);
                        exit(0);
                }
                else
                {
                        printf(NameMessage, "[%s]; %s", tzname, message);
                        write(connectedClient, NameMessage, strlen(NameMessage));
                }
        }
        return NULL;
}

void *Receive_Message(void *arg)
{
        int connectedClient = *((int*)arg);
        char NameMessage[BUFFER_SIZE+NAME_SIZE+1] = {0};

        int strLen = 0;

        while(1)
        {
                strLen = read(connectedClient, NameMessage, BUFFER_SIZE+NAME_SIZE);
                if(strLen == 1)
                {
                        exit(1);
                }
                else
                {
                        NameMessage[strLen] = '\0';
                        printf("%s", NameMessage);
                }
        }
        return NULL;
}
