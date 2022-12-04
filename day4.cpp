#include "common.h"

int main() {
    ifstream input("input4.txt");
    int l1, l2, h1, h2;
    int sumt1 = 0;
    int sumt2 = 0;

    while (input >> l1) {
        char temp;
        input >> temp;
        input >> h1;
        input >> temp;
        input >> l2;
        input >> temp;
        input >> h2;

        if (l1 < l2) {
            if (h1 >= h2) {
                sumt1++;
            }
        } else if (l1 > l2) {
            if (h1 <= h2) {
                sumt1++;
            }
        } else {
            sumt1++;
        }

        if (l1 < l2) {
            if (h1 >= l2) {
                sumt2++;
            }
        } else if (l1 > l2) {
            if (l1 <= h2) {
                sumt2++;
            }
        } else {
            sumt2++;
        }
    }

    cout << sumt1 << endl;
    cout << sumt2 << endl;
}