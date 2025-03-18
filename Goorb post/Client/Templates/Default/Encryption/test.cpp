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
#include "selected.hpp"

void Encryption(){
	init();
	while(true){
		cls();
		cout << "Goorb encode 2" << '\n';
		cout << "Created by: 21" << '\n';
		time_t t = time(nullptr);
		cout << "___________________________________\n";
		cout << ctime(&t);
		cout << "Key's name: " << keysname << '\n';
		cout << "___________________________________\n\n";
		cout << "You have these options:" << '\n';
		cout << "  1. decode\n";
		cout << "  2. encode\n";
		cout << "  3. make stronger the bank\n";
		cout << "  4. delete the bank and generate a new one\n";
		cout << "  5. delete the bank\n";
		string dir = "./messages/" + keysname + "/", s;
		getline(cin, s);
		if(s == "1"){
			time_t t = time(nullptr);
			_decode_(dir);
			cout << "task 1:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "2"){
			time_t t = time(nullptr);
			_encode_(dir);
			cout << "task 2:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "3"){
			int times;
			cout << "How many times? ";
			cin >> times;
			times = min(max(times, 1), 1021);
			time_t t = time(nullptr);
			cls();
			calls = 0;
			cout << "starting time: " << ctime(&t) << "tries: " << times << "\n--------\n";
			sha256.encrypt(times);
			cout << "task 3:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "4"){
            time_t t = time(nullptr);
			renew();
			cls();
			calls = 0;
			cout << "starting time: " << ctime(&t) << "--------\n";
			rescount = vector<int>(1 << K_, 0);
			sha256.encrypt();
			cout << "task 4:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "5"){
            time_t t = time(nullptr);
            renew();
            rescount = vector<int>(1 << K_, 0);
            calls = 0;
            cout << "task 5:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
	}
	return;
}

int main(){
    Encryption();
    return 0;
}
