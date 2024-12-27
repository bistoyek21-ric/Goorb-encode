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
#include "selected.hpp"

int main(){
	init();
	while(true){
		cls();
		cout << "Goorb encode 1" << '\n';
		cout << "Created by: 21" << '\n';
		time_t t = time(0);
		cout << "___________________________________\n";
		cout << ctime(&t);
		cout << "Key's name: " << keysname << '\n';
		cout << "___________________________________\n\n";
		cout << "You have these options:" << '\n';
		cout << "  1. decode\n";
		cout << "  2. encode\n";
		cout << "  3. make stronger the bank\n";
		cout << "  4. delete the bank and generate a new one\n";
		string s;
		getline(cin, s);
		if(s == "1"){
			time_t t = time(nullptr);
			_decode_();
			cout << "task 1:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "2"){
			time_t t = time(nullptr);
			_encode_();
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
			calls = quality = 0;
			cout << "starting time: " << ctime(&t) << "tries: " << times << "\n--------\n";
			g.play("", times);
			cout << "task 3:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
		if(s == "4"){
			renew();
			time_t t = time(nullptr);
			cls();
			calls = quality = 0;
			cout << "starting time: " << ctime(&t) << "--------\n";
			rescount = vector<int>(1 << K, 0);
			g.play();
			cout << "task 4:\ndone!\npress any key to continue\n";
			cout << "in: " << time(nullptr) - t << " seconds\n";
			getch();
		}
	}
	return 0;
}
