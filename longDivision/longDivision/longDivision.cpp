#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

// get degree of polynomial
int getDegree(unsigned int x) {
    int degree = -1;
    while (x) {
        x >>= 1; //shift right 1
        degree++;
    }
    return degree;
}

// XOR-based long division
unsigned int divide(unsigned int dividend, unsigned int divisor) {
    int degDividend = getDegree(dividend);
    int degDivisor = getDegree(divisor);

    while (degDividend >= degDivisor) {
        unsigned int shift = degDividend - degDivisor;
        dividend ^= (divisor << shift); // dividend XOR shift divisor
        degDividend = getDegree(dividend);
    }

    return dividend; // remainder
}

// start making identity matrix
vector<vector<int>> identityMatrix(int k) {

    vector<vector<int>> I(k, vector<int>(k, 0));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (i == j)
                I[i][j] = 1;
        }
    }
    return I;
}

// Starts making H^T
vector<vector<int>> hTranspose(int n, int k) {

    int p = n - k; 
    vector<vector<int>> HT(n, vector<int>(p, 0)); //n by p

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            if (i >= k && i <= n - 1)
                HT[i][i - k] = 1;
        }
    }
    return HT;
}

//encode message
void encode(vector<int> U, vector<vector<int>> G) {

    cout << "\n______________V______________\n";

    for (int i = 0; i < G[0].size(); i++) {
        int sum = 0;
        for (int j = 0; j < U.size(); j++) {
            sum ^= U[j] * G[j][i];
        }
        cout << sum << " ";
    }
}

//decode message
void decode(vector<int> R, vector<vector<int>> HT) {
    
    cout << "\n___S___\n";

    for (int i = 0; i < HT[0].size(); i++) {
        int sum = 0;
        for (int j = 0; j < R.size(); j++) {
            sum ^= R[j] * HT[j][i];
        }
        cout << sum << " ";
    }
}

int main() {
    
    // add or adjust values depending on what is needed
    int n = 15;
    int k = 11;
    unsigned int dividend = 0b10000;
    unsigned int divisor = 0b10011;

    vector<vector<int>> G = identityMatrix(k);

    vector<vector<int>> H = hTranspose(n, k);

    vector<int> U1 = { 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1 };

    vector<int> R1 = { 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1 };

    // create matrices based on long division
    for (int i = 0; i < k; i++) {
        unsigned int remainder = divide(dividend, divisor);

        bitset<4> binaryRemainder = bitset<4>(remainder);

        for (int j = 0; j < binaryRemainder.size(); j++) {
            G[i].push_back(binaryRemainder[j]);
        }

        for (int m = 0; m < binaryRemainder.size(); m++) {
            if (m == 0)
                H[i].clear();
            H[i].push_back(binaryRemainder[m]);
        }
        

        dividend <<= 1;
    }

    cout << "_____________G_______________\n";

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            cout << G[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\n______________H______________\n";

    for (int i = 0; i < n - k; i++) {
        for (int j = 0; j < n; j++) {
            cout << H[j][i] << " ";
        }
        cout << endl;
    }

    encode(U1, G);

    cout << endl;

    decode(R1, H);

    return 0;
}
