#include <iostream>
#include <cmath>

using namespace std;

// класс больших чисел, где каждый разряд есть элемент массива
class big_num {
private:
    int* number;
    bool sign;

public:
    big_num() {
        sign = true; // true значит число положительное,false - число отприцательное
        number = new int[1000];
        for(int i=0; i<1000; i++) {
            number[i] = 0;
        }
    }

    bool get_sign() {
        return sign;
    }

    void set_sign(bool key) {
        sign = key;
    }

    // перегружаем сумму столбиком
    big_num operator+(const big_num& rhs) {
        int j = 0;                      // чтобы не выполнять операции со всеми 1000-ю
        while((number[1000-j-1] == 0) && (rhs.number[1000-j-1] == 0)) { // массива
            j++;
        }
        j = 1000 - j;

        for(int i=0; i<j; i++)  {
            number[i] = number[i] + rhs.number[i];
            if(this->number[i]>=10) {
                this->number[i]-=10;
                this->number[i+1]++;
            }
        }
        return *this;
    }

    // перегружаем разность столбиком
    big_num operator-(const big_num& rhs) {
        int j = 0, k = 1; // чтобы не выполнять операции со всеми 1000-ю элементами
        while((number[1000-j-1] == 0) && (rhs.number[1000-j-1] == 0)) { // массива
            j++;
        }
        j = 1000 - j;

        for(int i=0; i<j; i++)  {
            if((this->number[i]>=rhs.number[i])) {
                this->number[i] = this->number[i] - rhs.number[i];
            }
            else {
                while((this->number[i+k] == 0) && ((i+k)<j)) {
                    this->number[i+k]=9;
                    k++;
                }
                if(k) {
                    number[i+k]--;
                    number[i]+=10;
                    this->number[i] = this->number[i] - rhs.number[i];
                }
                else
                    this->number[i] = this->number[i] - rhs.number[i];
                if(this->number[i]<0) {
                    number[i] = number[i]*(-1);
                    sign = false;
                }
            }
        }
        return *this;
    }

    // перегружаем оператор <
    bool operator <(big_num& rhs) {
        for(int i=0; i<1000; i++) {
            if(this->number[1000-i-1]>rhs.number[1000-i-1]) {
                return false;
            }
            else if(this->number[1000-i-1]<rhs.number[1000-i-1]) {
                return true;
            }
            else
                continue;
        }
    }

    // перегружаем оператор >
    bool operator >(big_num& rhs) {
        for(int i=0; i<1000; i++) {
            if(this->number[1000-i-1]<rhs.number[1000-i-1]) {
                return false;
            }
            else if(this->number[1000-i-1]>rhs.number[1000-i-1]) {
                return true;
            }
            else
                continue;
        }
    }

    // перегружаем оператор =
    big_num operator=(const big_num& rhs) {
        int j = 1;                      // чтобы не выполнять операции со всеми 1000-ю
        while(rhs.number[1000-j] == 0) {    // элементами массива
            j++;
        }
        j = 1001 - j;
        for(int i=0; i<j; i++) {
            this->number[i] = rhs.number[i];
        }
        this->sign = rhs.sign;
        return *this;
    }

    // печатаем наше большое число
    bool print() {
        int i = 0;
        while(number[1000-i-1] == 0 && i<1000) {
            i++;
        }
        i = 1000 - i;
        if(i == 0) {
            cout << 0 << endl;
            return false;
        }


        if(!this->sign)
            cout << "-";
        for(int j=0; j<i; j++) {
            cout << number[i - j - 1];
        }
        cout << endl;
    }

    // переносим данные из введенной строки в наше большое число
    friend void equal(big_num& num, string& str) {
        short int len = str.length();
        short int temp = 0;
        for(int i=0; i<len; i++) {
            temp = int(str[len - i - 1]) - 48;
            num.number[i] = temp;
        }
    }
};


int main()
{
    big_num a, b, c;
    bool s_a = true, s_b = true;
    string one;// = "2";
    cin >> one;
    if(one[0] == '-') {   // проверка на отрицательность
        one.erase(0, 1);
        a.set_sign(false);
        s_a = false;
    }
    equal(a, one);

    char op;// = '-';
    cin >> op;

    string two;// = "10";
    cin >> two;
    if(two[0] == '-') {    // проверка на отрицательность
        two.erase(0, 1);
        b.set_sign(false);
        s_b = false;
    }

    equal(b, two);

    if((s_a == false) && (s_b == false)) {
        switch(op) {
            case '+':
                c.set_sign(false);
                c = a+b;
                c.print();
                break;
            case '-':
                if(a<b) {
                    c = b-a;
                    c.set_sign(true);
                    c.print();
                }
                else {
                    c = a-b;
                    c.set_sign(false);
                    c.print();
                }
                break;
        }
    }
    else if((s_a == false) && (s_b == true)) {
        switch(op) {
            case '+':
                if(a<b) {
                    c = b-a;
                    c.print();
                }
                else {
                    c = a-b;
                    c.set_sign(false);
                    c.print();
                }
                break;
            case '-':
                c = a+b;
                c.set_sign(false);
                c.print();
                break;
        }
    }
    else if((s_a == true) && (s_b == false)) {
        switch(op) {
            case '+':
            if(a<b) {
                c.set_sign(false);
                c = b-a;
                c.print();
            }
            else {
                c = a-b;
                c.print();
            }
            break;
            case '-':
                c = a+b;
                c.print();
                break;
        }
    }
    else {
        switch(op) {
            case '+':
                c = a+b;
                c.print();
                break;
            case '-':
                if(a<b) {
                    c = b-a;
                    c.set_sign(false);
                    c.print();
                }
                else {
                    c = a-b;
                    c.print();
                }
                break;
        }
    }
}

