#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


int main() {
    int option;
    do {
        cout<<"#### SELECCIONE UNA OPCION DEL MENU####"<<endl;
        cout<<"1. Cifrar un mensaje"<<endl;
        cout<<"2. Descifrar un mensaje"<<endl;
        cout<<"3. Limpiar la pantalla"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<">";
        cin>>option;
        if (option == 1) {
            string plain_text;
            string key;
            cout<<"Digite el texto a cifrar: "<<endl;
            cin>>plain_text;
            cout<<"Digite la llave a utilizar: "<<endl;
            cin>>key;
            if (plain_text.size() == key.size()) {
                for_each(plain_text.begin(), plain_text.end(), [](char& ch) {ch = toupper(ch);});
                for_each(key.begin(), key.end(), [](char& ch) {ch = toupper(ch);});
                string output;
                for (int i = 0; i < key.size(); ++i) {
                    output.push_back((plain_text[i] - 'A' + key[i] - 'A') % 26 + 'A');
                }
                cout<<output<<endl;
            }
        }
        else if (option == 2) {
            string encrypted_text;
            string key;
            cout<<"Digite el texto a descifrar: "<<endl;
            cin>>encrypted_text;
            cout<<"Digite la llave a utilizar: "<<endl;
            cin>>key;
            if (encrypted_text.size() == key.size()) {
                for_each(encrypted_text.begin(), encrypted_text.end(), [](char& ch) {ch = toupper(ch);});
                for_each(key.begin(), key.end(), [](char& ch) {ch = toupper(ch);});
                string output;
                for (int i = 0; i < key.size(); ++i) {
                    output.push_back((encrypted_text[i] - key[i] + 26) % 26 + 'A');
                }
                cout<<output<<endl;
            }
        }
        else if (option == 3) {
            system("cls");
        }
        else break;
    } while (true);
    return 0;
}
