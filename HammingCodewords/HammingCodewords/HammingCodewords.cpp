
#include <iostream>
#include <bitset>
using namespace std;

const int k = 11;
const int n = 15;

int G[k][n] = {
		{1,0,0,0,0,0,0,0,0,0,0, 1,1,0,0},
		{0,1,0,0,0,0,0,0,0,0,0, 0,1,1,0},
		{0,0,1,0,0,0,0,0,0,0,0, 0,0,1,1},
		{0,0,0,1,0,0,0,0,0,0,0, 1,1,0,1},
		{0,0,0,0,1,0,0,0,0,0,0, 1,0,1,0},
		{0,0,0,0,0,1,0,0,0,0,0, 0,1,0,1},
		{0,0,0,0,0,0,1,0,0,0,0, 1,1,1,0},
		{0,0,0,0,0,0,0,1,0,0,0, 0,1,1,1},
		{0,0,0,0,0,0,0,0,1,0,0, 1,1,1,1},
		{0,0,0,0,0,0,0,0,0,1,0, 1,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,1, 1,0,0,1}
};

int main()
{
	for (int m = 0; m < (1 << k); m++) {
		bitset<k> message(m);
		bitset<n> codeword;

		for (int j = 0; j < n; j++) {
			int sum = 0;
			for (int i = 0; i < k; i++) {
				sum += message[k - i - 1] * G[i][j];
			}
			codeword[j] = sum % 2;
		}

		cout << "Message: " << message << " => Codeword: ";
		for (int i = 0; i < n; i++) {
			cout << codeword[i];
		}
		cout << "\n";
	}

	return 0;
}

