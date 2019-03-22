# Background:
Coroutines are computer program components that generalize subroutines for non-preemptive multitasking, by allowing execution to be suspended and resumed. (https://en.wikipedia.org/wiki/Coroutine)

# Implementation of Coroutines:
To implement a co coroutine in C we used threads. We used the locking mechanisms of threads to simulate the yield and send functions.
Each thread executes and then pauses at yield. At yield, the lock corresponding to the thread under consideration is locked.
After send() is called. send() basically unlocks that particular lock and transfers control to the next thread.

# Implementation of the Game:
Each player gets his own thread (or coroutine). And then they synchronize so that the round robin fashion in which the game is played is maintained. I use state variables which tell me which player's turn it is now. 


