# Server WINSOCK Example of server in C. 
The server open socket, using _WINSOCK_, and with *while(TRUE)* is
always in listening mode to socket, in order to wait a connection from
client. The server sends a _GREETING_ to client. The server receive a
_GREETING_ by client and saves the message in *connection.txt* file. If
file doesn't exists, server creates its.

## LINKS
[Socket example and other information](https://stackoverflow.com/questions/14404202/receiving-strange-characters-symbols-in-winsock)

## TEST
1. NMAP TOOL
Download nmap for Windows platform, clicking on _Latest stable release self-installer_, from the follow [link](https://nmap.org/download)
Open new terminal session and launch the follow command
```
ncat 127.0.0.1 8010
```
Write your messages from server and press ENTER to send to server.

2. USE CLIENT PROGRAM
Download, compile, build and run the _WINSOCK CLIENT_ program, written in C, which is available in *WINCLIENTSOCKET* repository, [link]()
## Authors
* **Benedetto Marco Serinelli** - *Initial work* 
## Acknowledgments
The code was developed with _CLion_ and another test was done with _Code
Blocks_.
