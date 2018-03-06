#include <iostream>
#include <typeinfo>

using namespace std;

class Stack {
public:
    Stack(int max = 1000) : n(max) {
        size = 0;
        stack = new char [n];
        for(int i=0; i<n; i++) {
            stack[i] = '0';
        }
    }

    ~Stack() { }

    bool push(char key) {
        if((size + 1) < (n - 1)) {
            stack[size + 1] = key;
            size++;
            return true;
        }
        else {
            return false;
        }
    }

    char top() {
        return stack[size];
    }

    char pop() {
        char temp = stack[size];
        stack[size] = '0';
        size--;
        return temp;
    }

    bool empty() {
        if(size == 0) {
            return true;
        }
        else {
            return false;
        }
    }

private:
    int n;
    char* stack; //= new char [n];
    int size;
};

int main()
{
    string input;
    cin >> input;
    Stack a(1000);
    int len = input.length();
    if(len%2 != 0) {
        cout << "NO" << endl;
        return false;
    }
    a.push(input[0]);
    for(int i = 1; i<len; i++) {
        if(a.empty()) {
            a.push(input[i]);
            continue;
        }
        if((a.top() == input[i])) {
            a.push(input[i]);
        }
        else {
            a.pop();

        }
    }

    if(a.empty()) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
}
