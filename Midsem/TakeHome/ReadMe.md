# Implementation of the server:
The server was to read the 5 different files and send it to the client.
What my server does is to read it and also create a 'csv' version of the readings.

# Implementation of the client:
Since our server is not really reliable in terms of times. The client runs and requests a reading from the server every 2 seconds (sampling rate for the sensors is 2 seconds for us).
Once we receive the readings we append the time data also and then write it into a 'readings.csv' file.

## NOTE: 
The plots have also been attached. But it may vary for different individuals, depending on their sensor readings. The sensor readings were simulated using 'simulator.py'. 
