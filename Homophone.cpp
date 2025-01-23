#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

int m = 100;
map<char,vector<int>> layout;
vector<char> layout_inverse;

void fillLayout() {
    layout.insert({'A',{9, 12, 33, 47, 53, 67, 78, 92}});
    layout.insert({'B',{48, 81}});
    layout.insert({'C',{13, 41, 62}});
    layout.insert({'D',{1, 3, 45, 79}});
    layout.insert({'E',{14, 16, 24, 44, 46, 55, 57, 64, 74, 82, 87, 98}});
    layout.insert({'F',{10, 31}});
    layout.insert({'G',{6, 25}});
    layout.insert({'H',{23, 39, 50, 56, 65, 68}});
    layout.insert({'I',{32, 70, 73, 83, 88, 93}});
    layout.insert({'J',{15}});
    layout.insert({'K',{4}});
    layout.insert({'L',{26, 37, 51, 84}});
    layout.insert({'M',{22, 27}});
    layout.insert({'N',{18, 58, 59, 66, 71, 91}});
    layout.insert({'O',{0, 5, 7, 54, 72, 90, 99}});
    layout.insert({'P',{38, 95}});
    layout.insert({'Q',{94}});
    layout.insert({'R',{29, 35, 40, 42, 77, 80}});
    layout.insert({'S',{11, 19, 36, 76, 86, 96}});
    layout.insert({'T',{17, 20, 30, 43, 49, 69, 75, 85, 97}});
    layout.insert({'U',{8, 61, 63}});
    layout.insert({'V',{34}});
    layout.insert({'W',{60, 89}});
    layout.insert({'X',{28}});
    layout.insert({'Y',{21, 52}});
    layout.insert({'Z',{2}});
}

void descypher() {
    for (int i = 0; i < m; ++i) {
        bool ok = 0;
        for (auto it = layout.begin(); it != layout.end(); it = next(it)) {
            for (int j = 0; j < it->second.size(); ++j) {
                if (i == it->second[j]) {
                    layout_inverse.push_back(it->first);
                    ok = 1;
                    break;
                }
            }
            if (ok) break;
        }
    }
}


int main() {
    fillLayout();
    descypher();
    srand(time(0));
    int option;
    do {
        cout<<"#### SELECCIONE UNA OPCION DEL MENU####"<<endl;
        cout<<"1. Cifrar un mensaje"<<endl;
        cout<<"2. Descifrar un mensaje"<<endl;
        cout<<"3. Limpiar la pantalla"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"> ";
        cin>>option;
        if (option == 1) {
            string plain_text;
            cout<<"Digite el texto a cifrar: "<<endl;
            cin.ignore();
            getline(cin, plain_text);

            int s = plain_text.size();
            int c = count(plain_text.begin(), plain_text.end(), ' ');
            remove(plain_text.begin(), plain_text.end(), ' ');
            plain_text.resize(s - c);

            for_each(plain_text.begin(), plain_text.end(), [](char& ch) {ch = toupper(ch);});

            vector<int> output;
            for (int i = 0; i < plain_text.size(); ++i) {
                output.push_back(layout[plain_text[i]][rand() % layout[plain_text[i]].size()]);
            }
            for (int i = 0; i < output.size(); ++i) {
                cout<<output[i]<<" ";
            }
            cout<<endl;
        }
        else if (option == 2) {
            string encrypted_text;
            cout<<"Digite el texto a descifrar: "<<endl;
            cin.ignore();
            getline(cin, encrypted_text);

            vector<int> encrypted_message;
            while (encrypted_text.size() > 0) {
                if (encrypted_text.find(" ") == string::npos) {
                    encrypted_message.push_back(stoi(encrypted_text));
                    encrypted_text = "";
                }
                else {
                    int pos = encrypted_text.find(" ");
                    encrypted_message.push_back(stoi(encrypted_text.substr(0, pos)));
                    encrypted_text.erase(0, pos + 1);
                }
            }

            string output;
            for (int i = 0; i < encrypted_message.size(); ++i) {
                output.push_back(layout_inverse[encrypted_message[i]]);
            }
            cout<<output<<endl;
        }
        else if (option == 3) {
            system("cls");
        }
        else break;
    } while (true);
    return 0;
}
