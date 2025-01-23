#include <bits/stdc++.h>
using namespace std;

int maxHoles(int);
pair<int,int> rotateClockwise(pair<int,int>);
pair<int,int> rotateCounterClockwise(pair<int,int>);
bool initialPosition(pair<int,int>, int);
bool validPositions(vector<pair<int,int>>);
pair<int,int> convertPosition(pair<int,int>, int);
pair<int,int> inverseConvertPosition(pair<int,int>, int);

int maxHoles(int n) {
    return n % 2 == 0 ? n * n / 4 : (n * n + 3) / 4;
}

pair<int,int> rotateClockwise(pair<int,int> p) {
    return {p.second, -p.first};
}

pair<int,int> rotateCounterClockwise(pair<int,int> p) {
    return {-p.second, p.first};
}

bool initialPosition(pair<int,int> p, int n) {
    if (p == make_pair(0,0)) return true;
    return p.second > 0 && p.first != n;
}

bool validPositions(vector<pair<int,int>> pos) {
    set<pair<int,int>> occupied;
    for (int i = 0; i < pos.size(); ++i) {
        while (!initialPosition(pos[i], max(abs(pos[i].first), abs(pos[i].second)))) {
            pos[i] = rotateCounterClockwise(pos[i]);
        }
        if (pos[i] != make_pair(0,0) && occupied.find(pos[i]) != occupied.end()) return false;
        occupied.insert(pos[i]);
    }
    return true;
}

pair<int,int> convertPosition(pair<int,int> p, int n) {
    if (n % 2) return {p.second - (n + 1) / 2, -p.first + (n + 1) / 2};
    return {p.second <= n/2 ? p.second - n/2 - 1 : p.second - n/2, p.first >= n/2 ? -p.first + n/2 : -p.first + n/2 + 1};
}

pair<int,int> inverseConvertPosition(pair<int,int> p, int n) {
    if (n % 2) return {-p.second + (n + 1) / 2, p.first + (n + 1) / 2};
    return {p.second < 0 ? -p.second + n/2 : -p.second + n/2 + 1, p.first < 0 ? p.first + n/2 + 1 : p.first + n/2};
}


