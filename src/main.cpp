#include <fstream>
#include <vector>
#include <cctype>
using namespace std;

bool Branje_Stevil(vector<int> &vec, const char s[]) {
    ifstream input(s);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        vec.push_back(st);
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void Izpis_Stevil(int* polje, unsigned int velikost) {
    ofstream output("out.txt");

    for (int i = 0; i < velikost; i++)
        output << polje[i] << ' ';
}

int main(int argc, const char* argv[]) {
    vector<int> A;

    if (argc < 3) return 0;
    if (!Branje_Stevil(A, argv[2])) return 0;

    if (argv[1][0] == '0') {
        int min = A[0];
        int max = A[0];

        for (int i = 0; i < A.size(); i++) {
            if (A[i] < min) min = A[i];
            if (A[i] > max) max = A[i];
        }

        for (int i = 0; i < A.size(); i++) {
            A[i] -= min;
        }
        max -= min;
        int size = max + 1;
        int* C = new int[size];
        for (int i = 0; i < size; i++) {
            C[i] = 0;
        }
        for (int i = 0; i < A.size(); i++) {
            C[A[i]] = C[A[i]] + 1;
        }
        for (int i = 1; i < size; i++) {
            C[i] += C[i - 1];
        }
        int* B = new int[A.size()];
        for (int j = A.size() - 1; j > -1; j--) {
            B[C[A[j]] - 1] = A[j];
            C[A[j]]--;
        }
        for (int i = 0; i < A.size(); i++) {
            B[i] += min;
        }
        Izpis_Stevil(B, A.size());
    } else {
        int min = A[0];
        int max = A[0];
        for (int i = 0; i < A.size(); i++) {
            if (A[i] < min) min = A[i];
            if (A[i] > max) max = A[i];
        }

        for (int i = 0; i < A.size(); i++) {
            A[i] -= min;
        }
        max -= min;
        int size = max + 1;
        int* C = new int[size];
        for (int i = 0; i < size; i++) {
            C[i] = 0;
        }

        for (int i = 0; i < A.size(); i++) {
            C[A[i]] = C[A[i]] + 1;
        }

        int* B = new int[A.size()];
        int index = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < C[i]; j++) {
                B[index] = i + min;
                index++;
            }
        }
        Izpis_Stevil(B, A.size());
    }

    return 0;
}