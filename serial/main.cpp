#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


char TRAIN_CSV[10] = "train.csv";
char WEIGHTS_CSV[12] = "weights.csv";


void calc_min_max(vector<vector<float>> &mobiles, vector<float> &mins, vector<float> &maxs);
void read_csv_train(vector<vector<float>> &mobiles, char *directory);
void read_csv_weights(vector<float> &weights, char *directory);


int main(int argc, char *argv[]) {
    char path_train[256];
    char path_weights[256];
    strcpy(path_train, argv[1]);
    strcpy(path_weights, argv[1]);
    strncat(path_train, TRAIN_CSV, strlen(TRAIN_CSV));
    strncat(path_weights, WEIGHTS_CSV, strlen(WEIGHTS_CSV));
    vector<vector<float>> mobiles;
    vector<float> weights, mins, maxs;
    read_csv_train(mobiles, path_train);
    read_csv_weights(weights, path_weights);
    calc_min_max(mobiles, mins, maxs);
    return 0;
}


void read_csv_train(vector<vector<float>> &mobiles, char *directory) {
    ifstream csvfile(directory);
    string str, feature;
    getline(csvfile, str);
    while (getline(csvfile, str)) {
        vector<float> mobile;
        stringstream s(str);
        while (getline(s, feature, ','))
            mobile.push_back(stold(feature));
        mobiles.push_back(mobile);
    }
    csvfile.close();
}


void read_csv_weights(vector<float> &weights, char *directory) {
    ifstream csvfile(directory);
    string str, weight;
    getline(csvfile, str);
    getline(csvfile, str);
    stringstream s(str);
    while (getline(s, weight, ','))
        weights.push_back(stold(weight));
    csvfile.close();
}


void calc_min_max(vector<vector<float>> &mobiles, vector<float> &mins, vector<float> &maxs) {
    for (int j = 0; j < mobiles[0].size(); j++) {
        float min = 1000000000;
        float max = -1;
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