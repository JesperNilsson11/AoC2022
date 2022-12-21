#include "common.h"

enum Operator {
    PLUS,
    MINUS,
    DIV,
    MUL
};

struct Element {
    string name;

    long long value;
    bool has_value;
    string n1;
    string n2;
    Operator op;
};

void task1() {
    ifstream input("input21.txt");
    string line;
    unordered_map<string, Element> elements;

    while (getline(input, line)) {
        stringstream ss(line);
        Element e;
        ss >> e.name;
        e.name = e.name.substr(0, e.name.size() - 1);
        string test;
        ss >> test;
        if (test[0] >= 'a' && test[0] <= 'z') {
            e.n1 = test;
            e.has_value = false;
            ss >> test;
            if (test == "+") {
                e.op = PLUS;
            } else if (test == "-") {
                e.op = MINUS;
            } else if (test == "/") {
                e.op = DIV;
            } else if (test == "*") {
                e.op = MUL;
            } else {
                cout << "Error expected operator" << endl;
            }

            ss >> e.n2;
        } else {
            e.value = atoi(test.c_str());
            e.has_value = true;
        }

        elements[e.name] = e;
    }

    while (elements["root"].has_value == false) {
        for (auto& p : elements) {
            auto& e = p.second;
            if (!e.has_value && elements[e.n1].has_value && elements[e.n2].has_value) {
                long long num1 = elements[e.n1].value;
                long long num2 = elements[e.n2].value;

                switch (e.op) {
                    case PLUS:
                        e.value = num1 + num2;
                        break;
                    case MINUS:
                        e.value = num1 - num2;
                        break;
                    case DIV:
                        e.value = num1 / num2;
                        break;
                    case MUL:
                        e.value = num1 * num2;
                        break;
                    default:
                        cout << "Error unknown operand" << endl;
                }

                e.has_value = true;
            }
        }
    }

    cout << elements["root"].value << endl;
}

void task2() {
    ifstream input("input21.txt");
    string line;
    unordered_map<string, Element> elements;

    while (getline(input, line)) {
        stringstream ss(line);
        Element e;
        ss >> e.name;
        e.name = e.name.substr(0, e.name.size() - 1);
        string test;
        ss >> test;
        if (test[0] >= 'a' && test[0] <= 'z') {
            e.n1 = test;
            e.has_value = false;
            ss >> test;
            if (test == "+") {
                e.op = PLUS;
            } else if (test == "-") {
                e.op = MINUS;
            } else if (test == "/") {
                e.op = DIV;
            } else if (test == "*") {
                e.op = MUL;
            } else {
                cout << "Error expected operator" << endl;
            }

            ss >> e.n2;
        } else {
            e.value = atoi(test.c_str());
            e.has_value = true;
        }

        elements[e.name] = e;
    }

    elements["humn"].has_value = false;

    while (elements[elements["root"].n1].has_value == false && elements[elements["root"].n2].has_value == false) {
        for (auto& p : elements) {
            auto& e = p.second;
            if (!e.has_value && elements[e.n1].has_value && elements[e.n2].has_value) {
                long long num1 = elements[e.n1].value;
                long long num2 = elements[e.n2].value;

                switch (e.op) {
                    case PLUS:
                        e.value = num1 + num2;
                        break;
                    case MINUS:
                        e.value = num1 - num2;
                        break;
                    case DIV:
                        e.value = num1 / num2;
                        break;
                    case MUL:
                        e.value = num1 * num2;
                        break;
                    default:
                        cout << "Error unknown operand" << endl;
                }

                e.has_value = true;
            }
        }
    }

    string find;
    if (elements[elements["root"].n1].has_value) {
        elements[elements["root"].n2].value = elements[elements["root"].n1].value;
        elements[elements["root"].n2].has_value = true;
        find = elements["root"].n2;
    } else {
        elements[elements["root"].n1].value = elements[elements["root"].n2].value;
        elements[elements["root"].n1].has_value = true;
        find = elements["root"].n1;
    }

    int i = 0;
    while (i < elements.size()) {
        i++;
        for (auto& p : elements) {
            auto& e = p.second;
            if (!e.has_value && elements[e.n1].has_value && elements[e.n2].has_value) {
                long long num1 = elements[e.n1].value;
                long long num2 = elements[e.n2].value;

                switch (e.op) {
                    case PLUS:
                        e.value = num1 + num2;
                        break;
                    case MINUS:
                        e.value = num1 - num2;
                        break;
                    case DIV:
                        e.value = num1 / num2;
                        break;
                    case MUL:
                        e.value = num1 * num2;
                        break;
                    default:
                        cout << "Error unknown operand" << endl;
                }

                e.has_value = true;
            }
        }
    }

    while (find != "humn") {
        auto& e = elements[find];
        long long num1, num2;

        if (elements[e.n1].has_value) {
            num1 = elements[e.n1].value;
            switch (e.op) {
                case PLUS:
                    num2 = e.value - num1;
                    break;
                case MINUS:
                    num2 = num1 - e.value;
                    break;
                case DIV:
                    num2 = num1 / e.value;
                    break;
                case MUL:
                    num2 = e.value / num1;
                    break;
                default:
                    cout << "Error unknown operand" << endl;
            }

            find = e.n2;
            elements[e.n2].value = num2;
            elements[e.n2].has_value = true;
        } else if (elements[e.n2].has_value) {
            num2 = elements[e.n2].value;
            switch (e.op) {
                case PLUS:
                    num1 = e.value - num2;
                    break;
                case MINUS:
                    num1 = e.value + num2;
                    break;
                case DIV:
                    num1 = e.value * num2;
                    break;
                case MUL:
                    num1 = e.value / num2;
                    break;
                default:
                    cout << "Error unknown operand" << endl;
            }

            find = e.n1;
            elements[e.n1].value = num1;
            elements[e.n1].has_value = true;
        }
    }

    cout << elements["humn"].value << endl;
}

int main() {
    task1();
    task2();
}