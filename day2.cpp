#include "common.h"

void task1() {
    ifstream input("input2.txt");
    int sum = 0;
    char opponent, me;

    while (input >> opponent) {
        input >> me;
        me -= 'X';
        opponent -= 'A';
        sum += me + 1;

        if (opponent == me) {
            sum += 3;
        } else if (((me + 1) % 3) != opponent) {
            sum += 6;
        }
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input2.txt");
    int sum = 0;
    char opponent, me;

    while (input >> opponent) {
        input >> me;
        
        opponent -= 'A';
        me -= 'X';
        switch (me) {
            case 0:
                me = opponent + 2;
                break;
            case 1:
                me = opponent;
                break;
            case 2:
                me = opponent + 1;          
        }
        me = me % 3;
        sum += me + 1;

        if (opponent == me) {
            sum += 3;
        } else if (((me + 1) % 3) != opponent) {
            sum += 6;
        }
    }

    cout << sum << endl;
}

int main() {
    task1();
    task2();
}