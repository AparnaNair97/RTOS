#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
	int id;
} message1, message2;

int main()
{
	int msgid, msgid2;
	char mesg_text_help[100];

	msgid = msgget(1000, 0666 | IPC_CREAT);
	message2.mesg_type = 1;
	message2.id = msgid;

	printf("msgid %d\n", msgid);
	//indefinite loop for the server
	while(msgrcv(msgid, &message1, sizeof(message1), 1, 0)>0){
		printf("received message from: %d\n",message1.id);
		int i;
		printf("strlen(message1.mesg_text) = %ld\n", strlen(message1.mesg_text));
		for (i=0;i<(strlen(message1.mesg_text)-4);i++){
				mesg_text_help[i] = message1.mesg_text[i+4];
				printf("i, %d\n", i);
		}
		mesg_text_help[i] = '\0';
		int fd;
		printf("Filename : %s \n",mesg_text_help);
		fd = open(mesg_text_help,O_RDONLY);
		if (fd == -1){
			printf("fd = -1\n");
			strcat(message2.mesg_text,"Data not found.");
		}
		else{
			char x[200];
			read(fd, &x, 200);
			strcpy(message2.mesg_text, x);
			close(fd);
		}
		printf("Data Received is : %s \n",message1.mesg_text);
		printf("Data Sent is : %s \n",message2.mesg_text);

		msgsnd(message1.id, &message2, sizeof(message2), 0);

		//clearing the character buffers.
		 memset(message1.mesg_text, 0, sizeof(message1.mesg_text));
		 memset(message2.mesg_text, 0, sizeof(message2.mesg_text));
		 memset(mesg_text_help, 0, sizeof(mesg_text_help));
	}

	return 0;
}
