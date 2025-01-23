#include <iostream>
#include <string>
#include <vector>
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
            string keyword;
            int t;
            cout<<"Digite la palabra clave a utilizar: "<<endl;
            cin>>keyword;
            cout<<"Digite el parametro t: "<<endl;
            cin>>t;
            cout<<"Digite el texto a cifrar: "<<endl;
            cin.ignore();
            getline(cin, plain_text);

            int s = plain_text.size();
            int c = count(plain_text.begin(), plain_text.end(), ' ');
            remove(plain_text.begin(), plain_text.end(), ' ');
            plain_text.resize(s - c);


            for_each(plain_text.begin(), plain_text.end(), [](char& ch) {ch = toupper(ch);});
            for_each(keyword.begin(), keyword.end(), [](char& ch) {ch = toupper(ch);});

            string key = keyword;
            while(key.size() < plain_text.size()) {
                key += keyword;
            }

            string output;
            for (int i = 0; i < plain_text.size(); ++i) {
                output.push_back((key[i] - 'A' + plain_text[i] - 'A') % 26 + 'A');
            }
            for (int i = 0; i < output.size(); i += t) {
                cout<<output.substr(i,min(t, (int)output.size() - i))<<" ";
            }
            cout<<endl;
        }
        else if (option == 2) {
            string encrypted_text;
            string keyword;
            int t;
            cout<<"Digite la palabra clave a utilizar: "<<endl;
            cin>>keyword;
            cout<<"Digite el parametro t: "<<endl;
            cin>>t;
            cout<<"Digite el texto a cifrar: "<<endl;
            cin.ignore();
            getline(cin, encrypted_text);

            int s = encrypted_text.size();
            int c = count(encrypted_text.begin(), encrypted_text.end(), ' ');
            remove(encrypted_text.begin(), encrypted_text.end(), ' ');
            encrypted_text.resize(s - c);


            for_each(encrypted_text.begin(), encrypted_text.end(), [](char& ch) {ch = toupper(ch);});
            for_each(keyword.begin(), keyword.end(), [](char& ch) {ch = toupper(ch);});

            string key = keyword;
            while(key.size() < encrypted_text.size()) {
                key += keyword;
            }

            string output;
            for (int i = 0; i < encrypted_text.size(); ++i) {
                output.push_back((encrypted_text[i] - key[i] + 26) % 26 + 'A');
            }
            for (int i = 0; i < output.size(); i += t) {
                cout<<output.substr(i,min(t, (int)output.size() - i))<<" ";
            }
            cout<<endl;
        }
        else if (option == 3) {
            system("cls");
        }
        else break;
    } while (true);
    return 0;
}
