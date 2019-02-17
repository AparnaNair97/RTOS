// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message1, message2;

int main()
{
	// key_t key, key2;
	int msgid, msgid2;

	msgid = msgget(1100, 0666 | IPC_CREAT);
	msgid2 = msgget(1101, 0666 | IPC_CREAT);
	message2.mesg_type = 1;

	while(msgrcv(msgid, &message1, sizeof(message1), 1, 0)>0){

	if(*(message1.mesg_text) >= 65 && *(message1.mesg_text) <= 90){
		printf("Upper Case\n");
		*(message2.mesg_text) = *(message1.mesg_text) + 32;
	}
	else if(*(message1.mesg_text) >= 97 && *(message1.mesg_text) <= 122){
		printf("Lower Case\n");
		*(message2.mesg_text) = *(message1.mesg_text) - 32;
	}
	else{
		*(message2.mesg_text) = *(message1.mesg_text);
	}

	printf("Data Received is : %s \n",message1.mesg_text);
	printf("Data Sent is : %s \n",message2.mesg_text);

	msgsnd(msgid2, &message2, sizeof(message2), 0);

}

	return 0;
}
