/*
MIT License

Copyright (c) 2024 bistoyek21 R.I.C.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <unistd.h>
#include <time.h>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/select.h>
#include <termios.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void disable_input_buffering(){
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ICANON;
	t.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void restore_input_buffering(){
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ICANON | ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int kbhit(){
	disable_input_buffering();
	struct timeval tv = {0, 0};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds);
	int res = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
	restore_input_buffering();
	return res;
}

int getch(){
	disable_input_buffering();
	int res = getchar();
	restore_input_buffering();
	return res;
}

#else
#include "win_arpa_inet.hpp"

#include <conio.h>
#endif

int constexpr PORT = 10000;

int client[2], server_socket_, cnt;

#if defined(__unix__) || defined(__APPLE__)
void handleSignal(int signal){
    if(signal == SIGINT || signal == SIGTERM){
        for(int i = 0; i < 2; ++i)
            send(client[i], "0 0 ", 4, 0);
    	close(client[0]);
        close(client[1]);
        close(server_socket_);
    }
}

#endif

int main(){
    #if defined(__unix__) || defined(__APPLE__)
	signal(SIGINT, handleSignal);
	signal(SIGTERM, handleSignal);
	#endif
	std::cout << "Goorb post\n";
	std::cout << "Raz protocol\n";
	std::cout << "Created by: 21\n";
	std::cout << "____________________________________________________\n\n";
    	#if !defined(__unix__) && !defined(__APLLE__)
    	WSADATA wsaData;
    	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0){
        	std::cerr << "WSAStartup failed" << std::endl;
        	return 1;
    	}
    	#endif
	char host[256];
	gethostname(host, sizeof(host));
	std::cout << "Server IP: " << inet_ntoa(*((struct in_addr*)gethostbyname(host)->h_addr_list[0])) << '\n';
	std::cout << "Running on port: " << PORT << '\n';
	std::cout << "-------------\n\n";
	int server_socket, client_socket;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_len = sizeof(client_addr);
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(server_socket == -1){
		std::cerr << "Failed to create socket" << std::endl;
		return 1;
	}
	server_socket_ = server_socket;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);
	if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		std::cerr << "Failed to bind socket" << std::endl;
		return 1;
	}
	if(listen(server_socket, 2) == -1){
		std::cerr << "Failed to listen on socket" << std::endl;
		return 1;
	}
	std::cout << "Server is running..." << std::endl;
	for(int i = 0; i < 2; ++i){
		client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
		if(client_socket == -1){
			std::cerr << "Failed to accept client" << std::endl;
			--i;
			continue;
		}
		struct timeval timeout;
        	timeout.tv_sec = 1;
        	timeout.tv_usec = 0;
        	#if defined(__unix__) || defined(__APPLE__)
        	auto t = &timeout;
        	#else
        	int ms = 1000;
        	char* t = (char*)&ms;
        	#endif
        	if(setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, t, sizeof(timeout)) < 0){
            		std::cout << "Error setting socket options" << '\n';
            		return 1;
        	}
		std::cout << "Connection from " << inet_ntoa(client_addr.sin_addr) << std::endl;
		client[i] = client_socket;
	}
	for(int i = 0; i < 2; ++i)
        	send(client[i], "0 ", 2, 0);
	char c[1];
	bool b = true;
	std::cout << "You can stop the server by pressing '~' key\n";
	for(int i = 0; b; i = 1 - i){
		while(b){
			if(kbhit() && getch() == '~')
				b = false;
			if(recv(client[i], c, 1, 0) <= 0 || c[0] == '~')
				break;
			if(c[0] == '!'){
				send(client[i], c, 1, 0);
				continue;
			}
			send(client[1 - i], c, 1, 0);
		}
		if(c[0] == '~')
			break;
	}
	for(int i = 0; i < 2; ++i)
        	send(client[i], "0 0 ", 4, 0);
	close(client[0]);
	close(client[1]);
	close(server_socket_);
	#if !defined(__unix__) && !defined(__APPLE__)
	WSACleanup();
	#endif
	time_t t = time(nullptr);
	while(time(nullptr) - t < 3);
	return 0;
}
