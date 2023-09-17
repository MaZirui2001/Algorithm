#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
// #include <stack>
using namespace std;
#define INDEX 21
class record{
    public:
    int left;
    int right;
    record(int l, int r){
        left = l;
        right = r;
    }
};
template <class T>
class stack{
private:
    int size;
    T *base;
    T *top;
public:
    stack(int n){
        size = n;
        base = (T*) malloc((n+1) * sizeof(T));
        top = base;
    }
    bool empty(){
        return top == base;
    }
    T pop(){
        if(!empty())top--;
        return *top;
    }
    void push(T elem){
        *top = elem;
        top++;
        if(top - base >= size) cout << "error" <<endl;
    }
};

void swap(int arr[], int idx1, int idx2){
    int c = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = c;
}
int random_partition(int arr[], int p, int r){
    /* get a location to be the key */
    int idx = rand() % (r - p + 1) + p;
    /* swap the last one and the key */
    swap(arr, r, idx);
    int key = arr[r];
    int i = p - 1;
    for(int j = p; j < r; j++){
        if(arr[j] <= key){
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i+1, r);
    return i + 1;
}
// stack <record> rec;
stack <record> rec(1 << INDEX);
void quick_sort(int arr[], int p, int r){
    rec.push(record(p, r));
    while(!rec.empty()){
        /* get a record to do partition */
        record tmp = rec.pop();
        int q = random_partition(arr, tmp.left, tmp.right);
        /* push the left and right into stack */
        if(tmp.left < q-1){
            rec.push(record(tmp.left, q-1));
        }
        if(tmp.right > q+1){
            rec.push(record(q+1, tmp.right));
        }
    }
}
int num[1 << 21];
int temp[1 << 21];
int main(){
    ofstream fout_time("../output/quick_sort/time.txt", ios::app);
    for(int j = 19; j <= 21; j += 1){
        ifstream fin("../input/input.txt");
        int n = 1 << j;
        for(int i = 0; i < n; i++){
            fin >> num[i];
        }
        memcpy(temp, num, 262144 * sizeof(int));
        double total_delay = 0;
        for(int k = 0; k < 5; k++){
            clock_t start = clock();
            quick_sort(num, 0, n-1);
            clock_t end = clock();
            total_delay += (double)(end - start) / CLOCKS_PER_SEC;
            if(k != 4) memcpy(num, temp, 262144 * sizeof(int));
        }
        string file_name = "../output/quick_sort/result_" + to_string(j) + ".txt"; 
        ofstream fout_result(file_name);
        for(int i = 0; i < n; i++){
            fout_result << num[i] << endl;
        }
        fout_time << "index: " << j << " => time: " << total_delay / 5<< "ms" << endl;
        cout << total_delay / 5 << endl;
        fout_result.close();
        fin.close();
    }

    fout_time.close();
    return 0;
}
// int main(){
//     ifstream fin("../input/input.txt");
//     int n = 1 << INDEX;
//     for(int i = 0; i < n; i++){
//         fin >> num[i];
//     }
//     srand((unsigned)time(NULL));
//     memcpy(temp, num, 262144 * sizeof(int));
//     double total_delay = 0;
//     for(int k = 0; k < 1000; k++){
//         clock_t start = clock();
//         quick_sort(num, 0, n-1);
//         clock_t end = clock();
//         total_delay += (double) (end - start) / CLOCKS_PER_SEC;
//         if(k != 999) memcpy(num, temp, 262144 * sizeof(int));
//     }
//     string file_name = "../output/quick_sort/result_" + to_string(INDEX) + ".txt"; 
//     ofstream fout_result(file_name);
//     // for(int i = 0; i < n; i++){
//     //     fout_result << num[i] << endl;
//     // }
//     cout << total_delay << endl;
//     fout_result.close();
//     fin.close();
//     return 0;
// }