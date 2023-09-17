#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
void counting_sort(int arr[], int sorted_arr[], int k, int n){
    int *count = new int[k];
    for(int i = 0; i < k; i++){
        count[i] = 0;
    }
    for(int i = 0; i < n; i++){
        count[arr[i]]++;
    }
    for(int i = 1; i < k; i++){
        count[i] += count[i-1];
    }
    for(int i = n - 1; i >= 0; i--){
        sorted_arr[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
}
int num[1 << 21];
int sorted_num[1 << 21];
int temp[1 << 21];
int main(){
    ofstream fout_time("../output/counting_sort/time.txt");
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
            counting_sort(num, sorted_num, 32768, n);
            clock_t end = clock();
            total_delay += (double) (end - start) / CLK_TCK;
            memcpy(num, temp, (1 << 21) * sizeof(int));
        }
        string file_name = "../output/counting_sort/result_" + to_string(j) + ".txt"; 
        ofstream fout_result(file_name);
        for(int i = 0; i < n; i++){
            fout_result << sorted_num[i] << endl;
        }
        fout_time << "index: " << j << " => time: " << total_delay / 5 << "ms" << endl;
        cout << total_delay / 5 << endl;
        fout_result.close();
        fin.close();
    }    fout_time.close();
    return 0;
}