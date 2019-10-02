#include <cmath>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Formula {
    int x;
    int y;
    string exp;
    vector<pair<int,int>> cells;
    
    Formula(string exp, int x, int y)
    : exp{exp}, x{x}, y{y} {
        string str = "";
        for (int i = 1; i < exp.size(); ++i) {
            if (exp[i] == '+') {
                dCell(str);
                str = "";
            } else
                str += exp[i];
        }
    }
    void dCell(string str) {
        vector<int> col_num;
        string s_row = "";
        int row, col = -1;
        for (int i = 0; i < str.size(); ++i) {
            if ((int)str[i] > 64)
                col_num.push_back((int)str[i]-64);
            else
                s_row += str[i];
        }
        int n = col_num.size();
        for (int i = 0; i < n; ++i)
            col += col_num[i]*(pow(26,n-i-1));
        cells.push_back(make_pair(stoi(s_row)-1,col));
    }
    void execute(int** matrix) {
        int result = 0;
        for (int i = 0; i < cells.size(); ++i)
            result += matrix[cells[i].first][cells[i].second];
        matrix[x][y] = result;
    }
};

int main(int argc, char const *argv[]){
    int hojas = 0;
    cin >> hojas;

    for (int i = 0; i < hojas; ++i) {
        vector<Formula*> formulas;
        int cols = 0, rows = 0;
        cin >> cols >> rows;
        int **hoja = new int*[rows];
        bool **check = new bool*[rows];

        for (int j = 0; j < rows; ++j) {
            hoja[j] = new int[cols];
            check[j] = new bool[cols];
            for (int k = 0; k < cols; ++k) {
                string value;
                cin >> value;
                if (value[0] == '=') {
                    value += '+';
                    Formula* func = new Formula(value,j,k);
                    formulas.push_back(func);
                    check[j][k] = 1;
                } else {
                    hoja[j][k] = stoi(value);
                    check[j][k] = 0;
                }
            }
        }
        while (formulas.size() > 0) {
            for (int i = 0; i < formulas.size(); ++i) {
                bool indep = true;
                for (auto c : formulas[i]->cells)
                    if (check[c.first][c.second]) {
                        indep = false;
                        break;
                    } 
                if (indep) {
                    formulas[i]->execute(hoja);
                    check[formulas[i]->x][formulas[i]->y] = 0;
                    formulas.erase(formulas.begin() + i);
                }
            }
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols-1; ++j)
                cout << hoja[i][j] << " ";
            cout << hoja[i][cols-1] << endl;
        }
    }
    
    return 0;
}
