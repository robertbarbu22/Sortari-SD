#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <random>
#include <chrono>
#include <time.h>
#include <algorithm>

using namespace std;
using namespace std::chrono;

ifstream f("date.in");

void radix_sort16(vector<int>& v, int n)
{
    queue<int> q[16];
    int k;
    for (int i=0; i<=24; i=i+4)
    {
        for (int j=0; j<n; j++)
            q[(v[j] >> i) & 15].push(v[j]);
        k = 0;
        for (int j=0; j<=15 && k<n; j++)
            while (!q[j].empty())
            {
                v[k++] = q[j].front();
                q[j].pop();
            }
    }
}

void radix_sort256(vector<int>& v, int n)
{
    queue<int> q[256];
    int k;
    for (int i=0; i<=24; i=i+8)
    {
        for (int j=0; j<n; j++)
            q[(v[j] >> i) & 255].push(v[j]);
        k = 0;
        for (int j=0; j<=255 && k<n; j++)
            while (!q[j].empty())
            {
                v[k++] = q[j].front();
                q[j].pop();
            }
    }
}


void merge(vector<int>& v, int st, int mij, int dr)
{
    int i, j;
    vector<int> aux;

    i = st;
    j = mij+1;
    while (i<=mij && j<=dr)
        if (v[i] < v[j])
            aux.push_back(v[i++]);
        else aux.push_back(v[j++]);
    while (i <= mij)
        aux.push_back(v[i++]);
    while (j <= dr)
        aux.push_back(v[j++]);
    for (i = st; i <= dr; i++)
        v[i] = aux[i-st];
}

void merge_sort(vector<int>& v, int st, int dr)
{
    if (dr>st)
    {
        int mij = st+(dr-st)/2;
        merge_sort(v, st, mij);
        merge_sort(v, mij + 1, dr);
        merge(v, st, mij, dr);
    }
}

void shellSort(vector<int>& v, int n)
{
    for (int i=n/2; i>0; i/=2) {
        for (int j=i; j<n; j++) {
            int aux=v[j];
            int t;
            for (t=j; t>=i && v[t-i]>aux; t-=i) {
                v[t] = v[t-i];
            }
        v[t]=aux;
        }
    }
}



vector<int> count_sort(vector<int> v, int n, int max_el)
{
    int* f = new int[max_el + 1];
    int i;
    for (i = 0; i < max_el; i++) f[i] = 0;
    vector<int> aux;
    for (i = 0; i < n; i++)
        f[v[i]]++;
    for (i = 0; i <= max_el; i++)
        while (f[i]--)
            aux.push_back(i);

    delete[] f;
    return aux;

}

void quicksort(vector<int>& v, int st, int dr)
{
    int i = st, j = dr;
    int p = v[rand() % (dr - st + 1) + st];
    while (i < j)
    {
        while (v[i] < p) i++;
        while (v[j] > p) j--;
        if (i <= j) swap(v[i++], v[j--]);
    }
    if (j > st) quicksort(v, st, j);
    if (i < dr) quicksort(v, i, dr);
}

void sortare_nativa(vector<int>& v, int n){
    sort(v.begin(), v.end());
}


bool verificare(vector<int> v, int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
        if (v[i] > v[i + 1]) return false;
    return true;
}

int main()
{
    vector<int> v;
    int i, p, maxim, n, T;
    f>>T;
    for(p=1; p<=T; p++)
    {

        v.clear();
        f>>n>>maxim;
        cout<<"Test "<<p<<" n="<<n<<" maxim= "<<maxim<<"\n";
        for(i=0; i<n; i++)
            v.push_back(rand() % maxim+1);
        vector<int> aux;
        clock_t start;
        clock_t end;

        double elapsed;


            aux = v;
            start = clock();
            radix_sort256(aux, n);
            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;
            if (verificare(aux, n))
                cout << "Sortat corect. Timpul pentru RadixSort1 este " << elapsed << " secunde\n";
            else
                cout << "RadixSort1 - FAILED\n";

            aux = v;
            start = clock();
            radix_sort16(aux, n);
            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;
            if (verificare(aux, n))
                cout << "Sortat corect. Timpul pentru RadixSort2 este "<< elapsed << " secunde\n";
            else
                cout << "RadixSort2 - FAILED\n";

            aux = v;
            start = clock();
            merge_sort(aux, 0, n - 1);
            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;
            if (verificare(aux, n))
                cout << "Sortat corect. Timpul pentru MergeSort este " << elapsed << " secunde\n";
            else
                cout << "MergeSort - FAILED\n";

            start = clock();

            aux = count_sort(v, n, maxim);

            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;
            if (verificare(aux, n))
                cout << "Sortat corect. Timpul pentru CountSort este " << elapsed << " secunde\n";
            else
                cout << "CountSort - FAILED\n";

            aux = v;
            start = clock();
            quicksort(aux, 0, n - 1);
            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;
            if (verificare(aux, n))
                cout << "Sortat corect. Timpul pentru QuickSort este " << elapsed << " secunde\n";
            else
                cout << "QuickSort - FAILED\n";

            aux = v;
            start = clock();
            shellSort(aux, n);
            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;
            if (verificare(aux, n))
                cout << "Sortat corect. Timpul pentru ShellSort este " << elapsed << " secunde\n";
            else
                cout << "ShellSort - FAILED\n";

            aux = v;
            start = clock();
            sortare_nativa(aux, n);
            end = clock();
            elapsed = double(end - start) / CLOCKS_PER_SEC;
            if (verificare(aux, n))
                cout << "Sortat corect. Timpul pentru SortareNativa este " << elapsed << " secunde\n";
            else
                cout << "SortareNativa - FAILED\n";

            cout<<"\n";

    }
return 0;
}
