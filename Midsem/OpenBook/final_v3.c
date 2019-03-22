#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int state[4]={1,0,0,0}; //this helps us tell which player's turn it is now.
int p[4]={0,0,0,0}; //their positions
int randomnumber=0; //to signify the die roll
pthread_t tid[4]; //the various threads.
pthread_mutex_t lock[4], lock_main; //this is how we'll implement the 'yield' function.
int s_start[3] = {99,64,17}; //snakes head
int s_end[3] = {78,60,7}; //snakes tail
int l_start[3] = {20,28,71}; //ladder down
int l_end[3] = {38,84,91}; //ladder up

void exit_func(int i);

//this functions essentially just computes the updated location with the die
//roll and checks if the person won or not. Or if the person rolled too high
//a number (which means they don't move forward). Or if they encountered a
//snake or a ladder
int check(int p1){
	int new_p;
	int i;
	srand(time(NULL));
	randomnumber = rand() % 6 +1;
	p1 = p1+randomnumber;
	if(p1==100){ //winning condition
		return p1;
	}
	else if (p1>100){ //greater than 100 condition
		return p1-randomnumber;
		//here we don't check for snakes or ladders again, because that would've
		//already been checked in the previous turn.
	}
	for(i=0;i<3;i++){
		if (p1==s_start[i]){ //checking for snakes
			p1 = s_end[i];
		}
		else if(p1==l_start[i]){ //checking for ladder
			p1=l_end[i];
		}
	}
	return p1;
}

// it unlocks and sends a signal to the next thread to continue execution.

void send(){
	// printf("in send\n");
	if(state[0]){ //checking who's turn it is, here player 0
		// printf("Locking0.\n");
		pthread_mutex_unlock(&lock[0]);
	}
	else if(state[1]){
		// printf("Locking1.\n");
		pthread_mutex_unlock(&lock[1]);
	}
	else if(state[2]){
		// printf("Locking2.\n");
		pthread_mutex_unlock(&lock[2]);
	}
	else if(state[3]){
		// printf("Locking3.\n");
		pthread_mutex_unlock(&lock[3]);
	}
}

//it gives the go-ahead signal for the program.

void yield(){
	// printf("in yield\n");
	if(state[0]){ //checking who's turn it is, here player 0
		// printf("Un Locking0.\n");
		pthread_mutex_lock(&lock[0]);
	}
	else if(state[1]){
		// printf("Un Locking1.\n");
		pthread_mutex_lock(&lock[1]);
	}
	else if(state[2]){
		// printf("Un Locking2.\n");
		pthread_mutex_lock(&lock[2]);
	}
	else if(state[3]){
		// printf("Un Locking3.\n");
		pthread_mutex_lock(&lock[3]);
	}
}

//this is our main function. It is the thread that we create.
//how does it work? It enters and locks itself. After, it checks for the state
//variable. It then picks the appropriate position variable and updates it's
//position.

void* play(void *vargp)
{
	int *myid = (int *)vargp;
	while(1){ //runs until someone wins
		yield();
		if(state[0]){ //checking who's turn it is, here player 0
		// printf("Locking0.\n");
			unsigned long i = 0;
			state[1]=1; //reassigning states so that the next player can play
			state[0]=0;
			p[0] = check(p[0]);
			if (p[0]==100){ //checking for winning condition
				exit_func(0);
			}
		}
		else if(state[1]){
			// printf("Locking1.\n");
			unsigned long i = 0;
			state[1]=0;
			state[2]=1;
			p[1] = check(p[1]);
			if (p[1]==100){
				exit_func(1);
			}
		}
		else if(state[2]){
			// printf("Locking2.\n");
			unsigned long i = 0;
			state[3]=1;
			state[2]=0;
			p[2] = check(p[2]);
			if (p[2]==100){
				exit_func(2);
			}
		}
		else if(state[3]){
			// printf("Locking3.\n");
			unsigned long i = 0;
			state[3]=0;
			state[0]=1;
			p[3] = check(p[3]);
			if (p[3]==100){
				exit_func(3);
			}
		}
		send();
	}
}

//it's similar to the python line "handle = print_name("Dear")"
//it is what we use to setup the necessary variables, initialize the lock,
//basically

void setup(){
	if (pthread_mutex_init(&lock_main, NULL) != 0)
	{
		printf("\n mutex init has failed\n");
		exit(0);
	}
	int j;
	for (j=0;j<4;j++){
		if (pthread_mutex_init(&lock[j], NULL) != 0)
		{
			printf("\n mutex init has failed\n");
			exit(0);
		}
	}
	int i=0;
	while(i < 4)
	{
		int err = pthread_create(&(tid[i]), NULL, &play, &(tid[i]));
		if (err != 0)
			printf("Error!\n");
		i++;
	}
	pthread_mutex_lock(&lock_main);
}

//similar to the __next__() function in python. It creates the threads and
//now within the thread they wait for the other threads to finish and
//then execute themselves

void __next__(){
	pthread_mutex_lock(&lock_main);
}

//exit procedure if they were to exit not via the thread.

void exit_func(int i){
	printf("Player %d wins!\n",i);
	printf("Positions: p1=%d, p3=%d, p3=%d, p4=%d\n",p[0],p[1],p[2],p[3]);
	int j;
	for (j=0;j<4;j++)
		pthread_mutex_destroy(&lock[j]);
	pthread_mutex_unlock(&lock_main);
	exit(0);
}

void destroy(){
	pthread_mutex_unlock(&lock_main);
	pthread_mutex_destroy(&lock_main);
}


int main()
{
	setup();
	__next__();
	destroy();
	return 0;
}
