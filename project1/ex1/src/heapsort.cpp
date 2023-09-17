#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
void swap(int arr[], int idx1, int idx2){
    int c = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = c;
}
void max_heapify(int arr[], int idx, int size){
    int lson = idx * 2 + 1;
    int rson = lson + 1;
    while(lson < size){
        /* find the largest one between parent, lson and ron */
        int largest = lson;
        if(rson < size && arr[lson] < arr[rson]){
            largest = rson;
        }
        if(arr[idx] > arr[largest]){
            largest = idx;
        }
        // if parent is the largest, heap is alreay a max_heap
        if(largest == idx) break; 
        swap(arr, idx, largest);
        /* go down to adjust heap */
        idx = largest;
        lson = idx * 2 + 1;
        rson = lson + 1;
    }
}
void build_max_heap(int arr[], int size){
    for(int i = (size - 1) / 2; i >= 0; i--){
        max_heapify(arr, i, size);
    }
}
void heap_sort(int arr[], int size){
    build_max_heap(arr, size);
    for(int i = size - 1; i > 0; i--){
        swap(arr, 0, i);
        size -= 1;
        max_heapify(arr, 0, size);
    }
}
int num[1 << 21];
int temp[1 << 21];
int main(){
    ofstream fout_time("../output/heap_sort/time.txt");
    for(int j = 3; j <= 21; j += 3){
        ifstream fin("../input/input.txt");
        int n = 1 << j;
        for(int i = 0; i < n; i++){
            fin >> num[i];
        }
        memcpy(temp, num, (1 << 21) * sizeof(int));
        double total_delay = 0;
        for(int k = 0; k < 5000; k++){
            clock_t start = clock();
            heap_sort(num, n);
            clock_t end = clock();
            total_delay += (double)(end - start) / CLOCKS_PER_SEC;
            if(k != 4999) memcpy(num, temp, (1 << 21) * sizeof(int));
        }
        string file_name = "../output/heap_sort/result_" + to_string(j) + ".txt"; 
        ofstream fout_result(file_name);
        for(int i = 0; i < n; i++){
            fout_result << num[i] << endl;
        }
        fout_time << "index: " << j << " => time: " << total_delay / 5 << "ms" << endl;
        cout << total_delay / 5 << endl;
        fout_result.close();
        fin.close();
    }
    fout_time.close();
    return 0;
}