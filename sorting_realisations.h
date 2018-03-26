#include <cmath>

// Разные виды сортировок

// Пузырьковая сортировка
// (сортировка обменом)
// Идея: просто меняем элементы местами, если они идут в массиве в неправильном порядке
// время работы | лучший случай | средний случай | худший случай |
//              |      O(N)     |      O(N^2)    |     O(N^2)    |
void bubbleSort(int n, int *arr1, int *arr2)
{
   int temp1 = 0, temp2 = 0;
   for (int i = 0; i < n-1; i++)  {
       for (int j = 0; j < n-i-1; j++) {
           if (arr1[j] > arr1[j+1]) {
              temp1 = arr1[j];
              temp2 = arr2[j];

              arr1[j] = arr1[j+1];
              arr2[j] = arr2[j+1];

              arr1[j+1] = temp1;
              arr2[j+1] = temp2;
           }
       }
   }
}


// Сортировка выбором
// Идея метода состоит в том, чтобы создавать отсортированную последовательность
// путем присоединения к ней одного элемента за другим в правильном порядке.
// Если входная последовательность почти упорядочена, то сравнений будет столько же,
// значит алгоритм ведет себя неестественно.
// Время работы | лучший случай | средний случай | худший случай |
//              |      O(N)     |      O(N^2)    |     O(N^2)    |
void selectSort(int* arr, int size)
{
    int tmp;
    for(int i = 0; i < size; ++i) // i - номер текущего шага
    {
        int pos = i;
        tmp = arr[i];
        for(int j = i + 1; j < size; ++j) // цикл выбора наименьшего элемента
        {
            if (arr[j] < tmp)
           {
               pos = j;
               tmp = arr[j];
           }
        }
        arr[pos] = arr[i];
        arr[i] = tmp; // меняем местами наименьший с a[i]
    }
}



// Сортировка вставками
// Аналогично сортировке выбором, среднее,
// а также худшее число сравнений и пересылок оцениваются как O(n^2),
// дополнительная память при этом не используется.
// Хорошим показателем сортировки является весьма естественное поведение:
// почти отсортированный массив будет досортирован очень быстро.
// Это, вкупе с устойчивостью алгоритма, делает метод хорошим выбором в
// соответствующих ситуациях.
// Алгоритм можно слегка улучшить.
// Заметим, что на каждом шаге внутреннего цикла проверяются 2 условия.
// Можно объединить из в одно, поставив в начало массива специальный
// сторожевой элемент. Он должен быть заведомо меньше всех остальных элементов
// массива.
// Время работы | лучший случай | средний случай | худший случай |
//              |      O(N)     |      O(N^2)    |     O(N^2)    |
void insertSort(int* a, int size)
{
    int tmp;
    for (int i = 1, j; i < size; ++i) // цикл проходов, i - номер прохода
    {
        tmp = a[i];
        for (j = i - 1; j >= 0 && a[j] > tmp; --j) // поиск места элемента в готовой последовательности
            a[j + 1] = a[j];    // сдвигаем элемент направо, пока не дошли
        a[j + 1] = tmp; // место найдено, вставить элемент
    }
}

// Сортировка Шелла
// Время работы | лучший случай | средний случай | худший случай |
//              |   O(N^(7/6))  |    O(N^(7/6))  |   O(N^(4/3))  |
void shellSort(int *a, long size)
{
    long inc, i, j, seq[40];
    int s;

    s = increment(seq, size); // вычисление последовательности приращений
    while (s >= 0)  // сортировка вставками с инкрементами inc[]
    {
         inc = seq[s--];
         for (i = inc; i < size; ++i)
         {
             T temp = a[i];
             for (j = i; (j >= inc) && (temp < a[j-inc]); j -= inc) {
                a[j] = a[j - inc];
             }
             a[j] = temp;
         }
    }
}

// Быстрая сортировка
// Время работы | лучший случай | средний случай | худший случай |
//              |  O(N*log(N))  |   O(N*log(N))  |  O(N*log(N))  |
#define MAXSTACK 2048 // максимальный размер стека
void qSortI(int *a, long size) {

    long i, j; // указатели, участвующие в разделении
    long lb, ub; // границы сортируемого в цикле фрагмента

    long lbstack[MAXSTACK], ubstack[MAXSTACK]; // стек запросов
    // каждый запрос задается парой значений,
    // а именно: левой(lbstack) и правой(ubstack)
    // границами промежутка
    long stackpos = 1; // текущая позиция стека
    long ppos; // середина массива
    int pivot; // опорный элемент
    int temp;

    lbstack[1] = 0;
    ubstack[1] = size-1;

    do {
        // Взять границы lb и ub текущего массива из стека.
        lb = lbstack[ stackpos ];
        ub = ubstack[ stackpos ];
        stackpos--;

        do {
            // Шаг 1. Разделение по элементу pivot
            ppos = ( lb + ub ) >> 1;
            i = lb; j = ub; pivot = a[ppos];
            do {
                while ( a[i] < pivot ) i++;
                while ( pivot < a[j] ) j--;
                if ( i <= j ) {
                    temp = a[i]; a[i] = a[j]; a[j] = temp;
                    i++; j--;
                }
            } while ( i <= j );

            // Сейчас указатель i указывает на начало правого подмассива,
            // j - на конец левого (см. иллюстрацию выше), lb ? j ? i ? ub.
            // Возможен случай, когда указатель i или j выходит за границу массива

            // Шаги 2, 3. Отправляем большую часть в стек и двигаем lb,ub
            if ( i < ppos ) { // правая часть больше
                if ( i < ub ) { // если в ней больше 1 элемента - нужно
                    stackpos++; // сортировать, запрос в стек
                    lbstack[ stackpos ] = i;
                    ubstack[ stackpos ] = ub;
                }
            ub = j; // следующая итерация разделения
            // будет работать с левой частью
            } else { // левая часть больше
                if ( j > lb ) {
                    stackpos++;
                    lbstack[ stackpos ] = lb;
                    ubstack[ stackpos ] = j;
                }
                lb = i;
            }
        } while ( lb < ub ); // пока в меньшей части более 1 элемента
    } while ( stackpos != 0 ); // пока есть запросы в стеке
}

