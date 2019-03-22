#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 8081

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int cnt = 0;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
	char mes_text_help[100] = {0};
	int fd;
	fd = open("readings.csv",O_WRONLY | O_CREAT);
	printf("file open error fd=%d\n",fd);
	char heading[2000] = {"Time, Temp, Hum, G1, G2, G3\n"}; //heading
	write(fd, &heading, strlen(heading));
	while(1){
		char buffer2[1024] = {0};
		printf("file open error fd=%d\n",fd);
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			printf("\n Socket creation error \n");
			return -1;
		}

		memset(&serv_addr, '0', sizeof(serv_addr));

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);

		// Convert IPv4 and IPv6 addresses from text to binary form
		if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
		{
			printf("\nInvalid address/ Address not supported \n");
			return -1;
		}

		if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		{
			printf("\nConnection Failed \n");
			return -1;
		}

		//not really important, but this is what helps establish the connection with the server.
		buffer[0] = 'G';
		buffer[1] = 'E';
		buffer[2] = 'T';
		buffer[3] = ' ';
		int i;
		send(sock , buffer , strlen(buffer) , 0 ); //hello message to the server
		int k;
		char x[20]={0};
		valread = read( sock , x, 1024); //reading the data from the server
		printf("%s\n",x );
		printf("Received\n");
		printf("%s\n",x );
		sprintf(buffer2,"%d, %s\n",cnt,x); //to put it in the correct format
		printf("%s\n",buffer2 );
		write(fd, &buffer2, strlen(buffer2)); //writing to the csv file
		memset(buffer2, 0, sizeof(buffer2));

		printf("for loop done\n");
		sleep(2);
		cnt=cnt+2; //for the time stamp
	}
	return 0;
}
