/*
MIT License

Copyright (c) 2024 bistoyek(21)

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
#pragma GCC optimize("Ofast")

#include <iostream>
#include <vector>
#include <ctime>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <bitset>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/select.h>
#include <termios.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>

int constexpr BK = 127, EN = 10;

bool kbhit(){
	struct termios oldt, newt;
	int ch, oldf;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if(ch != EOF){
		ungetc(ch, stdin);
		return true;
	}
	return false;
}

int getch(){
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

#else
#include <conio.h>

#include "win_arpa_inet.hpp"

void usleep(int x){
	Sleep(x / 1000);
	return;
}

int constexpr BK = 8, EN = 13;
#endif

using namespace std;

int L;

string keysname;

int rnb(std::ifstream& file){
    char byte;
    if(file.get(byte))
        return byte;
    return -129;
}

void write_zip_header(ofstream &f){
    unsigned char header[22] = {80, 75, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    f.write(reinterpret_cast<char*>(header), sizeof(header));
    return;
}

void create_dir(string dir){
    #if defined(__unix__) || defined(__APPLE__)
    system(("mkdir " + dir).c_str());
    #else
    for(auto &e: dir)
        if(e == '/')
            e = '\\';
    system(("mkdir " + dir).c_str());
    #endif
    return;
}

void move_file(string dir1, string dir2){
    #if defined(__unix__) || defined(__APPLE__)
    system(("mv " + dir1 + " " + dir2).c_str());
    #else
    system(("move " + dir1 + " " + dir2).c_str());
    #endif
    return;
}

void cls(){
	#if defined(__unix__) || defined(__APPLE__)
		system("clear");
	#else
		system("cls");
	#endif
	return;
}
