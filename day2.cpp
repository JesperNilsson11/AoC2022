#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    ifstream input("input2.txt");
    //ifstream input("example.txt");
    int sum = 0;
    char opponent, me;

    /*while (input >> opponent) {
        input >> me;
        //cout << opponent << " " << me;
        me -= 'X';
        opponent -= 'A';
        sum += me + 1;
        //cout << " + " << me+1;

        if (opponent == me) {
            sum += 3;
            //cout << " draw +3 " << endl;
        } else if (((me + 1) % 3) != opponent) {
            sum += 6;
            //cout << " " << ((me + 1) % 3) << " win +6 " << endl;
        } else {
            //cout << endl;
        }
    }*/

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
        //cout << " + " << me+1;

        if (opponent == me) {
            sum += 3;
            //cout << " draw +3 " << endl;
        } else if (((me + 1) % 3) != opponent) {
            sum += 6;
            //cout << " " << ((me + 1) % 3) << " win +6 " << endl;
        } else {
            //cout << endl;
        }
    }

    cout << sum << endl;
}