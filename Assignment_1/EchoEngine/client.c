#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message, message2;

int main()
{
	// key_t key, key2;
	int msgid, msgid2;

	msgid = msgget(1100, 0666 | IPC_CREAT);
	message.mesg_type = 1;
	msgid2 = msgget(1101, 0666 | IPC_CREAT);

	while (1){
		printf("Write Data : ");
	  fgets(message.mesg_text, sizeof(message.mesg_text), stdin);

		msgsnd(msgid, &message, sizeof(message), 0);
		clock_t t;
		t = clock();

		printf("Data send is : %s \n", message.mesg_text);

		if (msgrcv(msgid2, &message2, sizeof(message2), 1, 0) > 0){
		   printf("Data Received is : %s \n",message2.mesg_text);
	   }
		 t = clock() - t;
		 double time_taken = ((double)t)/CLOCKS_PER_SEC;
		 printf (" Time taken is : %f seconds\n", time_taken);
	 }

	// return 0;
}
