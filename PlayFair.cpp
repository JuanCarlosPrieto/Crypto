#include <iostream>
#include <string>
#include <algorithm>
#include <map>
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
            int index_row = 0;
            int index_col = 0;
            string plain_text;
            string key;
            char matrix[5][5];
            map<char,pair<int,int>> position;

            cout<<"Digite el texto a cifrar: "<<endl;
            cin>>plain_text;
            cout<<"Digite la llave a utilizar, de no estar completa se rellenara en orden alfabetico: "<<endl;
            cin>>key;

            for_each(plain_text.begin(), plain_text.end(), [](char& ch) {ch = toupper(ch);});
            for_each(key.begin(), key.end(), [](char& ch) {ch = toupper(ch);});

            if (plain_text.size() % 2 != 0) {
                plain_text.push_back('X');
            }

            for (int i = 0; i < key.size(); ++i) {
                if (key[i] == 'I') {
                    if (position.find(key[i]) == position.end() && position.find('J') != position.end()) {
                        position.insert({key[i],position['J']});
                    }
                    else if (position.find(key[i]) == position.end()) {
                        matrix[index_row][index_col] = key[i];
                        position.insert({key[i],{index_row, index_col++}});
                    }
                }
                else if (key[i] == 'J') {
                    if (position.find(key[i]) == position.end() && position.find('I') != position.end()) {
                        position.insert({key[i],position['I']});
                    }
                    else if (position.find(key[i]) == position.end()) {
                        matrix[index_row][index_col] = key[i];
                        position.insert({key[i],{index_row, index_col++}});
                    }
                }
                else if (position.find(key[i]) == position.end()) {
                    matrix[index_row][index_col] = key[i];
                    position.insert({key[i],{index_row, index_col++}});
                }
                if (index_col >= 5) {
                    index_row++;
                    index_col -= 5;
                }
            }
            if (index_row < 5) {
                for (char ch = 'A'; ch <= 'Z'; ++ch) {
                    if (ch == 'I') {
                        if (position.find(ch) == position.end() && position.find('J') != position.end()) {
                            position.insert({ch,position['J']});
                        }
                        else if (position.find(ch) == position.end()) {
                            matrix[index_row][index_col] = ch;
                            position.insert({ch,{index_row, index_col++}});
                        }
                    }
                    else if (ch == 'J') {
                        if (position.find(ch) == position.end() && position.find('I') != position.end()) {
                            position.insert({ch,position['I']});
                        }
                        else if (position.find(ch) == position.end()) {
                            matrix[index_row][index_col] = ch;
                            position.insert({ch,{index_row, index_col++}});
                        }
                    }
                    else if (position.find(ch) == position.end()) {
                        matrix[index_row][index_col] = ch;
                        position.insert({ch,{index_row, index_col++}});
                    }
                    if (index_col >= 5) {
                        index_row++;
                        index_col -= 5;
                    }
                }
            }

            cout<<"La matriz que se utilizara para cifrar es: "<<endl;
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    if (matrix[i][j] == 'I' || matrix[i][j] == 'J') {
                        cout<<"I|J ";
                    }
                    else {
                        cout<<matrix[i][j]<<"   ";
                    }
                }
                cout<<endl;
            }

            string output;
            for (int i = 0; i < plain_text.size(); i += 2) {
                int row1, col1, row2, col2;
                row1 = position[plain_text[i]].first;
                col1 = position[plain_text[i]].second;
                row2 = position[plain_text[i+1]].first;
                col2 = position[plain_text[i+1]].second;
                if (col1 == col2) {
                    output.push_back(matrix[(row1 + 1) % 5][col1]);
                    output.push_back(matrix[(row2 + 1) % 5][col2]);
                }
                else if (row1 == row2) {
                    output.push_back(matrix[row1][(col1 + 1) % 5]);
                    output.push_back(matrix[row2][(col2 + 1) % 5]);
                }
                else {
                    output.push_back(matrix[row1][col2]);
                    output.push_back(matrix[row2][col1]);
                }
            }
            cout<<"Texto cifrado: "<<output<<endl;
        }
        else if (option == 2) {
            int index_row = 0;
            int index_col = 0;
            string encrypted_text;
            string key;
            char matrix[5][5];
            map<char,pair<int,int>> position;

            cout<<"Digite el texto a descifrar: "<<endl;
            cin>>encrypted_text;
            cout<<"Digite la llave a utilizar, de no estar completa se rellenara en orden alfabetico: "<<endl;
            cin>>key;

            for_each(encrypted_text.begin(), encrypted_text.end(), [](char& ch) {ch = toupper(ch);});
            for_each(key.begin(), key.end(), [](char& ch) {ch = toupper(ch);});

            if (encrypted_text.size() % 2 != 0) {
                cout<<"El texto encriptado no es valido, debe tener una longitud par"<<endl;
            }
            else {
                for (int i = 0; i < key.size(); ++i) {
                    if (key[i] == 'I') {
                        if (position.find(key[i]) == position.end() && position.find('J') != position.end()) {
                            position.insert({key[i],position['J']});
                        }
                        else if (position.find(key[i]) == position.end()) {
                            matrix[index_row][index_col] = key[i];
                            position.insert({key[i],{index_row, index_col++}});
                        }
                    }
                    else if (key[i] == 'J') {
                        if (position.find(key[i]) == position.end() && position.find('I') != position.end()) {
                            position.insert({key[i],position['I']});
                        }
                        else if (position.find(key[i]) == position.end()) {
                            matrix[index_row][index_col] = key[i];
                            position.insert({key[i],{index_row, index_col++}});
                        }
                    }
                    else if (position.find(key[i]) == position.end()) {
                        matrix[index_row][index_col] = key[i];
                        position.insert({key[i],{index_row, index_col++}});
                    }
                    if (index_col >= 5) {
                        index_row++;
                        index_col -= 5;
                    }
                }
                if (index_row < 5) {
                    for (char ch = 'A'; ch <= 'Z'; ++ch) {
                        if (ch == 'I') {
                            if (position.find(ch) == position.end() && position.find('J') != position.end()) {
                                position.insert({ch,position['J']});
                            }
                            else if (position.find(ch) == position.end()) {
                                matrix[index_row][index_col] = ch;
                                position.insert({ch,{index_row, index_col++}});
                            }
                        }
                        else if (ch == 'J') {
                            if (position.find(ch) == position.end() && position.find('I') != position.end()) {
                                position.insert({ch,position['I']});
                            }
                            else if (position.find(ch) == position.end()) {
                                matrix[index_row][index_col] = ch;
                                position.insert({ch,{index_row, index_col++}});
                            }
                        }
                        else if (position.find(ch) == position.end()) {
                            matrix[index_row][index_col] = ch;
                            position.insert({ch,{index_row, index_col++}});
                        }
                        if (index_col >= 5) {
                            index_row++;
                            index_col -= 5;
                        }
                    }
                }

                cout<<"La matriz que se utilizara para descifrar es: "<<endl;
                for (int i = 0; i < 5; ++i) {
                    for (int j = 0; j < 5; ++j) {
                        if (matrix[i][j] == 'I' || matrix[i][j] == 'J') {
                            cout<<"I|J ";
                        }
                        else {
                            cout<<matrix[i][j]<<"   ";
                        }
                    }
                    cout<<endl;
                }

                string output;
                for (int i = 0; i < encrypted_text.size(); i += 2) {
                    int row1, col1, row2, col2;
                    row1 = position[encrypted_text[i]].first;
                    col1 = position[encrypted_text[i]].second;
                    row2 = position[encrypted_text[i+1]].first;
                    col2 = position[encrypted_text[i+1]].second;
                    if (col1 == col2) {
                        output.push_back(matrix[(row1 + 4) % 5][col1]);
                        output.push_back(matrix[(row2 + 4) % 5][col2]);
                    }
                    else if (row1 == row2) {
                        output.push_back(matrix[row1][(col1 + 4) % 5]);
                        output.push_back(matrix[row2][(col2 + 4) % 5]);
                    }
                    else {
                        output.push_back(matrix[row1][col2]);
                        output.push_back(matrix[row2][col1]);
                    }
                }
                cout<<"Texto descifrado: "<<output<<endl;
            }
        }
        else if (option == 3) {
            system("cls");
        }
        else break;
    } while (true);
    return 0;
}