// Сортировка слиянием
// Время работы | лучший случай | средний случай | худший случай |
//              |  O(N*log(N))  |   O(N*log(N))  |  O(N*log(N))  |
void merge(int *a, int low, int mid, int high, int *aux) {
   int i,j;
   for (i = mid+1; i > low; i--) {
       aux[i-1] = a[i-1];
   }
   for (j = mid; j < high; j++) {
       aux[high+mid-j]=a[j+1];
   }
   for (int k = low; k <= high; k++) {
      if (aux[j] < aux[i]) {
         a[k] = aux[j--];
      }
      else {
         a[k] = aux[i++];
      }
   }
}

void sort_insertion(int *a, int n) {
  for (int i = n-1; i > 0; i--) {
    if (a[i-1] > a[i]) {
      int tmp = a[i-1]; a[i-1] = a[i]; a[i] = tmp;
    }
  }
  for (int i = 2; i < n; i++) {
    int j = i;
    int tmp = a[i];
    while (tmp < a[j-1]) {
       a[j] = a[j-1]; j--;
    }
    a[j] = tmp;
  }
}

void mergeSort(int a[], int low, int high, int *aux) {
   const int THRESHOLD = 10;
   if (high - low < THRESHOLD) {
      sort_insertion(a+low, high-low+1);
   } else {
      int mid = (low + high) / 2;
      mergeSort(a, low, mid, aux);
      mergeSort(a, mid+1, high, aux);
      merge(a, low, mid ,high, aux);
  }
}

void sort_merge(int *a, int n) {
    int *aux = new int[n];
    mergeSort(a,0,n-1, aux);
    delete [] aux;
}

// Пирамидальная сортировка (heapsort)
// Время работы | лучший случай | средний случай | худший случай |
//              |      O(N)     |   O(N*log(N))  |  O(N*log(N))  |
void downHeap(int *a, long k, long n)
{
    //  процедура просеивания следующего элемента
    //  До процедуры: a[k+1]...a[n]  - пирамида
    //  После:  a[k]...a[n]  - пирамида
    int new_elem;
    long child;
    new_elem = a[k];

    while(k <= n/2) // пока у a[k] есть дети
    {
        child = 2*k;

        if( child < n && a[child] < a[child+1] ) //  выбираем большего сына
            child++;
        if( new_elem >= a[child] )
            break;
        // иначе
        a[k] = a[child];    // переносим сына наверх
        k = child;
    }
    a[k] = new_elem;
}

void heapSort(int *a, long size)
{
    long i;
    T temp;

  // строим пирамиду
    for(i = size / 2 - 1; i >= 0; --i)
        downHeap(a, i, size-1);

  // теперь a[0]...a[size-1] пирамида

    for(i=size-1; i > 0; --i)
    {
        // меняем первый с последним
        temp = a[i];
        a[i] = a[0];
        a[0] = temp;
        // восстанавливаем пирамидальность a[0]...a[i-1]
        downHeap(a, 0, i-1);
    }
}

// Порязрядная сортировка
// время работы | лучший случай | средний случай | худший случай |
//              |      O(N)     |       O(N)     |      O(N)     |
typedef struct slist_ {
    long val;
    struct slist_ *next;
} slist;

// функция сортировки возвращает указатель на начало отсортированного списка
slist *radix_list(slist *l, int t) {
    //  t - разрядность (максимальная длина числа)
    int i, j, d, m=1;
    slist *temp, *out, *head[10], *tail[10];
    out=l;

    for (j=1; j<=t; j++) {
        for (i=0; i<=9; i++)
            head[i] = (tail[i]=NULL);

        while ( l != NULL ) {
            d = ((int)(l->val/m))%(int)10;
            temp = tail[d];
            if ( head[d]==NULL ) head[d] = l;
            else temp->next = l;
            temp = tail[d] = l;
            l = l->next;
            temp->next = NULL;
        }
        for (i=0; i<=9; i++)
            if ( head[i] != NULL ) break;
        l = head[i];
        temp = tail[i];
        for (d=i+1; d<=9; d++) {
            if ( head[d] != NULL) {
                temp->next = head[d];
                temp = tail[d];
            }
        }
        m*=10;
    }
    return (out);
}

#endif // SORTING_REALISATIONS
