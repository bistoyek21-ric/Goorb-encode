#include "basic.hpp"

long long jomle, mod = (1 << 16) + 1;

long long random[18], seed[18], sn[18], p[(1 << 16) + 1][11];

void make_p(){
	for(int i = 0; i < mod; ++i){
		p[i][0] = 1;
		for(int j = 1; j < 11; ++j)
			p[i][j] = (i * p[i][j - 1]) % mod;
	}
	return;
}

long long binpow(long long a, long long b){
	long long res = 1;
	b %= mod - 1;
	while(b){
		if(b & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}

int _rand(){
	long long sum = 1;
	for(int i = 0; i < 18; ++i)
		sum = (sum + sn[i] * p[random[i]][seed[i]]) % mod;
	random[0] = binpow(sum + (int)(sum == 0), ++jomle);
	for(int i = 0; i < 17; ++i)
		swap(random[i], random[i + 1]);
	return random[17] & 1023;
}

void _srand(long long tb, long long serial_number){
	for(int i = 0; i < 18; ++i){
		sn[i] = serial_number % 10 + 1;
		seed[i] = tb % 10 + 1;
		serial_number /= 10;
		tb /= 10;
		random[i] = 0;
	}
	jomle = 18;
	for(int i = 0; i < 1024; ++i)
		_rand();
	return;
}
