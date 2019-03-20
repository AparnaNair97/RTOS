The idea for me to implement the co routine is as follows.
We will create threads. And the threads are to communicate with each other. We will use a global variable to store the context. So when we access it that becomes the critical section. And then we use that to synchronize the threads. Here, what I mean when i say context is merely the next player who has to play. 

I am facing difficulty in synchornizing the threads. They fail to happen one after the other as is required. Perhaps a bit of tweaking is required, and I am working on it.

The first version of the code is uploaded for now. It is by no means complete and requires much more effort on my part.
