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
#include "note.hpp"

bool b_len;
int len;

class SHA256 {
public:
    bool decode, enough;
    static const size_t HASH_SIZE = 32;

    ifstream cipher_text;

    void set_input(string &input);
    void fill_input(string &input);
    int key(uint8_t* hash);
    void map_it(int res);
    string translate();

    void decrypt(string dir, int times, string typ = ".txt"){
        decode = true;
        cipher_text.open(dir + "encoded.txt");
        ofstream plain_text(dir + "decoded" + typ);
        plain_text.close();
        while(times--){
            F();
            if(!b_len)
                continue;
            ofstream plain_text;
            plain_text.open(dir + "decoded" + typ, ios::binary | ios::app);
            string s = translate();
            for(auto &c: s)
                plain_text << (char)(c - 128);
            len = 0;
            b_len = false;
            plain_text.close();
        }
        if(!len)
            return;
        plain_text.open(dir + "decoded" + typ, ios::binary | ios::app);
        string s = translate();
        for(auto &c: s)
            plain_text << (char)(c - 128);
        plain_text.close();
        cipher_text.close();
        return;
    }

    void encrypt(int times = -1){
        decode = false;
        srand(time(nullptr));
        if(times == -1){
            enough = false;
            while(!enough)
                F();
        }
        else
            while(times--)
                F();
        flush_it();
        return;
    }

    void F(){
        reset();
        cipher_block obj;
        if(decode)
            fill_input(obj.s);
        else
            set_input(obj.s);
        auto input = obj.s.c_str();
        uint8_t hash[HASH_SIZE] = {};
        update(reinterpret_cast<const uint8_t*>(input), strlen(input));
        finalize(hash);
        int res = key(hash);
        if(decode)
            map_it(res);
        else
            enough = add_it(obj, res);
        return;
    }

    void update(const uint8_t* data, size_t length) {
        size_t i = 0;
        while (i < length) {
            size_t chunk_size = std::min(BLOCK_SIZE - buffer_size, length - i);
            std::memcpy(buffer + buffer_size, data + i, chunk_size);
            buffer_size += chunk_size;
            i += chunk_size;

            if (buffer_size == BLOCK_SIZE) {
                process_block(buffer);
                buffer_size = 0;
            }
        }
    }

    void finalize(uint8_t* hash) {
        buffer[buffer_size] = 0x80;
        if (buffer_size >= BLOCK_SIZE - 8) {
            std::memset(buffer + buffer_size + 1, 0, BLOCK_SIZE - buffer_size - 1);
            process_block(buffer);
            buffer_size = 0;
        }
        std::memset(buffer + buffer_size + 1, 0, BLOCK_SIZE - buffer_size - 9);
        uint64_t total_bits = total_length * 8;
        for (int i = 0; i < 8; ++i)
            buffer[BLOCK_SIZE - 1 - i] = total_bits >> (8 * i);
        process_block(buffer);

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 4; ++j) {
                hash[i * 4 + j] = (state[i] >> (24 - j * 8)) & 0xFF;
            }
        }
    }

private:
    static const size_t BLOCK_SIZE = 64;

    const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    uint32_t state[8];
    uint8_t buffer[BLOCK_SIZE];
    size_t buffer_size;
    uint64_t total_length;

    void reset() {
        state[0] = 0x6a09e667;
        state[1] = 0xbb67ae85;
        state[2] = 0x3c6ef372;
        state[3] = 0xa54ff53a;
        state[4] = 0x510e527f;
        state[5] = 0x9b05688c;
        state[6] = 0x1f83d9ab;
        state[7] = 0x5be0cd19;
        buffer_size = 0;
        total_length = 0;
    }

    void process_block(const uint8_t* block) {
        uint32_t w[64];
        for (int i = 0; i < 16; ++i) {
            w[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | block[i * 4 + 3];
        }
        for (int i = 16; i < 64; ++i) {
            uint32_t s0 = right_rotate(w[i - 15], 7) ^ right_rotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
            uint32_t s1 = right_rotate(w[i - 2], 17) ^ right_rotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }

        uint32_t a = state[0];
        uint32_t b = state[1];
        uint32_t c = state[2];
        uint32_t d = state[3];
        uint32_t e = state[4];
        uint32_t f = state[5];
        uint32_t g = state[6];
        uint32_t h = state[7];

        for (int i = 0; i < 64; ++i) {
            uint32_t S1 = right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h + S1 + ch + K[i] + w[i];
            uint32_t S0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
        state[5] += f;
        state[6] += g;
        state[7] += h;

        total_length += BLOCK_SIZE;
    }

    uint32_t right_rotate(uint32_t value, uint32_t count) {
        return (value >> count) | (value << (32 - count));
    }

} sha256;