int main() {
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
            int sz;
            int direction;
            int num_positions;
            vector<pair<int,int>> positions;
            string plain_text;

            cout<<"Digite la cantidad de filas de la matriz: "<<endl;
            cin>>sz;

            cout<<"Digite la direccion hacia la cual rota la matriz para cifrar (0 sentido de las manecillas del reloj y 1 sentido contrario): "<<endl;
            cin>>direction;

            while(direction != 0 && direction != 1) {
                cout<<"Digite la direccion hacia la cual rota la matriz para cifrar (0 sentido de las manecillas del reloj y 1 sentido contrario): "<<endl;
                cin>>direction;
            }

            cout<<"Digite la cantidad de huecos que tendra la matriz: "<<endl;
            cin>>num_positions;

            while(num_positions > maxHoles(sz)) {
                cout<<"El numero maximo de huecos para que sea valida la matriz es "<<maxHoles(sz)<<endl;
                cout<<"Digite la cantidad de huecos que tendra la matriz: "<<endl;
                cin>>num_positions;
            }

            positions = vector<pair<int,int>>(num_positions);

            cout<<"Digite las posiciones donde hay huecos, primero la fila, luego la columna y presione enter (la primera celda es 1 1): "<<endl;
            for (int i = 0; i < num_positions; ++i) {
                cin>>positions[i].first>>positions[i].second;
                positions[i] = convertPosition(positions[i], sz);
            }

            while (!validPositions(positions)) {
                cout<<"Las posiciones no son validas porque hay solapamiento, digite otras!"<<endl;
                cout<<"Digite las posiciones donde hay huecos, primero la fila, luego la columna y presione enter (la primera celda es 1 1): "<<endl;
                for (int i = 0; i < num_positions; ++i) {
                    cin>>positions[i].first>>positions[i].second;
                    positions[i] = convertPosition(positions[i], sz);
                }
            }

            cout<<"Digite el texto a cifrar: "<<endl;
            cin.ignore();
            getline(cin, plain_text);

            int s = plain_text.size();
            int c = count(plain_text.begin(), plain_text.end(), ' ');
            remove(plain_text.begin(), plain_text.end(), ' ');
            plain_text.resize(s - c);


            plain_text += string(((4 * num_positions) - plain_text.size() % (4 * num_positions))%(4 * num_positions), 'X');

            for_each(plain_text.begin(), plain_text.end(), [](char& ch) {ch = toupper(ch);});

            string output;
            for (int k = 0; k < plain_text.size(); k += 4 * num_positions) {
                int idx = 0;
                string text_block = plain_text.substr(k, 4 * num_positions);
                vector<vector<char>> text_matrix(sz, vector<char>(sz,'X'));
                for (int i = 0; i < 4; ++i) {
                    sort(positions.begin(), positions.end(), [&](pair<int,int> x, pair<int,int> y) {
                        return x.second > y.second ? true : x.second == y.second ? x.first < y.first : false;
                    });
                    for (int j = 0; j < positions.size(); ++j) {
                        pair<int,int> grille_position = inverseConvertPosition(positions[j], sz);
                        text_matrix[grille_position.first - 1][grille_position.second - 1] = text_block[idx++];
                        if (direction) positions[j] = rotateCounterClockwise(positions[j]);
                        else positions[j] = rotateClockwise(positions[j]);
                    }
                }
                for (int i = 0; i < sz; ++i) {
                    for (int j = 0; j < sz; ++j) {
                        output += text_matrix[i][j];
                    }
                    output += " ";
                }
            }
            cout<<output<<endl;
        }
        else if (option == 2) {
            int sz;
            int direction;
            int num_positions;
            vector<pair<int,int>> positions;
            string plain_text;

            cout<<"Digite la cantidad de filas de la matriz: "<<endl;
            cin>>sz;

            cout<<"Digite la direccion hacia la cual rota la matriz para cifrar, para descifrar se usara claramente la direccion contraria (0 sentido de las manecillas del reloj y 1 sentido contrario): "<<endl;
            cin>>direction;

            while(direction != 0 && direction != 1) {
                cout<<"Digite la direccion hacia la cual rota la matriz para cifrar, para descifrar se usara claramente la direccion contraria (0 sentido de las manecillas del reloj y 1 sentido contrario): "<<endl;
                cin>>direction;
            }

            cout<<"Digite la cantidad de huecos que tendra la matriz: "<<endl;
            cin>>num_positions;

            while(num_positions > maxHoles(sz)) {
                cout<<"El numero maximo de huecos para que sea valida la matriz es "<<maxHoles(sz)<<endl;
                cout<<"Digite la cantidad de huecos que tendra la matriz: "<<endl;
                cin>>num_positions;
            }

            positions = vector<pair<int,int>>(num_positions);

            cout<<"Digite las posiciones donde hay huecos, primero la fila, luego la columna y presione enter (la primera celda es 1 1): "<<endl;
            for (int i = 0; i < num_positions; ++i) {
                cin>>positions[i].first>>positions[i].second;
                positions[i] = convertPosition(positions[i], sz);
            }

            while (!validPositions(positions)) {
                cout<<"Las posiciones no son validas porque hay solapamiento, digite otras!"<<endl;
                cout<<"Digite las posiciones donde hay huecos, primero la fila, luego la columna y presione enter (la primera celda es 1 1): "<<endl;
                for (int i = 0; i < num_positions; ++i) {
                    cin>>positions[i].first>>positions[i].second;
                    positions[i] = convertPosition(positions[i], sz);
                }
            }

            // Preparing for decoding, matrix to the right position
            if (direction) {
                for (int i = 0; i < num_positions; ++i) {
                    positions[i] = rotateClockwise(positions[i]);
                }
            }
            else {
                for (int i = 0; i < num_positions; ++i) {
                    positions[i] = rotateCounterClockwise(positions[i]);
                }
            }

            cout<<"Digite el texto a descifrar: "<<endl;
            cin.ignore();
            getline(cin, plain_text);

            int s = plain_text.size();
            int c = count(plain_text.begin(), plain_text.end(), ' ');
            remove(plain_text.begin(), plain_text.end(), ' ');
            plain_text.resize(s - c);


            plain_text += string(((sz * sz) - plain_text.size() % (sz * sz))%(sz * sz), 'X');

            for_each(plain_text.begin(), plain_text.end(), [](char& ch) {ch = toupper(ch);});

            string output;
            for (int k = 0; k < plain_text.size(); k += sz * sz) {
                int idx = 0;
                string text_block = plain_text.substr(k, sz * sz);
                vector<vector<char>> text_matrix(sz, vector<char>(sz));
                for (int i = 0; i < sz; ++i) {
                    for (int j = 0; j < sz; ++j) {
                        text_matrix[i][j] = text_block[sz * i + j];
                    }
                }

                for (int i = 0; i < 4; ++i) {
                    sort(positions.begin(), positions.end(), [&](pair<int,int> x, pair<int,int> y) {
                        return !(x.second > y.second ? true : x.second == y.second ? x.first < y.first : false);
                    });
                    for (int j = 0; j < positions.size(); ++j) {
                        pair<int,int> grille_position = inverseConvertPosition(positions[j], sz);
                        output += text_matrix[grille_position.first - 1][grille_position.second - 1];
                        if (direction) positions[j] = rotateClockwise(positions[j]);
                        else positions[j] = rotateCounterClockwise(positions[j]);
                    }
                }
            }
            reverse(output.begin(), output.end());
            cout<<output<<endl;
        }
        else if (option == 3) {
            system("cls");
        }
        else break;
    } while (true);

    return 0;
}
