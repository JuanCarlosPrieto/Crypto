#include <bits/stdc++.h>
using namespace std;

class Matrix;
int mod(int, int);
int gcd(int, int);
int congruence(int);

class Matrix {
public:
    vector<vector<int>> matrix;

    Matrix() {}
    Matrix(vector<vector<int>> matrix) : matrix(matrix){}

    Matrix operator+(const Matrix other) {
        Matrix result = Matrix(vector<vector<int>>(this->matrix.size(), vector<int>(matrix[0].size())));
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[0].size(); ++j) {
                result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix other) {
        Matrix result = Matrix(vector<vector<int>>(this->matrix.size(), vector<int>(other.matrix[0].size())));
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[0].size(); ++j) {
                for (int k = 0; k < this->matrix[0].size(); ++k) {
                    result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator*(const int num) {
        Matrix result = Matrix(vector<vector<int>>(this->matrix.size(), vector<int>(this->matrix[0].size())));
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[0].size(); ++j) {
                result.matrix[i][j] = this->matrix[i][j] * num;
            }
        }
        return result;
    }

    Matrix minor_mat(int row, int col) {
        int sz = this->matrix.size();
        Matrix result(vector<vector<int>>(sz - 1, vector<int>(sz - 1)));
        int idx_row = 0, idx_col = 0;
        for (int i = 0; i < this->matrix.size(); ++i) {
            for (int j = 0; j < this->matrix[0].size(); ++j) {
                if (i == row || j == col) continue;
                result.matrix[idx_row][idx_col] = this->matrix[i][j];
                ++idx_col;
                if (idx_col >= sz - 1) {
                    idx_col = 0;
                    ++idx_row;
                }
            }
        }
        return result;
    }

    int det() {
        int result = 0;
        if (this->matrix.size() == 1) return this->matrix[0][0];
        vector<Matrix> minors(this->matrix.size());
        for (int i = 0; i < minors.size(); ++i) {
            minors[i] = this->minor_mat(0, i);
        }
        for (int i = 0; i < minors.size(); ++i) {
            result += (i % 2 == 0 ? 1 : -1) * (this->matrix[0][i]) * (minors[i].det());
        }
        return result;
    }

    Matrix adjoint() {
        int sz = this->matrix.size();
        Matrix result = Matrix(vector<vector<int>>(sz, vector<int>(sz)));
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                result.matrix[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * (this->minor_mat(i, j).det());
            }
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const Matrix& matrix);
};

ostream& operator<<(ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.matrix.size(); ++i) {
        for (int j = 0; j < matrix.matrix[0].size(); ++j) {
            os<<matrix.matrix[i][j]<<" ";
        }
        os<<endl;
    }
    return os;
}

int mod(int number,int k) {
    return (number%k + k)%k;
}

int gcd(int a, int b) {
    if (b > a) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

// a x mod 26 = 1
int congruence(int a) {
    for (int i = 0; i < 26; ++i) {
        if (mod(a * i, 26) == 1) return i;
    }
    return -1;
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
            string plain_text;
            Matrix key;
            int t;
            cout<<"Digite el parametro t: "<<endl;
            cin>>t;
            key = Matrix(vector<vector<int>>(t, vector<int>(t)));

            cout<<"Digite la matriz a utilizar: "<<endl;
            for (int i = 0; i < t; ++i) {
                for (int j = 0; j < t; ++j) {
                    cin>>key.matrix[i][j];
                    key.matrix[i][j] = mod(key.matrix[i][j], 26);
                }
            }

            if (gcd(mod(key.det(), 26), 26) == 1) {
                cout<<"Digite el texto a cifrar: "<<endl;
                cin.ignore();
                getline(cin, plain_text);

                int s = plain_text.size();
                int c = count(plain_text.begin(), plain_text.end(), ' ');
                remove(plain_text.begin(), plain_text.end(), ' ');
                plain_text.resize(s - c);

                if (plain_text.size() % t != 0) {
                    plain_text += string(t - plain_text.size() % t, 'X');
                }


                for_each(plain_text.begin(), plain_text.end(), [](char& ch) {ch = toupper(ch);});

                string output;
                for (int i = 0; i < plain_text.size(); i += t) {
                    string block = plain_text.substr(i, t);
                    Matrix block_vector = Matrix(vector<vector<int>>(1, vector<int>(t)));
                    for (int i = 0; i < block.size(); ++i) {
                        block_vector.matrix[0][i] = block[i] - 'A';
                    }
                    Matrix cyphered_block = block_vector * key;
                    for (int i = 0; i < block.size(); ++i) {
                        output += mod(cyphered_block.matrix[0][i],26) + 'A';
                    }
                }
                cout<<output<<endl;
            }
            else {
                cout<<"La matriz no es valida pues no es invertible."<<endl;
            }
        }
        else if (option == 2) {
            string encrypted_text;
            Matrix key;
            int t;
            cout<<"Digite el parametro t: "<<endl;
            cin>>t;
            key = Matrix(vector<vector<int>>(t, vector<int>(t)));

            cout<<"Digite la matriz utilizada para cifrar el texto: "<<endl;
            for (int i = 0; i < t; ++i) {
                for (int j = 0; j < t; ++j) {
                    cin>>key.matrix[i][j];
                    key.matrix[i][j] = mod(key.matrix[i][j], 26);
                }
            }

            Matrix key_dec = (key.adjoint() * congruence(key.det()));

            for (int i = 0; i < t; ++i) {
                for (int j = 0; j < t; ++j) {
                    key_dec.matrix[i][j] = mod(key_dec.matrix[i][j], 26);
                }
            }

            cout<<"La matriz inversa a utilizar es: \n"<<key_dec;

            if (gcd(mod(key.det(), 26), 26) == 1) {
                cout<<"Digite el texto a cifrar: "<<endl;
                cin.ignore();
                getline(cin, encrypted_text);

                int s = encrypted_text.size();
                int c = count(encrypted_text.begin(), encrypted_text.end(), ' ');
                remove(encrypted_text.begin(), encrypted_text.end(), ' ');
                encrypted_text.resize(s - c);

                if (encrypted_text.size() % t != 0) {
                    encrypted_text += string(t - encrypted_text.size() % t, 'X');
                }


                for_each(encrypted_text.begin(), encrypted_text.end(), [](char& ch) {ch = toupper(ch);});

                string output;
                for (int i = 0; i < encrypted_text.size(); i += t) {
                    string block = encrypted_text.substr(i, t);
                    Matrix block_vector = Matrix(vector<vector<int>>(1, vector<int>(t)));
                    for (int i = 0; i < block.size(); ++i) {
                        block_vector.matrix[0][i] = block[i] - 'A';
                    }
                    Matrix cyphered_block = block_vector * key_dec;
                    for (int i = 0; i < block.size(); ++i) {
                        output += mod(cyphered_block.matrix[0][i],26) + 'A';
                    }
                }
                cout<<output<<endl;
            }
            else {
                cout<<"La matriz no es valida pues no es invertible."<<endl;
            }
        }
        else if (option == 3) {
            system("cls");
        }
        else break;
    } while (true);

    return 0;
}
