#include "note.hpp"

struct game{

	int maxn, N, M, same, addr, addr1, bl, blsc, res, rang;

	long long tb, serial_number;

	ifstream cipher_text;
	cipher_block factors;

	vector<vector<int>> a, lst, ok;
	vector<vector<bool>> exs, blast;
	bool enough = false, decode;

	int pts, mvs, mvs1, tries = 0, canon, ini;

	int dx[6] = {0, 0, 1, 1, -1, -1}, dy[6] = {2, -2, -1, 1, -1, 1};

	vector<int> key();
	vector<int> cmp(int i);
	void upd_res(int pos);
	void fill_factors();
	void set_factors();
	void map_it();
	string translate();

	int rnd(){
		int res = 0, k;
		if(_rand() % 8 == 0)
			res = (_rand() % rang + 1) * (rang + 2);
		k = _rand() % rang + 1;
		int cnt = 4;
		while(k == res / (rang + 2) && cnt--){
			k = _rand() % rang + 1;
			if(!cnt)
				k = 0;
		}
		res += k;
		if(res / (rang + 2) > res % (rang + 2))
			return (res % (rang + 2)) * (rang + 2) + res / (rang + 2);
		return res;
	}

	void add_row(){
		ini = (1 - ini);
		for(int i = maxn - 1; i; --i)
			for(int j = 0; j < M; ++j){
				swap(a[i][j], a[i - 1][j]);
				swap(exs[i][j], exs[i - 1][j]);
				swap(blast[i][j], blast[i - 1][j]);
			}
		for(int i = ini; i < M; i += 2){
			for(int k = 0; k < 3; ++k){
				if(!k && i != ini && _rand() <= same)
					a[0][i] = a[0][i - 2];
				else
					a[0][i] = rnd();
				int tmp = pts, tmp1;
				dfs_blast({0, i});
				for(int ii = 0; ii < maxn; ++ii)
					for(int jj = (ii + ini) % 2; jj < M; jj += 2)
						if(blast[ii][jj])
							blast[ii][jj] = false, exs[ii][jj] = true;
				tmp1 = pts, pts = tmp;
				if(tmp1 - tmp <= bl)
					break;
				if(tmp1 - tmp > blsc && k == 2){
					a[0][i] = rang + 1;
					break;
				}
				upd_rnd();
			}
			exs[0][i] = true;
		}
		return;
	}

	void gen(){
		++tries;
		if(decode)
			set_factors();
		else
			fill_factors();
		mvs = mvs1 = res = ini = pts = 0;
		_srand(tb, serial_number);
		a = vector<vector<int>>(maxn, vector<int>(M, 0));
		blast = exs = vector<vector<bool>>(maxn, vector<bool>(M, false));
		lst.clear();
		for(int i = 0; i < N; ++i)
			add_row();
		canon = rnd();
		return;
	}

	void upd_sit(int color){
		for(int i = 0; i < maxn; ++i)
			for(int j = (i + ini) % 2; j < M; j += 2)
				if(!exs[i][j])
					blast[i][j] = a[i][j] = 0;
		canon = color;
		return;
	}

	bool not_null(int i){
		return *max_element(a[i].begin(), a[i].end());
	}

	bool check_end(){
		return not_null(maxn - 1) || !not_null(0);
	}

	bool adj_blast(vector<int> c, vector<int> p){
		if(!(-1 < c[0] && c[0] < maxn) || !(-1 < c[1] && c[1] < M))
			return false;
		if(!exs[c[0]][c[1]])
			return false;
		if(a[p[0]][p[1]] % (rang + 2) == a[c[0]][c[1]] % (rang + 2))
			return true;
		if(a[p[0]][p[1]] / (rang + 2) == a[c[0]][c[1]] % (rang + 2))
			return true;
		if(a[p[0]][p[1]] % (rang + 2)  == a[c[0]][c[1]] / (rang + 2))
			return true;
		if(a[p[0]][p[1]] / (rang + 2) == a[c[0]][c[1]] / (rang + 2) && a[c[0]][c[1]] > (rang + 2))
			return true;
		return false;
	}

	void dfs_blast(vector<int> c){
		++pts;
		blast[c[0]][c[1]] = true;
		exs[c[0]][c[1]] = false;
		for(int i = 0; i < 6; ++i)
			if(adj_blast({c[0] + dx[i], c[1] + dy[i]}, c) && exs[c[0] + dx[i]][c[1] + dy[i]])
				dfs_blast({c[0] + dx[i], c[1] + dy[i]});
		return;
	}

	bool adj_conct(vector<int> c){
		if(!(-1 < c[0] && c[0] < maxn) || !(-1 < c[1] && c[1] < M))
			return false;
		return !exs[c[0]][c[1]] && !blast[c[0]][c[1]] && a[c[0]][c[1]];
	}

