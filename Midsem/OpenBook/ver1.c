#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// Let us create a global variable to change it in threads
int id = 0;
int p[4];
int randomnumber=0;
pthread_t tid[4];
int counter;
pthread_mutex_t lock;
int prev=4;

// The function to be executed by all threads

void* trythis(void *vargp)
{
	int *myid = (int *)vargp;
	printf("Thread ID: %d, ID: %d, randomnumber: %d\n", *myid, id, randomnumber);
	
	if(id==prev+1 || (id==0 && prev==4)){
		printf("Locking.\n");
		pthread_mutex_lock(&lock);
		// printf("Current pos: %d, %d, %d, %d\n",*p1, *p2, *p3, *p4);



		unsigned long i = 0;
		// counter += 1;
		// printf("\n Job %d has started\n", counter);
		//
		// for(i=0; i<(0xFFF);i++);
		//
		// printf("\n Job %d has finished\n", counter);
		p[id] = p[id]+randomnumber;
		prev=id;
		if (id!=4)
			id = id+1;
		else
			id = 0;
		// id = id%4;
		// id = id+1;
		randomnumber = rand() % 6;
		randomnumber = randomnumber+1;

		pthread_mutex_unlock(&lock);
	}

	return NULL;
}


// pthread_mutex_t lock;

int main()
{
	int i = 0;
	int error;

	p[0]=0;
	p[1]=0;
	p[2]=0;
	p[3]=0;
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n mutex init has failed\n");
		return 1;
	}
	srand(time(NULL));
	randomnumber = rand() % 6;
	randomnumber = randomnumber+1;

	while(i < 4)
	{
		int err = pthread_create(&(tid[i]), NULL, &trythis, &(tid[i]));
		if (err != 0)
			printf("Error!\n");
			// printf("\nThread can't be created :[%s]", strerror(error));
		i++;
	}

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);
	printf("Positions: p1=%d, p3=%d, p3=%d, p4=%d\n",p[0],p[1],p[2],p[3]);
	pthread_mutex_destroy(&lock);

	return 0;
}
