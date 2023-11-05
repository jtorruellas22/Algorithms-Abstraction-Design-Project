#include <iostream>
using namespace std;
void task2 () {
    int profit = 0;
    int min = 0;
    int max = 0;
    int buy, sell, stock, bought, sold;
    int matrix[4][5] = { {12, 1, 5, 3, 16},
                         {4, 4, 13, 4, 9},
                         {6, 8, 6, 1, 2},
                         {14, 3, 4, 8, 10} };
    for (int m = 0; m < 4; m++) {
        for (int n = 0; n < 5; n++) {
            if (n == 0) {
                min = matrix[m][n];
                buy = n;
            }
            else if (matrix[m][n] < min) {
                min = matrix[m][n];
                buy = n;
                max = 0;
            }
            else if (matrix[m][n] > max) {
                max = matrix[m][n];
                sell = n;
                if(profit < max - min) {
                    profit = max - min;
                    stock = m;
                    bought = buy;
                    sold = sell;
                }
            }
        }
    }
    cout << "(" << stock + 1 << "," << bought + 1 << ","<< sold + 1 << ","<< profit << ")" << endl;
}

int main() {
    task2();
};