// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 8080
int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char mesg_text_help[100];
	char buffer2[1024] = {0};

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	int fd;
	while ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))>0) {
		valread = read( new_socket , buffer, 1024);
		// printf("%s\n",buffer );

		// printf("received message from: %d\n",message1.id);
		int i;
		printf("strlen(buffer) = %ld\n", strlen(buffer));
		for (i=0;i<(strlen(buffer)-4);i++){
				mesg_text_help[i] = buffer[i+4];
				printf("i, %d\n", i);
		}

		// printf("Filename Received : %s \n",mesg_text_help);
		char ch_arr[5][12] = {
                             "sensor1.txt",
                             "sensor2.txt",
                             "sensor3.txt",
														 "sensor4.txt",
														 "sensor5.txt"
                         };

		int k;
		for(k=0;k<5;k++){
			printf("Buffer at the begin : %s ...\n",buffer2);
			fd = open(ch_arr[k],O_RDONLY);
			printf("File being opened: %s\n", ch_arr[k]);
			if (fd == -1){
				printf("fd = -1\n");
				strcat(buffer2,"Data not found.");
			}
			else{
				char x[20]={0};
				read(fd, &x, 20);
				strcpy(buffer2, x);
				close(fd);
			}

			printf("Data Sent is : %s \n",buffer2);

			send(new_socket , buffer2 , strlen(buffer2) , 0 );
			memset(buffer2, 0, sizeof(buffer2));
			memset(mesg_text_help, 0, sizeof(mesg_text_help));
		}
		memset(buffer, 0, sizeof(buffer));
	}

	perror("accept");
	exit(EXIT_FAILURE);
	return 0;
}
