#include "../../alg.hpp"

int constexpr K = 8, CAPACITY = 100 * (1 << 10) * 8;
int len;
bitset<CAPACITY> mapped;
vector<cipher_block> res[1 << K];

void init(){
    make_p();
	keysname = "key-1";
	decode = vector<vector<cipher_block>>(1 << K);
	rescount = vector<int>(1 << K, 0);
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

void game::set_factors(){
	cipher_text >> serial_number >> tb >> N >> maxn >> M >> same >> addr >> addr1 >> bl >> blsc >> rang;
	return;
}

void game::fill_factors(){
	maxn = 21 + (rand() & 15);
	N = 5 + (rand() & 3);
	M = 13 + (rand() & 7);
	same = 63 + (rand() & 63);
	addr1 = 512 + (rand() & 511);
	addr = 256 + (rand() & 255);
	bl = 7 + (rand() & 7);
	blsc = 11 + (rand() & 7);
	tb = rand() + ((long long)rand() << 15) + ((long long)rand() << 30) + ((long long)rand() << 45);
	serial_number = rand() + ((long long)rand() << 15) + ((long long)rand() << 30) + ((long long)rand() << 45);
	rang = 3 + (rand() & 3);
	factors.f[0] = serial_number;
	factors.f[1] = tb;
	factors.f[2] = N;
	factors.f[3] = maxn;
	factors.f[4] = M;
	factors.f[5] = same;
	factors.f[6] = addr;
	factors.f[7] = addr1;
	factors.f[8] = bl;
	factors.f[9] = blsc;
	factors.f[10] = rang;
	return;
}

vector<int> game::cmp(int i){
	int x = lst[i][0], y = lst[i][1];
	vector<int> ans = {0, 0};
	if(!check_good({x, y})){
		a[x][y] = canon, exs[x][y] = true;
		ans[0] = 1000000020;
		ans[1] = -1;
		for(int i = maxn - 1; ~i; --i)
			if(not_null(i)){
				ans[1] = i;
				break;
			}
		a[x][y] = 0, exs[x][y] = false;
		ans[1] = (ans[1] == maxn - 1 ? 1000000020 : ans[1]);
	}
	else{
		auto a1 = a;
		auto exs1 = exs;
		auto blast1 = blast;
		a[x][y] = canon, exs[x][y] = true;
		int tmp = pts;
		dfs_blast({x, y});
		pts = tmp;
		fall();
		ans[0] = 0;
		for(int i = 0; i < maxn; ++i)
			for(int j = (ini + i) % 2; j < M; j += 2)
				ans[0] += (int)exs[i][j];
		ans[1] = -1;
		for(int i = maxn - 1; ~i; --i)
			if(not_null(i)){
				ans[1] = i;
				break;
			}
		ans[1] = (ans[1] == maxn - 1 ? 1000000020 : ans[1]);
		a = a1, exs = exs1, blast = blast1;
	}
	return ans;
}

vector<int> game::key(){
    if(mvs + mvs1 == 200)
        return {};
	vector<int> mn = cmp(0), ans = lst[0];
	for(int i = 1; i < lst.size(); ++i){
		auto v = cmp(i);
		if(v < mn)
			mn = v, ans = lst[i];
	}
	return ans;
}

void game::upd_res(int pos){
	if(pos != 1)
		return;
	for(int i = 0; i < maxn; ++i)
		for(int j = 0; j < M; ++j)
			res += a[i][j], res &= (1 << K) - 1;
	return;
}

void game::map_it(){
    for(int i = 0; i < K; ++i)
        mapped[len + i] = res & (1 << (K - i - 1));
    len += K;
    return;
}

string game::translate(){
	string res = "";
	for(int i = 0; i < len; i += K){
        char c = 0;
        for(int j = i; j < i + K; ++j)
            c = (c << 1) | mapped[i];
        res += c;
	}
	return res;
}

void note::note_it(ofstream &cipher_text, cipher_block &obj){
	for(int i = 0; i < 11; ++i)
		cipher_text << obj.f[i] << " ";
	cipher_text << '\n';
	return;
}

void _encode_(){
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
	int cnt = 0;
	string s;
	ifstream plain_text("./messages/" + keysname + "/decoded.txt");
	while(getline(plain_text, s)){
		s += (cnt ? "\n" : "");
		for(int i = 0; i < s.size(); ++i)
			for(int j = 0; j < K; ++j)
				mapped[(cnt + i) * K + j] = (((int)s[i] & (1 << (K - j - 1))) != 0);
		cnt += s.size();
	}
	srand(time(nullptr));
	ofstream cipher_text("./messages/" + keysname + "/encoded.txt");
	for(int i = 0; i < cnt; ++i){
		int num = 0;
		for(int j = i * K; j < (i + 1) * K; ++j)
			num = num * 2 + mapped[j];
		nt.note_it(cipher_text, res[num][rand() % res[num].size()]);
	}
	cipher_text.close();
	return;
}

void _decode_(){
	int cnt = 0;
	ifstream cipher_text("./messages/" + keysname + "/encoded.txt");
	string s;
	while(getline(cipher_text, s))
		++cnt;
	cipher_text.close();
	len = 0;
	g.play("./messages/" + keysname + "/", cnt);
	return;
}
