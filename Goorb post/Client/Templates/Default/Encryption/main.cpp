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
#include "Encryption.hpp"

int main(){
    #if defined(__unix__) || defined(__APPLE__)
	signal(SIGINT, handleSignal);
	signal(SIGTERM, handleSignal);
	#endif
    ifstream f("contact_name.txt");
    getline(f, contact_name);
    f.close();
    init();
    while(!client.open){
        cls();
        cout << "Goorb post\n";
        cout << "Raz protocol\n";
        cout << "Created by: 21\n";
        cout << "_________________________________________\n";
        cout << "Private Message to: " << contact_name << "\n_________________________________________\n";
        string server_ip, server_port_s;
        int server_port = 0;
        cout << "Enter the server IP: ";
        getline(cin, server_ip);
        cout << "Enter the server port: ";
        getline(cin, server_port_s);
        for(auto e: server_port_s)
            server_port = 10 * server_port + (e - '0');
        server_port = max(min(server_port, (1 << 16) - 1), 0);
        client.start(server_ip, server_port);
        if(!client.open){
            cout << "cannot connect to the server press space button to retry\n";
            while(getch() != ' ');
        }
    }
    int cnt_send = 0;
    char c;
    bool two = false;
    while(true){
        while(client.recv_it());
        cls();
        cout << "Goorb post\n";
        cout << "Raz protocol\n";
        cout << "Created by: 21\n";
        cout << "_________________________________________\n";
        cout << "Private Message to: " << contact_name << " ";
        if(!is_online)
            cout << "(not connected yet)";
        else if(is_online == 1)
            cout << "(online)";
        else
            cout << "(disconnected)";
        if(notification.size())
            cout << "\n*" << notification.size() << " nofitication";
        if(notification.size() > 1)
            cout << "s";
        cout << "\n_________________________________________\n";
        cout << "You can choose any of these options by entering their number:\n";
        cout << "  1. Encrypt the draft\n";
        cout << "  2. Send the draft\n";
        cout << "  3. Decode message\n";
        cout << "  4. Update the Bank_y\n";
        cout << "  5. Show notifications\n";
        cout << "  6. Disconnect\n";
        if(two || kbhit()){
            if(!two)
                c = getch();
            if(c == '1')
                encode_to_send();
            if(c == '2'){
                if(!two){
                    ifstream f("../Draft/encoded.txt");
                    if(!f.is_open()){
                        cout << "failed! seems there isn't any encoded.txt file\npress any key to continue";
                        getch();
                        continue;
                    }
                }
                cout << "sending ...\n";
                two = false;
                if(!client.send_it()){
                    two = true;
                    ++cnt_send;
                    if(cnt_send == 5){
                        cnt_send = 0;
                        two = false;
                    }
                    continue;
                }
            }
            if(c == '3'){
                cout << "~ the directory of message: ";
                string dir;
                getline(cin, dir);
                if(dir.empty())
                    dir = ".";
                if(dir.back() != '\\' && dir.back() != '/')
                    dir += '/';
                decode_to_read(dir);
            }
            if(c == '4'){
                cout << "put the update folder in the ./Encryption directory and then press space\n";
                while(getch() != ' ');
                for(int i = 0; i < BY; ++i){
                    ifstream f1("update/" + to_string(i) + ".txt");
                    ofstream f2("../Bank/" + to_string(i) + ".txt", ios::app);
                    string ln;
                    while(getline(f1, ln))
                        if(ln.size())
                            f2 << ln << '\n';
                }
                cout << "ok now delete the update folder and then press space\n";
                while(getch() != ' ');
            }
            if('0' <= c && c <= '4'){
                cout << "task " << c << " done!\npress a key to continue\n";
                getch();
            }
            if(c == '5'){
                cout << "\n____________\nNotifications:\n";
                for(int e: notification)
                    cout << "* " << e << '\n';
                notification.clear();
                cout << "\n____________\npress space key to continue\n";
                while(getch() != ' ');
            }
            if(c == '6'){
                client.end_it();
                is_online += 100;
                continue;
            }
        }
    }
    return 0;
}
