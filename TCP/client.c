#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define CONNECTION_PORT 3500

int main() {
	int client_sock_descriptor;
	int status;
	struct sockaddr_in server_address;
	
	char* message="Hello to my server...!!!";
	char message_buffer[100];
	
	client_sock_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if(client_sock_descriptor < 0) {
		printf("Socket creation failed...\n");
		exit(EXIT_FAILURE);
	}
	printf("Client Socket Created...\n");
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = CONNECTION_PORT;
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	status = connect(client_sock_descriptor, (struct sockaddr*)&server_address, sizeof(server_address));
	if( status < 0 ) {
		printf("Connection with server failed...\n");
		exit(EXIT_FAILURE);
	}
	printf("Successfully connected with the server...\n");
	
	send(client_sock_descriptor, message, 100, 0);
	printf("Message sent to server...\n");
	
	recv(client_sock_descriptor, message_buffer, 100, 0);
	printf("From Server : %s\n", message_buffer);
	
	close(client_sock_descriptor);
	printf("Connection closed...\n");
	
	return 0;
}
