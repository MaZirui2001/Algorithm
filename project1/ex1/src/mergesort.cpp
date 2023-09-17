#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
void merge(int arr[], int p, int q, int r){
    int num1 = q - p + 1;
    int num2 = r - q;
    // int left[131073];
    // int right[131073];
    int *left = new int[num1+1];
    int *right = new int[num2+1];
    for(int i = 0; i < num1; i++){
        left[i] = arr[p + i];
    }
    left[num1] = INT32_MAX;
    for(int i = 0; i < num2; i++){
        right[i] = arr[q + 1 + i];
    }
    right[num2] = INT32_MAX;
    int i = 0, j = 0;
    for(int k = p; k <= r; k++){
        if(left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        }
        else{
            arr[k] = right[j];
            j++;
        }
    }
    delete [] left;
    delete [] right;
}
void merge_sort(int arr[], int p, int r){
    int left, mid, right;
    /* for each step, the length should double */
    for(int i = 1; i < r - p + 1; i *= 2){
        for(left = p ; left < r - p + 1 - i; left = right + 1){
            mid = left + i - 1; // get middle elem
            right = mid + i;
            if (right > r) right = r; // right may be larger than r
            merge(arr, left, mid, right);
        }
    }
}
int num[1 << 21];
int temp[1 << 21];
int main(){
    ofstream fout_time("../output/merge_sort/time.txt");
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
            merge_sort(num, 0, n-1);
            clock_t end = clock();
            total_delay += (double)(end - start) / CLK_TCK;
            if(k != 4999) memcpy(num, temp, (1 << 21) * sizeof(int));
        }
        string file_name = "../output/merge_sort/result_" + to_string(j) + ".txt"; 
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