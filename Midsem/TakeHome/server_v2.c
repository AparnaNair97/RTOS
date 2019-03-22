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

#define PORT 8081
int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
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
		valread = read( new_socket , buffer, 1024); //the first message - "GET "
		char mesg_text_help[]={0};
		char read_file[5][1024] = {0,0,0,0,0};
		int i;
		printf("strlen(buffer) = %ld\n", strlen(buffer));
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
				printf("x : %s \n",x);
				strcat(read_file[k],x);
				printf("read_file[k] : %s \n",read_file[k]); //readingthe values and putting into a buffer so that we can send it to the client later.
				close(fd);
			}
		}
		//making the buffer to send. we need it to be comma seperated values hence the commas.
		sprintf(buffer2,"%s, %s, %s, %s, %s",read_file[0],read_file[1],read_file[2],read_file[3],read_file[4]);

		printf("Data Sent is : %s \n",buffer2);
		send(new_socket , buffer2 , strlen(buffer2) , 0 );
		memset(buffer2, 0, sizeof(buffer2)); //clearing the buffer values
		memset(buffer, 0, sizeof(buffer)); //clearing the buffer values
	}

	perror("accept");
	exit(EXIT_FAILURE);
	return 0;
}
