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
#include "basic.hpp"

int constexpr buff = 10, KB = 2, per = 1000;

struct cipher_block{
	string s;
};

struct note{
	void note_it(ofstream &f, cipher_block &obj);
} nt;

vector<vector<cipher_block>> decode;
vector<int> rescount;

long long calls = 0;

void bank_info(){
	cout << "____________________________________________\n";
	cout << "~ " << keysname + "'s bank log:" << '\n';
	time_t t = time(nullptr);
	cout << ctime(&t) << '\n';
	int cnt[decode.size()] = {}, sum = 0, len = 1;
	for(int i = 0; i < decode.size(); ++i){
		ifstream f1("./bank/" + keysname + "/" + to_string(i) + ".txt");
		int cnt1 = 0;
		string s;
		if(!f1.is_open())
			++cnt[0];
		else{
			while(getline(f1, s))
				++cnt1, ++sum;
			++cnt[cnt1];
		}
		len = max(len, cnt1 + 1);
		f1.close();
	}
	cout << "All codes: " << sum << "\n---------\n";
	for(int i = 0; i < len; ++i){
		cout << cnt[i];
		for(int j = 0; j < 5 - to_string(cnt[i]).size(); ++j)
			cout << " ";
		cout << "|";
	}
	cout << '\n';
	for(int i = 0; i < len; ++i){
		cout << i;
		for(int j = 0; j < 5 - to_string(i).size(); ++j)
			cout << " ";
		cout << "|";
	}
	cout << '\n';
	return;
}

void flush_it(){
	for(int res = 0; res < decode.size(); ++res){
		ofstream f("./bank/" + keysname + "/" + to_string(res) + ".txt", ios::app);
		for(int i = 0; i < decode[res].size(); ++i)
			nt.note_it(f, decode[res][i]);
		f.close();
		rescount[res] += decode[res].size();
		decode[res].clear();
	}
	bank_info();
	return;
}

bool add_it(cipher_block &obj, int res){
	++rescount[res];
	decode[res].push_back(obj);
	if(sizeof(decode) >= 1024.0 * KB)
		flush_it();
	else if(decode[res].size() == buff){
		ofstream f("./bank/" + keysname + "/" + to_string(res) + ".txt", ios::app);
		for(int i = 0; i < decode[res].size(); ++i)
			nt.note_it(f, decode[res][i]);
		f.close();
		decode[res].clear();
	}
	if(!((++calls) % per))
		flush_it();
	return *min_element(rescount.begin(), rescount.end());
}
