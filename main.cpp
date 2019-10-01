#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Formula {
    int x;
    int y;
    string exp;
    map<int,int> cels;
    
    Formula(string exp, int x, int y)
    : exp{exp}, x{x}, y{y} {
        string str = "";
        for (int i = 1; i < exp.size(); ++i) {
            if (exp[i] == '+') {
                dCell(str);
                str = "";
            } else str += exp[i];
        } dCell(str);
    }
    void dCell(string str) {
        vector<int> col_num;
        string s_row = "";
        int row, col = -1;
        for (int i = 0; i < str.size(); ++i) {
            if ((int)str[i] > 64)
                col_num.push_back((int)str[i]-64);
            else  s_row += str[i];
        } int n = col_num.size();
        for (int i = 0; i < n; ++i)
            col += col_num[i]*(pow(26,n-i-1));
        row = stoi(s_row)-1;
        cels[row] = col;
        cout << row << " " <<  cels[row] << endl;
    }

    void celdas() {
        for (auto i = cels.begin(); i != cels.end(); ++i)
            cout << i->first << " " << i->second << endl;
        cout << endl;
    }
};

vector<Formula*> formulas;

int main(int argc, char const *argv[]){
    int hojas = 0;
    cin >> hojas;
    for (int i = 0; i < hojas; ++i) {
        int cols = 0, rows = 0;
        cin >> rows >> cols;
        int **hoja = new int*[rows];
        for (int j = 0; j < rows; ++j) {
            hoja[j] = new int[cols];
            for (int k = 0; k < cols; ++k) {
                string value;
                cin >> value;
                if (value[0] == '=') {
                    Formula* func = new Formula(value,j,k);
                    formulas.push_back(func);
                } else 
                    hoja[j][k] = stoi(value);
            }
        }
        /*for (auto x : formulas)
            x->celdas();*/
        /*
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                cout << hoja[i][j] << " ";
            cout << endl;
        }*/
    }
    
    return 0;
}
