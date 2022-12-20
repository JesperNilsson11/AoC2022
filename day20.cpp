#include "common.h"

typedef long long ll;

struct Element {
    ll num;
    ll index;
};

void task1() {
    ifstream input("input20.txt");
    int sum = 0;
    int num;
    vector<Element> file;
    int index_0 = 0;

    int i = 0;
    while (input >> num) {
        if (num == 0) {
            index_0 = i;
        }
        file.push_back(Element{num, i});
        i++;
    }

    for (int i = 0; i < file.size(); i++) {
        Element& e = file[i];

        int move = e.num;
        if (move > 0) {
            move = move % (file.size() - 1);

            if (move + e.index >= file.size()) {
                move -= (file.size() - 1);
            }
        } else if (move < 0) {
            move = -(abs(move) % (file.size() - 1));

            if (move + e.index < 0) {
                move += file.size() - 1;
            }
        } else {
            continue;
        }

        int min;
        int max;
        int delta;
        if (move < 0) {
            min = move + e.index;
            max = e.index - 1;
            delta = 1;
        } else {
            min = e.index + 1;
            max = e.index + move;
            delta = -1;
        }

        for (int j = 0; j < file.size(); j++) {
            if (file[j].index >= min && file[j].index <= max) {
                file[j].index += delta;
            }
        }

        e.index += move;
    }

    int index_1000 = (file[index_0].index + 1000) % file.size();
    int index_2000 = (file[index_0].index + 2000) % file.size();
    int index_3000 = (file[index_0].index + 3000) % file.size();

    for (auto& e : file) {
        if (e.index == index_1000) {
            cout << "1000th: " << e.num << endl;
            sum += e.num;
        }

        if (e.index == index_2000) {
            cout << "2000th: " << e.num << endl;
            sum += e.num;
        }

        if (e.index == index_3000) {
            cout << "3000th: " << e.num << endl;
            sum += e.num;
        }
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input20.txt");
    ll sum = 0;
    ll num;
    vector<Element> file;
    ll index_0 = 0;

    ll i = 0;
    while (input >> num) {
        if (num == 0) {
            index_0 = i;
        }
        file.push_back(Element{num * 811589153, i});
        i++;
    }

    for (int mix = 0; mix < 10; mix++) {
        for (ll i = 0; i < file.size(); i++) {
            Element& e = file[i];

            ll move = e.num;
            if (move > 0) {
                move = move % (file.size() - 1);

                if (move + e.index >= file.size()) {
                    move -= (file.size() - 1);
                }
            } else if (move < 0) {
                move = -(abs(move) % (file.size() - 1));

                if (move + e.index < 0) {
                    move += file.size() - 1;
                }
            } else {
                continue;
            }

            ll min;
            ll max;
            ll delta;
            if (move < 0) {
                min = move + e.index;
                max = e.index - 1;
                delta = 1;
            } else {
                min = e.index + 1;
                max = e.index + move;
                delta = -1;
            }

            for (ll j = 0; j < file.size(); j++) {
                if (file[j].index >= min && file[j].index <= max) {
                    file[j].index += delta;
                }
            }

            e.index += move;
        }
    }

    ll index_1000 = (file[index_0].index + 1000) % file.size();
    ll index_2000 = (file[index_0].index + 2000) % file.size();
    ll index_3000 = (file[index_0].index + 3000) % file.size();

    for (auto& e : file) {
        if (e.index == index_1000) {
            cout << "1000th: " << e.num << endl;
            sum += e.num;
        }

        if (e.index == index_2000) {
            cout << "2000th: " << e.num << endl;
            sum += e.num;
        }

        if (e.index == index_3000) {
            cout << "3000th: " << e.num << endl;
            sum += e.num;
        }
    }

    cout << sum << endl;
}

int main() {
    cout << "Task1:" << endl;
    task1();
    cout << "Task2:" << endl;
    task2();
}