// Client side C/C++ program to demonstrate Socket programming
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

#define PORT 8080

int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	// char *hello = "H";
	char buffer[1024] = {0};
	char mes_text_help[100];
	char buffer2[1024] = {0};
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

	printf("Write Data : ");
	fgets(mes_text_help, sizeof(mes_text_help), stdin);

	buffer[0] = 'G';
	buffer[1] = 'E';
	buffer[2] = 'T';
	buffer[3] = ' ';
	int i;
	for(i=0;i<(strlen(mes_text_help)-1);i++){
		buffer[i+4] = mes_text_help[i];
	}

	clock_t t;
	send(sock , buffer , strlen(buffer) , 0 );
	t = clock();
	// printf("Hello message sent\n");
	valread = read( sock , buffer2, 1024);
	t = clock()-t;
	printf("%s\n",buffer2 );

	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf (" Time taken is : %f seconds\n", time_taken);
	return 0;
}
