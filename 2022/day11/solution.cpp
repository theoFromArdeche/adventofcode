#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>

using namespace std;

class Monkey {
private:
    vector<long long> items;
    function<long long(long long)> operation;  
    int testDivisor, trueMonkey, falseMonkey, commonLCM, part;
    long long itemInspected = 0;

public:
    Monkey(vector<long long> items, function<long long(long long)> op, int divisor, int trueMonkey, int falseMonkey, int commonLCM, int part)
        : items(items), operation(op), testDivisor(divisor), trueMonkey(trueMonkey), falseMonkey(falseMonkey), commonLCM(commonLCM), part(part) {}

    void inspectItems(vector<Monkey>& monkeys) {
        vector<long long> newItems;

        for (long long item:items) {
            long long newItem;
            if (part == 1) newItem = operation(item)/3;
            else newItem = operation(item) % commonLCM;
            if (newItem % testDivisor == 0) {
                monkeys[trueMonkey].receiveItem(newItem);
            } else {
                monkeys[falseMonkey].receiveItem(newItem);
            }
        }
        this->itemInspected += items.size();
        items.clear();
    }

    void receiveItem(long long item) {
        items.push_back(item);
    }

    void printItems() {
        for (long long item:items) {
            cout << item << " ";
        }
        cout << "\n";
    }

    int getItemInspected() {
        return this->itemInspected; 
    }
};


vector<long long> parseItems(const string& line) {
    vector<long long> items;
    stringstream ss(line);
    string temp;
    while (getline(ss, temp, ',')) {
        items.push_back(stoi(temp));
    }
    return items;
}

function<long long(long long)> parseOperation(const string& opStr) {
    if (opStr.find('*') != string::npos) {
        string factorStr = opStr.substr(opStr.find('*') + 2);
        if (factorStr == "old") return [](long long old) {return old * old;};
        
        int factor = stoi(factorStr);
        return [factor](long long old) {return old * factor;};

    } else if (opStr.find('+') != string::npos) {
        string addendStr = opStr.substr(opStr.find('+') + 2);
        if (addendStr == "old") return [](long long old) {return old + old;};
        
        int addend = stoi(addendStr);
        return [addend](long long old) {return old + addend;};
    }
    return [](long long old) {return old;};
}

vector<Monkey> monkeysFromInput(const string& filename, int commonLCM,  int part) {
    ifstream infile(filename);
    string line;
    vector<Monkey> monkeys;

    while (getline(infile, line)) {
        if (line.find("Monkey") == string::npos) continue;

        getline(infile, line);
        line = line.substr(line.find(":") + 2);
        vector<long long> items = parseItems(line);

        getline(infile, line);
        line = line.substr(line.find("= ") + 2);
        function<long long(long long)> operation = parseOperation(line);

        getline(infile, line);
        int divisor = stoi(line.substr(line.find("by ") + 3));

        getline(infile, line);
        int trueMonkey = stoi(line.substr(line.find("monkey ") + 7));

        getline(infile, line);
        int falseMonkey = stoi(line.substr(line.find("monkey ") + 7));

        monkeys.push_back(Monkey(items, operation, divisor, trueMonkey, falseMonkey, commonLCM, part));
    }
    return monkeys;
}


vector<int> getDivisors(const string& filename) {
    ifstream infile(filename);
    string line;
    vector<int> divisors; 

    while (getline(infile, line)) {
        if (line.find("by ") == string::npos) continue;
         
        int divisor = stoi(line.substr(line.find("by ") + 3));
        divisors.push_back(divisor);

    }
    return divisors;
}


long long findSolution(vector<Monkey>& monkeys) {
    long long firstMax=0, secondMax=0;
    for (Monkey& mk:monkeys) {
        int inspectedItem = mk.getItemInspected();
        if (inspectedItem >= firstMax) {secondMax=firstMax; firstMax=inspectedItem;}
        else if (inspectedItem > secondMax) secondMax=inspectedItem;
    }
    return firstMax * secondMax;
}


void simulateRounds(vector<Monkey>& monkeys, int numberOfRounds, bool show) {
    for (int round=1; round<=numberOfRounds; round++) {
        for (Monkey& mk:monkeys) {
            mk.inspectItems(monkeys);
        }  

        if (!show) continue;

        cout << "Round " << round << "\n";
        for (int i=0; i<monkeys.size(); i++) {
            cout << "Monkey " << i << ": ";
            monkeys[i].printItems();
        }
        cout << "\n\n";
    }

}


int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

int calculateLCM(const vector<int>& divisors) {
    int result = divisors[0];
    for (int i = 1; i<divisors.size(); ++i) {
        result = lcm(result, divisors[i]);
    }
    return result;
}




int main() {
    const string filename = "input.txt";
    int commonLCM = calculateLCM(getDivisors(filename));

    vector<Monkey> monkeysPart1 = monkeysFromInput(filename, commonLCM, 1);
    vector<Monkey> monkeysPart2 = monkeysFromInput(filename, commonLCM, 2);

    simulateRounds(monkeysPart1, 20, false);
    simulateRounds(monkeysPart2, 10000, false);

    cout << "Part 1 solution: " << findSolution(monkeysPart1) << "\n";
    cout << "Part 2 solution: " << findSolution(monkeysPart2) << "\n";

    return 0;
}
