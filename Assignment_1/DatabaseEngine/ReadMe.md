## How to Run:
Each of the client codes only differs in line 23. Each of the clients has a different queue, to prevent mixing up of data.
You need to run them at seperate terminals, and the server should always keep running.

## Timing Analysis:
Similar observations as the Echo Engine were made. The timings were close to the same majorly because we were not able to simulate simultaneous processes. Once we figure out how to use fork() in the Echo Engine, we'll extend the same here as well.
