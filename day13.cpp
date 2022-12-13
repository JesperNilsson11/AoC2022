#include "common.h"

class Item {
public:
    Item() = default;
    virtual ~Item() = default;

    virtual bool isList() = 0;
};

class Num : public Item {
public:
    Num(int i) : num(i) {}

    bool isList() { return false; }

    int num = 0;
};

class List : public Item {
public:
    List() = default;

    bool isList() { return true; }

    vector<Item*> items;
};

struct Packet {
    vector<Packet> packets;
    vector<int> numbers;
};

Item* read(stringstream& ss) {
    Item* i = nullptr;
    char c;

    c = ss.peek();

    if (c == '[') {
        ss >> c;
        List* l = new List();

        while (ss.peek() != ']') {
            l->items.push_back(read(ss));
            if (ss.peek() == ',')
                ss >> c;
        }
        ss >> c;

        return l;
    } else if (c >= '0' && c <= '9') {
        int num;
        ss >> num;

        return new Num(num);
    } 
}

void print(Item* i) {
    if (i->isList()) {
        cout << "[";
        List* l = dynamic_cast<List*>(i);
        for (int i = 0; i < l->items.size(); i++) {
            print(l->items[i]);
        }
        cout << "]";
    } else {
        Num* n = dynamic_cast<Num*>(i);
        cout << n->num << ",";
    }
}

int correct(Item* p1, Item* p2) {
    if (!p1->isList() && !p2->isList()) {
        Num* n1 = dynamic_cast<Num*>(p1);
        Num* n2 = dynamic_cast<Num*>(p2);

        if (n1->num == n2->num) {
            return 0;
        } else if (n1->num < n2->num) {
            return 1;
        } else {
            return -1;
        }
    }

    List* l1 = dynamic_cast<List*>(p1);
    List* l2 = dynamic_cast<List*>(p2);
    if (!p1->isList()) {
        l1 = new List();
        l1->items.push_back(p1);
    }

    if (!p2->isList()) {
        l2 = new List();
        l2->items.push_back(p2);
    }

    int size = min(l1->items.size(), l2->items.size());
    for (int i = 0; i < size; i++) {
        int r = correct(l1->items[i], l2->items[i]);

        if (r != 0)
            return r;
    }

    if (l1->items.size() < l2->items.size()) {
        return 1;
    } else if (l1->items.size() > l2->items.size()) {
        return -1;
    }
    

    return 0;
}

void task1() {
    ifstream input("input13.txt");
    string line;
    string line2;
    int sum = 0;
    int index = 1;

    while (getline(input, line)) {
        Packet head;
        getline(input, line2);
        stringstream ss(line);
       Item* p1 = read(ss);
       stringstream s2(line2);
       Item* p2 = read(s2);

       if (correct(p1, p2) == 1) {
        sum += index;
       }

        index++;
       getline(input, line);
    }

    cout << sum << endl;
}

void task2() {
    ifstream input("input13.txt");
    string line;
    string line2;
    vector<Item*> packets;
    List* d = new List();
    d->items.push_back(new Num(2));
    List* d2 = new List();
    d2->items.push_back(d);

    d = new List();
    d->items.push_back(new Num(6));
    List* d6 = new List();
    d6->items.push_back(d);

    packets.push_back(d2);
    packets.push_back(d6);
    

    while (getline(input, line)) {
        Packet head;
        getline(input, line2);
        stringstream ss(line);
       Item* p1 = read(ss);
       packets.push_back(p1);
       stringstream s2(line2);
       Item* p2 = read(s2);
       packets.push_back(p2);

       getline(input, line);
    }

    sort(packets.begin(), packets.end(), [](Item* p1, Item* p2) -> bool
    {
        if (correct(p1, p2) == -1) {
            return false;
        }
        return true;
    });

    int key = 1;
    for (int i = 0; i < packets.size(); i++) {
        if (d2 == packets[i]) {
            key *= (i+1);
        }
        if (d6 == packets[i]) {
            key *= (i+1);
        }
    }

    cout << key << endl;
}

int main() {
    task1();
    task2();
}