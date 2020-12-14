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


void read_csv_train(vector<vector<long double>> &mobiles, char *directory);
void read_csv_weights(vector<long double> &weights, char *directory);


int main(int argc, char *argv[]) {
    char path_train[256];
    char path_weights[256];
    strcpy(path_train, argv[1]);
    strcpy(path_weights, argv[1]);
    strncat(path_train, TRAIN_CSV, strlen(TRAIN_CSV));
    strncat(path_weights, WEIGHTS_CSV, strlen(WEIGHTS_CSV));
    vector<vector<long double>> mobiles;
    vector<long double> weights;
    read_csv_train(mobiles, path_train);
    read_csv_weights(weights, path_weights);
    for (int i = 0; i < mobiles.size(); i++) {
        for (int j = 0; j < mobiles[i].size(); j++) {
            cout << mobiles[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
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


void read_csv_weights(vector<long double> &weights, char *directory) {
    ifstream csvfile(directory);
    string str, weight;
    getline(csvfile, str);
    getline(csvfile, str);
    stringstream s(str);
    while (getline(s, weight, ','))
        weights.push_back(stold(weight));
    csvfile.close();
}