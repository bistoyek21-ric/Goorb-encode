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

void runExecutableWithFiles(const std::string &executable, const std::string &inputFile, const std::string &outputFile) {
    std::string command;
#if defined(__unix__) || defined(__APPLE__)
 command = executable + " < " + inputFile + " > " + outputFile + " &";
 #else
 #endifcommand = "start /B " + executable + " < " + inputFile + " > " + outputFile; #endif
int returnCode = system(command.c_str());
if (returnCode != 0) {
std::cerr << "Error: Command failed with return code " << returnCode << std::endl; }
else {
std::cout << "Command executed successfully." << std::endl;
}
}

int main(){
    cout << "Goorb Lab\n";
	cout << "Created by: 21\n";
	cout << "___________________________________________\n\n";
	cout << "\n-----------\n";
	cout << "First step: enter the attacker's directory\n";
	cout << "(If you want to use Goorb Lab's default attacks just press the enter key)\n";
	cout << "~  ";
	string attacker = "";
	getline(cin, attacker);
	if(attacker.empty())
        attacker = "";
    cout << "\n-----------------------------------------------------------\n";
    cout << "Second step: enter the defender's directory\n";
    /*
    #if defined(__unix__) || defined(__APPLE__)
    system();
    system();
    #else
    system();
    system();
    #endif
    */
    std::ofstream(askFile).close();
    std::ofstream(answerFile).close();

	return 0;
}
