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
    a.f[0] = rand() + ((long long)rand() << 15) + ((long long)rand() << 30) + ((long long)rand() << 45);
    a.f[1] = rand() + ((long long)rand() << 15) + ((long long)rand() << 30) + ((long long)rand() << 45);
    a.f[2] = 5 + (rand() & 3);
    a.f[3] = 21 + (rand() & 15);
    a.f[4] = 13 + (rand() & 7);
    a.f[5] = 63 + (rand() & 63);
    a.f[6] = 256 + (rand() & 255);
    a.f[7] = 512 + (rand() & 511);
    a.f[8] = 7 + (rand() & 7);
	a.f[9] = 11 + (rand() & 7);
	a.f[10] = 3 + (rand() & 3);
	return a;
}

cipher_block translate(string s){
    cipher_block a;
    int l[11] = {60, 60, 2, 4, 3, 6, 8, 9, 3, 3, 2};
    long long b[11] = {0, 0, 5, 21, 13, 63, 256, 512, 7, 11, 3};
    int k = 0;
    for(int i = 0; i < 11; ++i){
        a.f[i] = 0;
        for(int j = 0; j < l[i]; ++j, ++k){
            a.f[i] <<= 1;
            if(s[k] == '1')
                a.f[i] ^= 1;
        }
        a.f[i] += b[i];
    }
    return a;
}

string to_bin(cipher_block a){
    string res = "";
    int l[11] = {60, 60, 2, 4, 3, 6, 8, 9, 3, 3, 2};
    long long b[11] = {0, 0, 5, 21, 13, 63, 256, 512, 7, 11, 3};
    for(int i = 0; i < 11; ++i){
        for(int j = l[i] - 1; ~j; --j){
            if(((a.f[i] - b[i]) >> j) & 1)
                res += '1';
            else
                res += '0';
        }
    }
    return res;
}

void ready_res(){
    for(int i = 0; i < (1 << K); ++i){
		ifstream bank("./bank/" + keysname + "/" + to_string(i) + ".txt");
		bool b = true;
		res[i].clear();
		while(b){
			res[i].push_back({});
			for(int j = 0; j < 11 && b; ++j)
				if(bank >> res[i].back().f[j])
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
	int constexpr l_c_p = 160, l_p_b = 8;
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
            for(int i = 0; i < 11; ++i)
                encoded << cb.f[i] << " ";
            encoded << '\n';
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
        for(int j = 0; j < 11; ++j)
            encoded << cb.f[j] << " ";
        encoded << '\n';
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
