#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<time.h>
#include<conio.h>
#include<algorithm>
#include<bitset>
#include<cstring>
using namespace std;

static int L;

string keysname;

void cls(){
	#ifdef __unix__
		system("clear");
	#elifdef __mach__
		system("clear");
	#else
		system("cls");
	#endif
	return;
}