	int dfs_conct(vector<int> c){
		int res = 1;
		exs[c[0]][c[1]] = true;
		for(int i = 0; i < 6; ++i)
			if(adj_conct({c[0] + dx[i], c[1] + dy[i]}))
				res += dfs_conct({c[0] + dx[i], c[1] + dy[i]});
		return res;
	}

	int check_good(vector<int> c, bool sen = true){
		int cnt = 0, mx = 0;
		for(int i = 0; i < 6; ++i)
			if(adj_blast({c[0] + dx[i], c[1] + dy[i]}, c)){
				if(sen)
					mx = max(mx, check_good({c[0] + dx[i], c[1] + dy[i]}, false));
				++cnt;
			}
		return (sen ? (int)(max(mx, cnt) > 1) : cnt);
	}

	void fall(){
		for(int i = 0; i < maxn; ++i)
			for(int j = 0; j < M; ++j)
				exs[i][j] = false;
		for(int i = ini; i < M; i += 2)
			if(!blast[0][i] && a[0][i])
				dfs_conct({0, i});
		return;
	}

	void dfs_ok(vector<int> c){
		ok[c[0]][c[1]] = 1;
		int adj_cell = 0;
		for(int i = 0; i < 6; ++i){
			int x = c[0] + dx[i], y = c[1] + dy[i];
			if(0 <= x && 0 <= y && x < maxn && y < M && ok[x][y] != -1)
				++adj_cell;
		}
		if(c[0] == maxn - 1)
			adj_cell += 2;
		if(adj_cell <= 2)
			return;
		for(int i = 0; i < 6; ++i){
			int x = c[0] + dx[i], y = c[1] + dy[i];
			if(0 <= x && 0 <= y && x < maxn && y < M && !ok[x][y])
				dfs_ok(vector<int>{x, y});
		}
		return;
	}

	void updlst(){
		lst.clear();
		ok.clear();
		for(int i = 0; i < maxn; ++i){
			ok.push_back({});
			for(int j = 0; j < M; ++j)
				ok[i].push_back(exs[i][j] ? -1 : 0);
		}
		dfs_ok({maxn - 1, (maxn + ini - 1) % 2});
		for(int i = 0; i < maxn; ++i)
			for(int j = (ini + i) % 2; j < M; j += 2)
				if(!exs[i][j] && ok[i][j] == 1)
					for(int k = 0; k < 6; ++k)
						if(i + dx[k] < maxn && -1 < i + dx[k])
							if(j + dy[k] < M && -1 < j + dy[k])
								if(exs[i + dx[k]][j + dy[k]]){
									lst.push_back({i, j});
									break;
								}
		ok.clear();
		return;
	}

	void upd_rnd(){
		int num = 0, bs = 71, mod = 1000000021;
		for(int i = 0; i < maxn; ++i)
			for(int j = 0; j < M; ++j)
				num = ((num * bs) % mod + a[i][j]) % mod;
		num %= 21;
		while(num-- >= 0)
			if(_rand() & 1)
				_rand();
		return;
	}

	int search_it(vector<int> c){
		int l = 0, r = lst.size();
		while(r - l > 1){
			int mid = (l + r) / 2;
			if(lst[mid][0] > c[0] || (lst[mid][0] == c[0] && lst[mid][1] > c[1]))
				r = mid;
			else
				l = mid;
		}
		if(lst[l][0] != c[0] || lst[l][1] != c[1])
			return 0;
		return l + 1;
	}

	void F(){
		gen();
		upd_res(0);
		while(true){
			upd_res(1);
			if(check_end())
				break;
			updlst();
			vector<int> x = key();
			if(x.empty()){
				upd_res(2);
				break;
			}
			upd_res(3);
			int s_it = search_it(x);
			while(s_it--)
				_rand();
			a[x[0]][x[1]] = canon, exs[x[0]][x[1]] = true;
			if(!check_good(x)){
				++mvs1;
				upd_sit(rnd());
				upd_res(4);
				if(_rand() <= addr1)
					add_row();
				if(check_end())
					break;
				continue;
			}
			++mvs;
			dfs_blast(x), --pts;
			fall();
			upd_sit(canon);
			upd_rnd();
			if(_rand() <= addr)
				add_row();
			canon = rnd();
			upd_res(5);
		}
		quality += mvs + mvs1;
		if(!decode)
			enough = add_it(factors, res);
		upd_res(6);
		return;
	}

	void play(string dir = "", int times = -1){
		decode = !dir.empty();
		if(decode){
			cipher_text.open(dir + "encoded.txt");
			while(times--)
				F(), map_it();
			ofstream plain_text(dir + "decoded.txt");
			plain_text << translate();
			plain_text.close();
			cipher_text.close();
		}
		else{
			if(times == -1){
                enough = false;
				while(!enough)
					F();
			}
			else
				while(times--)
					F();
			flush_it();
		}
		return;
	}
} g;
