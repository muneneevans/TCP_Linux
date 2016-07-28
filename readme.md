
**TCPIP SERVER CLIENT AND P2P APPLICATION** 
**********************************************

This is a client server application that allows for clients to connect to a server then connect to their peers


**SETTING UP**
**********************************************

Clone the repository and you are done. Make sure you have gcc running



**CODE FILES**
**********************************************
There are two files of interest:
    s.c -> The server coe
    c.c -> The client/peer code 




**ALGORITHM**
**********************************************
Run the s.c first before running the clients

A client first connects to the server and is given information about the port it is listening on and other peers who are online

The client then starts listening for packets on the port it has been given by the server

The client then selects one of the other peers at random and sends a series of 5 messages saying "hello"

It then continues to listen on that port

When a client receives a message, it displays the port of the sender and responds with an acknowledgment message 