#include "common.h"

enum OP {
    ADD,
    MULTIPLY
};

class Monkey {
public:
    Monkey(OP o, int ov, int tv, int m_1, int m_2) : op(o), op_value(ov), test_value(tv), m1(m_1), m2(m_2) {}
    Monkey() = default;

    list<long long> items;
    OP op;
    long long op_value;
    long long test_value;
    int m1;
    int m2;
};

void task1() {
    ifstream input("input11.txt");
    string line;
    vector<Monkey> monkies;

    while (getline(input, line)) {
        stringstream ss(line);
        string word;
        ss >> word;
        if (word == "Monkey") {
            monkies.push_back(Monkey());
        } else if (word == "Starting") {
            ss >> word;
            int item;
            while (ss >> item) {
                monkies.back().items.push_back(item);
                char c;
                ss >> c;
            }
        } else if (word == "Operation:") {
            ss >> word;
            ss >> word;
            ss >> word;
            ss >> word;
            if (word == "+") {
                monkies.back().op = ADD;
            } else {
                monkies.back().op = MULTIPLY;
            }
            int item;

            if (ss >> item) {
                monkies.back().op_value = item;
            } else {
                monkies.back().op_value = -1;
            }
        } else if (word == "Test:") {
            ss >> word;
            ss >> word;
            int n;
            ss >> n;
            monkies.back().test_value = n;
        } else if (word == "If") {
            ss >> word;
            bool b = false;
            if (word == "true:") {
                b = true;
            }

            ss >> word;
            ss >> word;
            ss >> word;
            int n;
            ss >> n;
            if (b) {
                monkies.back().m1 = n;
            } else {
                monkies.back().m2 = n;
            }
        }
    }

    vector<int> inspections(monkies.size());

    for (int loop = 0; loop < 20; loop++) {
        for (int i = 0; i < monkies.size(); i++) {
            while (monkies[i].items.size() > 0)
            {
                Monkey& m = monkies[i];
                int item = m.items.front();
                m.items.pop_front();

                if (m.op == ADD) {
                    item += m.op_value;
                } else {
                    if (m.op_value == -1) {
                        item *= item;
                    } else {
                        item *= m.op_value;
                    }
                }

                item /= 3;
                if (item % m.test_value == 0) {
                    monkies[m.m1].items.push_back(item);
                } else {
                    monkies[m.m2].items.push_back(item);
                }

                inspections[i]++;
            }
            
        }
    }

    int size = inspections.size();
    std::sort(inspections.begin(), inspections.end());
    std::cout << inspections[size-2] * inspections[size-1] << endl;    
}

void task2() {
    ifstream input("input11.txt");
    string line;

    vector<Monkey> monkies;
    while (getline(input, line)) {
        stringstream ss(line);
        string word;
        ss >> word;
        if (word == "Monkey") {
            monkies.push_back(Monkey());
        } else if (word == "Starting") {
            ss >> word;
            int item;
            while (ss >> item) {
                monkies.back().items.push_back(item);
                char c;
                ss >> c;
            }
        } else if (word == "Operation:") {
            ss >> word;
            ss >> word;
            ss >> word;
            ss >> word;
            if (word == "+") {
                monkies.back().op = ADD;
            } else {
                monkies.back().op = MULTIPLY;
            }
            int item;

            if (ss >> item) {
                monkies.back().op_value = item;
            } else {
                monkies.back().op_value = -1;
            }
        } else if (word == "Test:") {
            ss >> word;
            ss >> word;
            int n;
            ss >> n;
            monkies.back().test_value = n;
        } else if (word == "If") {
            ss >> word;
            bool b = false;
            if (word == "true:") {
                b = true;
            }

            ss >> word;
            ss >> word;
            ss >> word;
            int n;
            ss >> n;
            if (b) {
                monkies.back().m1 = n;
            } else {
                monkies.back().m2 = n;
            }
        }
    }

    vector<long long> inspections(monkies.size());
    unsigned long long mod = 1;
    for (auto& m : monkies) {
        mod *= m.test_value;
    }

    for (int loop = 0; loop < 10000; loop++) {
        for (int i = 0; i < monkies.size(); i++) {
            while (monkies[i].items.size() > 0)
            {
                Monkey& m = monkies[i];
                unsigned long long item = m.items.front();
                m.items.pop_front();

                if (m.op == ADD) {
                    item += m.op_value;
                } else {
                    if (m.op_value == -1) {
                        item *= item;
                    } else {
                        item *= m.op_value;
                    }
                }

                item %= mod;
                if (item % m.test_value == 0) {
                    monkies[m.m1].items.push_back(item);
                } else {
                    monkies[m.m2].items.push_back(item);
                }

                inspections[i]++;
            }
            
        }
    }

    int size = inspections.size();
    std::sort(inspections.begin(), inspections.end());
    std::cout << inspections[size-2] * inspections[size-1] << endl;
}

int main() {
    task1();
    task2();
}