#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define CONNECTION_PORT 3500

int main() {
	int server_socket_desc;
	int client_socket_desc;
	
	int status;
	int length_of_address;
	
	char storage_buffer[100];
	
	char* message = "Welcome Client...!!!";
	
	struct sockaddr_in server_address;
	struct sockaddr_in connection_address;
	
	
	server_socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket_desc < 0) {
		printf("Socket creation failed...\n");
		exit(EXIT_FAILURE);
	}
	printf("Server Socket Created...\n");
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = CONNECTION_PORT;
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	status = bind(server_socket_desc, (struct sockaddr*)&server_address, sizeof(struct sockaddr) );
	if (status < 0 ) {
		printf("Binding failed ...\n");
		exit(EXIT_FAILURE);
	}
	printf("Server socket binding successfull...\n");
	
	status = listen(server_socket_desc, 4);
	if( status < 0 ) {
		printf("Listening failed...\n");
		exit(EXIT_FAILURE);
	}
	
	length_of_address = sizeof(connection_address);
	client_socket_desc = accept(server_socket_desc, (struct sockaddr*)&connection_address, &length_of_address);
	if (client_socket_desc < 0) {
		printf("Connection establishment failed...\n");
		exit(EXIT_FAILURE);
	}
	printf("Connection established with the client...\n");
	
	recv(client_socket_desc, storage_buffer, 100, 0);
	printf("From Client : %s\n", storage_buffer);
	
	send(client_socket_desc, message, 100, 0);
	printf("Message sent to the client...\n");
	
	
	close(server_socket_desc);
	close(client_socket_desc);
	return 0;
	
}
