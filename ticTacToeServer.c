#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main()
{

	char server_message[256] = "You have reached the server!";
	char server_message2[256] = "And got little bit of data!";
	char playerCount[1];
	playerCount[0] = 0;

	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port

	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(server_socket, 2);

	int player1;
	player1 = accept(server_socket, NULL, NULL);
	send(player1, playerCount, 1, 0);
	playerCount[0]++;

	int player2;
	player2 = accept(server_socket, NULL, NULL);
	send(player2 & player1, playerCount, 39, 0);

	// send the message

	char client_response[256];
	recv(player1, &client_response, sizeof(client_response), 0);
	printf("Client response: %s\n", client_response);

	// close the socket
	shutdown(server_socket, 2);

	return 0;
}
