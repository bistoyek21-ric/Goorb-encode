#include "../../alg.hpp"

int constexpr K_ = 8, CAPACITY = 100 * (1 << 10) * 8;
int len;
bitset<CAPACITY> mapped;
vector<cipher_block> res[1 << K_];

void init(){
    L = 64;
	keysname = "key-0";
	decode = vector<vector<cipher_block>>(1 << K_);
	rescount = vector<int>(1 << K_, 0);
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

void _encode_(){
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
	int cnt = 0;
	string s;
	ifstream plain_text("./messages/" + keysname + "/decoded.txt");
	while(getline(plain_text, s)){
		s += (cnt ? "\n" : "");
		for(int i = 0; i < s.size(); ++i)
			for(int j = 0; j < K_; ++j)
				mapped[(cnt + i) * K_ + j] = (((int)s[i] & (1 << (K_ - j - 1))) != 0);
		cnt += s.size();
	}
	srand(time(nullptr));
	ofstream cipher_text("./messages/" + keysname + "/encoded.txt");
	for(int i = 0; i < cnt; ++i){
		int num = 0;
		for(int j = i * K_; j < (i + 1) * K_; ++j)
			num = (num << 1) | mapped[j];
		nt.note_it(cipher_text, res[num][rand() % res[num].size()]);
	}
	cipher_text.close();
	return;
}

void _decode_(){
	ifstream cipher_text("./messages/" + keysname + "/encoded.txt");
	int cnt = 0;
	string s;
	while(getline(cipher_text, s))
		++cnt;
	len = 0;
	sha256.decrypt("./messages/" + keysname + "/", cnt);
	return;
}
