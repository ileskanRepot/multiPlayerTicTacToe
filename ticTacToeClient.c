#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int updateMap(char map[10])
{
	for (unsigned int i = 0; i < 9; ++i)
	{
		unsigned int x = (i % 3) * 2 + 3;
		unsigned int y = (i / 3) * 2 + 3;
		//printf("\nx: %u\ny: %u\n", x, y);
		printf("\033[%u;%uH%c", y, x, map[i]);
	}
	return 0;
}

int main()
{

	// create a socket
	int network_socket;
	network_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = inet_addr("192.168.8.169"); //INADDR_ANY;

	int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	// check for error with the connection
	if (connection_status == -1)
	{
		printf("There was an error making a connection to the remote socket \n\n");
	}

	// recive data from the server

	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	char server_response2[256];
	recv(network_socket, &server_response2, sizeof(server_response), 0);

	char client_message[256] = "Dataa";
	send(network_socket, client_message, sizeof(client_message), 0);

	// print out the data server's response
	printf("The server sent the sata: %s\nAnd this: %s\n", server_response, server_response2);

	// and then close the socket

	// draw board
	shutdown(network_socket, 2);
	return 0;
}
