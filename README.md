# Server WINSOCK Example of server in C. 
The server open socket, using _WINSOCK_, and with *while(TRUE)* is
always in listening mode to socket, in order to wait a connection from
client. The server sends a _GREETING_ to client. The server receive a
_GREETING_ by client and saves the message in *connection.txt* file. If
file doesn't exists, server creates its.

## LINKS
[Socket example and other information](https://stackoverflow.com/questions/14404202/receiving-strange-characters-symbols-in-winsock)

[Code Block with GCC G++ compiler and GDB debugger Official](http://www.codeblocks.org/downloads/26)

[Code Block with GCC G++ compiler and GDB debugger Direct Download](https://sourceforge.net/projects/codeblocks/files/Binaries/17.12/Windows/codeblocks-17.12mingw-setup.exe/download)

[Download MinGW-w64](https://sourceforge.net/projects/mingw-w64/)

## INSTALLATION
1. Install CLion
* Create new student account
https://www.jetbrains.com/student/ or https://www.jetbrains.com/shop/eform/students

* Insert your university email

* Download the IDE

* Download the code as ZIP

* Extract zip in a folder

* Import project as "New CMake Project from Source". Chose and select the project, navigating inside your file system. Fianlly import as "Open Existing Project".

* Download and install MinGW-w64

* Set Toolchains. File -> Settings -> Build, Execution, Deployment -> Toolchais. Click on '+'. Automatically, CLion sets up toolchains

![figure](img/clionToolChain.jpg "CLion toolchains")

2. Install CodeBlocks

* Use Code Block with GCC/G++ compiler and GDB debugger (Direct Download) link

* Install application 

* Set up linker: Settings -> Compiler -> Linker settings -> Add

* Add C:\windows\system32\wsock32.dll libraries

![figure](img/codeBlocCompiler.jpg "Add library linker in Code Block")

* You can click on "Build and Run" button to launch server

![figure](img/buildAndRunButton.jpg "Build and run button")

* You can run application from file system

![figure](img/serverApplication.jpg "Double click to run server application")

## TEST
1. NMAP TOOL
Download nmap for Windows platform, clicking on _Latest stable release self-installer_, from the follow [link](https://nmap.org/download)
Open new terminal session and launch the follow command
```
ncat 127.0.0.1 8010
```
Write your messages from server and press ENTER to send to server.

2. USE CLIENT PROGRAM
Download, compile, build and run the _WINSOCK CLIENT_ program, written in C, which is available in *WINCLIENTSOCKET* repository, [link](https://github.com/marksniper/WinSockClient)
## Authors
* **Benedetto Marco Serinelli** - *Initial work* 
## Acknowledgments
The code was developed with _CLion_ and another test was done with _Code
Blocks_.
