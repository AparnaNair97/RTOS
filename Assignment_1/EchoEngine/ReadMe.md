## How To Run:
The client code after being compiled can just be run from multiple terminals to simulate multiple clients.
The server code has to be run simultaneously at another terminal.

## Timing Analysis:
Timing analysis tells us that all of the processes are in fact close to promptly dealt with (in about 0.000053 seconds). We were unable to simulate simultaneous clients. Even though we ran the clients at multiple terminals at the same time, it was still not truly at the same time. So in essesnce it's pretty much like each process occurs one after the other.
We are in the process of using fork() to try and simulate simulatneous processes.
