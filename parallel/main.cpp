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

#define NUMBER_OF_THREADS 4
char TRAIN_0_CSV[12] = "train_0.csv";
char TRAIN_1_CSV[12] = "train_1.csv";
char TRAIN_2_CSV[12] = "train_2.csv";
char TRAIN_3_CSV[12] = "train_3.csv";
char WEIGHTS_CSV[12] = "weights.csv";

/*
int classifier(vector<vector<long double>> &mobiles, vector<vector<long double>> &weights, vector<long double> &mins, vector<long double> &maxs);
void calc_min_max(vector<vector<long double>> &mobiles, vector<long double> &mins, vector<long double> &maxs);
void read_csv_train(vector<vector<long double>> &mobiles, char *directory);
void read_csv_weights(vector<vector<long double>> &weights, char *directory);
*/

int main(int argc, char *argv[]) {
    pthread_t thread[NUMBER_OF_THREADS];
	for(long tid = 0; tid < NUMBER_OF_THREADS; tid++) {
        
	}
/*    char path_train[256];
    char path_weights[256];
    strcpy(path_train, argv[1]);
    strcpy(path_weights, argv[1]);
    strncat(path_train, TRAIN_CSV, strlen(TRAIN_CSV));
    strncat(path_weights, WEIGHTS_CSV, strlen(WEIGHTS_CSV));
    vector<vector<long double>> mobiles, weights;
    vector<long double> mins, maxs;
    read_csv_train(mobiles, path_train);
    read_csv_weights(weights, path_weights);
    calc_min_max(mobiles, mins, maxs);
    int correct_detected = classifier(mobiles, weights, mins, maxs);
    int num_of_samples = mobiles.size();
    long double accuracy = (long double)correct_detected / (long double)num_of_samples * 100;
    cout << setprecision(2) << fixed;
    cout << "Accuracy: " << accuracy << "%" << endl; */
    return 0;
}

/*
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
} */