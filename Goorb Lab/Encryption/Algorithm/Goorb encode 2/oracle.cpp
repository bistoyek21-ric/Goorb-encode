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

cipher_block random_block(){
    cipher_block a;
    a.s = "";
    for(int i = 0; i < 64; ++i)
        a.s += (char)('A' + rand() & 15);
	return a;
}

cipher_block translate(string s){
    cipher_block a;
    a.s = "";
    for(int i = 0; i < 256; i += 4){
        int num = 0;
        for(int j = i; j < i + 4; ++j){
            num <<= 1;
            if(s[j] == '1')
                num += 1;
        }
        a.s += (char)('A' + num);
    }
    return a;
}

string to_bin(cipher_block a){
    string res = "";
    for(int i = 0; i < 64; ++i){
        int num = a.s[i] - 'A';
        for(int j = 3; ~j; --j){
            if((num >> j) & 1)
                res += '1';
            else
                res += '0';
        }
    }
    return res;
}

void ready_res(){
    for(int i = 0; i < (1 << K_); ++i){
		ifstream bank("./bank/" + keysname + "/" + to_string(i) + ".txt");
		bool b = true;
		res[i].clear();
		while(b){
			res[i].push_back({});
            if(bank >> res[i].back().s)
                int x;
            else{
                res[i].pop_back();
                b = false;
            }
		}
		bank.close();
	}
	return;
}

int main(){
	init();
	ready_res();
	int constexpr l_c_p = 256, l_p_b = 8;
	int x, y, supply;
	cout << l_c_p << endl << l_p_b << endl;
	cin >> supply >> x >> y;
	srand(time(nullptr));
	string s;
	while(min(x, y) <= supply){
		cin >> s;
		if(s == "1"){
            if(supply < x){
                cout << "INVALID" << endl;
                continue;
            }
            supply -= x;
            cout << "Cipher_Block" << endl;
            string c_b;
            cin >> c_b;
            cipher_block cb = translate(c_b);
            ofstream encoded("./messages/" + keysname + "/encoded.txt");
            encoded << cb.s << '\n';
            encoded.close();
			_decode_();
            ifstream decoded("./messages/" + keysname + "/decoded.txt");
            unsigned char p_b = decoded.get();
            decoded.close();
            cout << (int)p_b << endl;
		}
		else if(s == "2"){
            if(supply < y){
                cout << "INVALID" << endl;
                continue;
            }
            supply -= y;
            cout << "Plain_Blcok" << endl;
            int p_b;
            cin >> p_b;
            cout << to_bin(res[p_b][rand() % res[p_b].size()]) << endl;
		}
	}
	cout << "Final_Tests" << endl;
	int cnt = 0;
	for(int i = 0; i < 10000; ++i){
        cipher_block cb = random_block();
        ofstream encoded("./messages/" + keysname + "/encoded.txt");
        encoded << cb.s << '\n';
        encoded.close();
        string c_b = to_bin(cb);
        cout << c_b << endl;
        _decode_();
        ifstream decoded("./messages/" + keysname + "/decoded.txt");
        unsigned char p_b = decoded.get();
        decoded.close();
        int p_b_1;
        cin >> p_b_1;
        if((int)p_b == p_b_1)
            ++cnt;
	}
	cout << cnt << endl;
	return 0;
}
