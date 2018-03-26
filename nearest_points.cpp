#include <iostream>
#include <cmath>

using namespace std;

void sort_shell(int  *a, int *index, int n) {
   int h;
   for (h = 1; h <= n / 9; h = 3*h + 1)
      ;
   for ( ; h > 0; h /= 3) {
      for (int i = h; i < n; i++) {
        int j = i;
        int tmp = a[i];
        int indx = index[i];
        while (j >= h && tmp < a[j-h]) {
          a[j] = a[j-h];
          index[j] = index[j-h];
          j -= h;
        }
        a[j] = tmp;
        index[j] = indx;
      }
   }
}

int main()
{
    //srand(time(0));
    //unsigned int f = clock();
    int n = 0, d = 0, d1 = 0, first = 0, last = 0;
    cin >> n;
    //n = 1000000;

    int *ns = new int [n];
    int *index = new int [n];

    for(int i=0; i<n; i++) {
        cin >> ns[i];
        //ns[i] = -1000000000+rand()%2000000000;
        index[i] = i+1;
    }
    /*cout << "Before" << endl;
    for(int i=0; i<n; i++) {
        cout << ns[i] << " ";
    }

    cout << endl;

    for(int i=0; i<n; i++) {
        cout << index[i] << " ";
    }



    cout << endl;
    cout << "After" << endl;

    for(int i=0; i<n; i++) {
        cout << ns[i] << " ";
    }

    cout << endl;

    for(int i=0; i<n; i++) {
        cout << index[i] << " ";
    }*/

    sort_shell(ns, index, n);

    //cout << endl;
    d=abs(ns[0] - ns[1]);
    first = index[0];
    last = index[1];

    for(int i=0; i<n-1; i++) {
        d1=abs(ns[i]-ns[i+1]);
        if(d1<d) {
            d=d1;
            first = index[i];
            last = index[i+1];
        }
    }
    cout << d << endl;
    if(first>last)
        cout << last << " " << first << endl;
    else
        cout << first << " " << last << endl;
    //unsigned int l = clock();
    //double time = 1.0*(l - f)/CLOCKS_PER_SEC;
    //cout << "time is: " << time << endl;
}

