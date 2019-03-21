The idea for me to implement the co routine is as follows.
We will create threads. And the threads are to communicate with each other. We will lock the state variable which tells us whether or not the necessary information needed for the routine has come or not. (In our case we keep a track of the players.)
So the code has 4 state variables which tell us if a particular player's turn has come or not and then the corresponding thread starts execution. 
Thr threads are looped indefinitely and will end only when we get at least one winner. After which the program tells us the winner and exits the program. 
