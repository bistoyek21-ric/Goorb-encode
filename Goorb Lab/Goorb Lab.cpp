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
    cout << "Goorb Lab\n";
	cout << "Created by: 21\n";
    cout << "- bistoyek21 RIC first mini lab\n";
    cout << "- developed by Kasra Fouladi\n";
    cout << "- a part of Goorb-encode research project\n";
	cout << "___________________________________________\n\n";
	cout << "To use Goorb Lab the system has to be able to run python3 codes\n";
	cout << "\n~~~~~~~~~~~~~~~~~~~\n";
	string run_attacker, run_defender;
    cout << "First step: enter a command line that runs the defender (mind the direcroty)\n";
    cout << "~ ";
    getline(cin, run_defender);
    cout << "\n-----------------------------------------------------------\n";
    cout << "Second step: enter the a command line that runs attacker (mind the directory)\n";
    cout << "~ ";
	getline(cin, run_attacker);
    cout << "\n-----------------------------------------------------------\n";
    ofstream a("./intractor/a.py");
    a << "import os\nos.system(\"cd ../ && " << run_defender << "\")\n";
    a.close();
    ofstream b("./intractor/b.py");
    b << "import os\nos.system(\"cd ../ && " << run_attacker << "\")\n";
    b.close();
    system("python ./intractor/intractor.py");
    cout << "done! :)" << '\n';
	return 0;
}
