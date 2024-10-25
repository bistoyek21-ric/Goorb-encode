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
#include "../../alg.hpp"

int constexpr K_ = 8;
int64_t constexpr CAPACITY = 800;
bitset<CAPACITY> mapped;
vector<cipher_block> res[1 << K_];

void init_rescount(){
	rescount = vector<int>(1 << K_, 0);
	for(int i = 0; i < (1 << K_); ++i){
		string s;
		ifstream f("./bank/" + keysname + "/" + to_string(i) + ".txt");
		if(!f.is_open())
			continue;
		while(getline(f, s))
			++rescount[i];
	}
	return;
}

void init(){
    L = 64;
	keysname = "key-0";
	decode = vector<vector<cipher_block>>(1 << K_);
	init_rescount();
	return;
}

void renew(){
    #if defined(__unix__) || defined(__APPLE__)
		system(("rm -fr ./bank/" + keysname + "/*").c_str());
	#else
		system(("del /s /q .\\bank\\" + keysname + "\\* > nul").c_str());
	#endif
	return;
}

void SHA256::set_input(string &input){
    input = "";
    for(int i = 0; i < L; ++i)
        input += (char)('A' + (rand() & 15));
    return;
}

void SHA256::fill_input(string &input){
    cipher_text >> input;
    return;
}

int SHA256::key(uint8_t* hash){
    int res = 0;
    for(int i = 0; i < HASH_SIZE; ++i)
        res ^= hash[i];
    return res;
}

void SHA256::map_it(int res){
    for(int i = 0; i < K_; ++i)
        mapped[len + i] = res & (1 << (K_ - i - 1));
    len += K_;
    if(len % 8 == 0 && CAPACITY - len < K_)
        b_len = true;
    return;
}

string SHA256::translate(){
	string res = "";
	for(int i = 0; i < len; i += K_){
        char c = 0;
        for(int j = i; j < i + K_; ++j)
            c = (c << 1) | mapped[j];
        res += c;
	}
	return res;
}

void note::note_it(ofstream &cipher_text, cipher_block &obj){
	cipher_text << obj.s << '\n';
	return;
}

void _encode_(const string &dir, string typ = ".txt"){
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
	ifstream plain_text(dir + "decoded" + typ, ios::binary);
    ofstream cipher_text(dir + "encoded.txt");
    cipher_text.close();
    len = 0;
	srand(time(nullptr));
	while(true){
		int c = rnb(plain_text) + 128;
		if(c == -1)
            break;
        for(int i = 0; i < 8; ++i)
            mapped[len + i] = ((c & (1 << (7 - i))) != 0);
		len += 8;
		if(len % K_ == 0 && CAPACITY - len < K_){
            cipher_text.open(dir + "encoded.txt", ios::app);
            for(int i = 0; i < len / K_; ++i){
                int num = 0;
                for(int j = i * K_; j < (i + 1) * K_; ++j)
                    num = (num << 1) | mapped[j];
                nt.note_it(cipher_text, res[num][rand() % res[num].size()]);
            }
            cipher_text.close();
            len = 0;
		}
	}
	if(len){
        cipher_text.open(dir + "encoded.txt", ios::app);
        for(int i = 0; i < (len + K_ - 1) / K_; ++i){
            int num = 0;
            for(int j = i * K_; j < (i + 1) * K_; ++j)
                num = (num << 1) | mapped[j];
            nt.note_it(cipher_text, res[num][rand() % res[num].size()]);
        }
        cipher_text.close();
        len = 0;
	}
	return;
}

void _decode_(const string &dir, string typ = ".txt"){
	ifstream cipher_text(dir + "encoded.txt");
	int cnt = 0;
	string s;
	while(getline(cipher_text, s))
		++cnt;
	len = 0;
	b_len = false;
	sha256.decrypt(dir, cnt, typ);
	return;
}
