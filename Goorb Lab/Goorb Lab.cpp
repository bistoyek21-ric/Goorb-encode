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
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

int main(){
    bool bistoyek_special_test = false;
    cout << "Goorb Lab\n";
	cout << "Created by: 21\n";
    cout << "- bistoyek21 RIC first mini lab\n";
    cout << "- developed by Kasra Fouladi\n";
    cout << "- a part of Goorb-encode research project\n";
	cout << "___________________________________________\n\n";
	string attacker = "", defender = "";
    cout << "First step: enter the defender's address\n";
    cout << "~ ";
    getline(cin, defender);
    cout << "\n-----------------------------------------------------------\n";
    cout << "Second step: enter the attacker's address\n";
    cout << "(if you want to use bistoyek special test just press enter key)\n";
    cout << "~ ";
	getline(cin, attacker);
	if(attacker.empty()){
        bistoyek_special_test = true;
        attacker = "./Attacks/attack.py";
    }
    cout << "\n-----------------------------------------------------------\n";
    /*
    intractive mechanism
    */
	return 0;
}
