#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <pthread.h>
using namespace std;


int classifier(vector<vector<long double>> &mobiles, vector<vector<long double>> &weights, vector<long double> &mins, vector<long double> &maxs);
void calc_min_max(vector<vector<long double>> &mobiles, vector<long double> &mins, vector<long double> &maxs);
void read_csv_train(vector<vector<long double>> &mobiles, char *directory);
void read_csv_weights(vector<vector<long double>> &weights, char *directory);
void* thread_func(void* data);


#define NUMBER_OF_THREADS 4

char TRAIN_CSV[NUMBER_OF_THREADS][12] = {"train_0.csv", "train_1.csv", "train_2.csv", "train_3.csv"};
char WEIGHTS_CSV[12] = "weights.csv";
int flag[NUMBER_OF_THREADS] = {0, 0, 0, 0};
int correct_detected[NUMBER_OF_THREADS] = {0, 0, 0, 0};
int main_flag = 0;

vector<vector<long double>> weights;
vector<vector<long double>> mobiles[NUMBER_OF_THREADS];
vector<long double> mins[NUMBER_OF_THREADS];
vector<long double> maxs[NUMBER_OF_THREADS];
vector<long double> all_min;
vector<long double> all_max;

struct thread_data {
   int thread_id;
   char path_train[256];
};
struct thread_data thread_data_array[NUMBER_OF_THREADS];


int main(int argc, char *argv[]) {
    int tid, j;
    long double min, max;
    pthread_t threads[NUMBER_OF_THREADS];
    for (tid = 0; tid < NUMBER_OF_THREADS; tid++) {
        char path_train[256];
        strcpy(path_train, argv[1]);
        strncat(path_train, TRAIN_CSV[tid], strlen(TRAIN_CSV[tid]));
        thread_data_array[tid].thread_id = tid;
        strcpy(thread_data_array[tid].path_train, path_train);
        pthread_create(&threads[tid], NULL, thread_func, (void*)&thread_data_array[tid]);
    }
    char path_weights[256];
    strcpy(path_weights, argv[1]);
    strncat(path_weights, WEIGHTS_CSV, strlen(WEIGHTS_CSV));
    read_csv_weights(weights, path_weights);
    while (flag[0] == 0 || flag[1] == 0 || flag[2] == 0 || flag[3] == 0) {}
    for (j = 0; j < mins[0].size(); j++) {
        min = 1000000000;
        max = -1000000000;
        for (tid = 0; tid < NUMBER_OF_THREADS; tid++) {
            if (mins[tid][j] < min)
                min = mins[tid][j];
            if (maxs[tid][j] > max)
                max = maxs[tid][j];
        }
        all_min.push_back(min);
        all_max.push_back(max);
    }
    main_flag = 1;
    for (tid = 0; tid < NUMBER_OF_THREADS; tid++)
        pthread_join(threads[tid], NULL);
    int all_correct_detected = 0;
    int num_of_samples = 0;
    for (tid = 0; tid < NUMBER_OF_THREADS; tid++) {
        all_correct_detected += correct_detected[tid];
        num_of_samples += mobiles[tid].size();
    }
    long double accuracy = (long double)all_correct_detected / (long double)num_of_samples * 100;
    cout << setprecision(2) << fixed;
    cout << "Accuracy: " << accuracy << "%" << endl;
    pthread_exit(NULL);
}


void* thread_func(void* data) {
    struct thread_data* my_data = (struct thread_data*) data;
    int thread_id = my_data->thread_id;
	char* path_train = my_data->path_train;
    read_csv_train(mobiles[thread_id], path_train);
    calc_min_max(mobiles[thread_id], mins[thread_id], maxs[thread_id]);
    flag[thread_id] = 1;
    while (main_flag == 0) {}
    correct_detected[thread_id] = classifier(mobiles[thread_id], weights, all_min, all_max);
    pthread_exit(NULL);
}


void read_csv_train(vector<vector<long double>> &mobiles, char *directory) {
    ifstream csvfile(directory);
    string str, feature;
    getline(csvfile, str);
    while (getline(csvfile, str)) {
        vector<long double> mobile;
        stringstream s(str);
        while (getline(s, feature, ','))
            mobile.push_back(stold(feature));
        mobiles.push_back(mobile);
    }
    csvfile.close();
}


void read_csv_weights(vector<vector<long double>> &weights, char *directory) {
    ifstream csvfile(directory);
    string str, temp;
    getline(csvfile, str);
    while (getline(csvfile, str)) {
        vector<long double> weight;
        stringstream s(str);
        while (getline(s, temp, ','))
            weight.push_back(stold(temp));
        weights.push_back(weight);
    }
    csvfile.close();
}


void calc_min_max(vector<vector<long double>> &mobiles, vector<long double> &mins, vector<long double> &maxs) {
    for (int j = 0; j < mobiles[0].size(); j++) {
        long double min = 1000000000;
        long double max = -1000000000;
        for (int i = 0; i < mobiles.size(); i++) {
            if (mobiles[i][j] > max)
                max = mobiles[i][j];
            if (mobiles[i][j] < min)
                min = mobiles[i][j];
        }
        mins.push_back(min);
        maxs.push_back(max);
    }
}


int classifier(vector<vector<long double>> &mobiles, vector<vector<long double>> &weights, vector<long double> &mins, vector<long double> &maxs) {
    int correct_detected = 0;
    int price_range, i, j, k;
    long double score, max_score;
    for (i = 0; i < mobiles.size(); i++) {
        max_score = -1000000000;
        for (k = 0; k < weights.size(); k++) {
            score = weights[k][weights[0].size() -1];
            for (j = 0; j < mobiles[i].size() - 1; j++)
                score += (((mobiles[i][j] - mins[j]) / (maxs[j] - mins[j])) * weights[k][j]);
            if (score > max_score) {
                price_range = k;
                max_score = score;
            }
        }
        if (price_range == mobiles[i][mobiles[0].size() - 1])
            correct_detected += 1;
    }
    return correct_detected;
}