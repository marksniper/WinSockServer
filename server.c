/*
 *This work is licensed under a Creative Commons Attribution 4.0 International License.
 *Author: Benedetto Marco Serinelli
 */
#include<stdio.h>
#include<winsock2.h>
#include <time.h>

#define MAXRECV 1024
#define MAX_CLIENT_SOCK 30
#define PORT 8010

void saveInFile(char *buffer);

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET master, new_socket, client_socket[MAX_CLIENT_SOCK], s;
    struct sockaddr_in server, address;
    int activity, addrlen, i, valread;
    char *message = "Hello client :)";
    //size of our receive buffer, this is string length.
    //set of socket descriptors
    fd_set readfds;
    //1 extra for null character, string termination
    char *buffer;
    for (i = 0; i < MAX_CLIENT_SOCK; i++) {
        client_socket[i] = 0;
    }
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised...\n");
    //Create a socket
    if ((master = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Socket created...\n");
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    //Bind
    if (bind(master, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Bind done...\n");
    //Listen to incoming connections
    listen(master, 3);
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    addrlen = sizeof(struct sockaddr_in);
    while (TRUE) {
        buffer = (char *) malloc((MAXRECV + 1) * sizeof(char));
        //clear the socket fd set
        FD_ZERO(&readfds);
        //add master socket to fd set
        FD_SET(master, &readfds);
        //add child sockets to fd set
        for (i = 0; i < MAX_CLIENT_SOCK; i++) {
            s = client_socket[i];
            if (s > 0) {
                FD_SET(s, &readfds);
            }
        }
        //wait for an activity on any of the sockets, timeout is NULL , so wait indefinitely
        activity = select(0, &readfds, NULL, NULL, NULL);
        if (activity == SOCKET_ERROR) {
            printf("Select call failed with error code: %ld\n", WSAGetLastError());
            perror("Select call failed");
            exit(EXIT_FAILURE);
        }
        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(master, &readfds)) {
            if ((new_socket = accept(master, (struct sockaddr *) &address, (int *) &addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            //inform user of socket number - used in send and receive commands
            printf("New connection. Socket fd: %d --- IP: %s --- Port : %d\n", new_socket, inet_ntoa(address.sin_addr),
                   ntohs(address.sin_port));
            //send new connection greeting message
            int bytesSent = send(new_socket, message, strlen(message) + 1, 0);
            if (bytesSent == SOCKET_ERROR) {
                perror("Send error. Error" + WSAGetLastError());
            } else {
                printf("Welcome message sent successfully...\n");
            }
            //add new socket to array of sockets
            for (i = 0; i < MAX_CLIENT_SOCK; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets at index %d \n", i);
                    break;
                }
            }
        }
        //else its some IO operation on some other socket :)
        for (i = 0; i < MAX_CLIENT_SOCK; i++) {
            s = client_socket[i];
            //if client presend in read sockets
            if (FD_ISSET(s, &readfds)) {
                //get details of the client
                getpeername(s, (struct sockaddr *) &address, (int *) &addrlen);
                //Check if it was for closing , and also read the incoming message
                //recv does not place a null terminator at the end of the string (whilst printf %s assumes there is one).
                valread = recv(s, buffer, MAXRECV, 0);
                if (valread == SOCKET_ERROR) {
                    int error_code = WSAGetLastError();
                    if (error_code == WSAECONNRESET) {
                        //Somebody disconnected , get his details and print
                        printf("Host disconnected unexpectedly. IP %s --- port %d \n", inet_ntoa(address.sin_addr),
                               ntohs(address.sin_port));
                        //Close the socket and mark as 0 in list for reuse
                        closesocket(s);
                        client_socket[i] = 0;
                    } else {
                        printf("Received failed with error code : %d\n", error_code);
                        exit(EXIT_FAILURE);
                    }
                }
                if (valread == 0) {
                    //Somebody disconnected , get his details and print
                    printf("Host disconnected. IP %s --- Port %d \n", inet_ntoa(address.sin_addr),
                           ntohs(address.sin_port));
                    //Close the socket and mark as 0 in list for reuse
                    closesocket(s);
                    client_socket[i] = 0;
                } else {
                    //Echo back the message that came in
                    buffer[valread] = ' ';
                    printf("Host[IP:PORT]= %s:%d - %s \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port),
                           buffer);
                    send(s, buffer, valread, 0);
                    //save buffer value in a file
                    saveInFile(buffer);
                }
            }
        }
    }
}

void saveInFile(char *buffer) {
    printf("Message: %s\n", buffer);
    FILE *fp = fopen("connection.txt", "a");
    if (fp != NULL) {
        //add timestamp before mesage
        time_t ltime; /* calendar time */
        ltime = time(NULL); /* get current cal time */
        //printf("%s",asctime(localtime(&ltime)));
        fputs(asctime(localtime(&ltime)), fp);
        fputs(buffer, fp);
        fputs("\n", fp);
        fclose(fp);
    } else {
        //create file
        FILE *fpNEW = fopen("connection.txt", "w");
        if (fpNEW != NULL) {
            perror("Impossible to create a file");
        } else {
            fclose(fpNEW);
            saveInFile(buffer);
        }
    }
}

