#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
	int id;
} message, message2;

int main()
{
	// long long int start, end;
	int msgid, msgid2;
	char mes_text_help[100];

	msgid = msgget(1000, 0666 | IPC_CREAT); //to send request and filename.
	message.mesg_type = 1;
	message.id = msgid;
	msgid2 = msgget(1002, 0666 | IPC_CREAT); //to send and receive messages
	message.id = msgid2; //this is what the server will use to send the file contents back.

	while (1){
		clock_t t;
		printf("Filename : ");
	  fgets(mes_text_help, sizeof(mes_text_help), stdin);
		message.mesg_text[0] = 'G';
		message.mesg_text[1] = 'E';
		message.mesg_text[2] = 'T';
		message.mesg_text[3] = ' ';
		int i;
		for(i=0;i<(strlen(mes_text_help)-1);i++){
			message.mesg_text[i+4] = mes_text_help[i];
		}

		msgsnd(msgid, &message, sizeof(message), 0);
		t = clock();
		printf("Data sent is : %s \n", message.mesg_text);

		if (msgrcv(msgid2, &message2, sizeof(message2), 1, 0) > 0){
		   printf("Data Received is : %s \n",message2.mesg_text);
	   }
		 t = clock() - t;
	   double time_taken = ((double)t)/CLOCKS_PER_SEC;

		 printf (" Time taken is : %f seconds\n", time_taken);

		 //clearing the character buffers
		 memset(message.mesg_text, 0, sizeof(message.mesg_text));
		 memset(message2.mesg_text, 0, sizeof(message2.mesg_text));
 }

}
