/* 
 * File:   main.cpp
 * Author: benwa_000
 *
 * Created on January 25, 2015, 7:56 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>


using namespace std;

/*
 * 
 */

int inversions = 0;

void divarray(int src[], int dest1[], int dest2[], int count) {
    int i;
    
    for (i = 0; i < (count / 2); i++) {
        dest1[i] = src[i];
    }
    int j = 0;
    for (; i < count; i++) {
        dest2[j] = src[i];
        j++;
    }
}

void merge(int h, int m, const int U[], const int V[], int S[]) {
    int i, j, k;
    i = 0; j = 0; k = 0;
	int values_to_jump = h;
    while (i < h && j < m) {
        if (U[i] < V[j]) {
            S[k] = U[i];
            i++;
			values_to_jump--;
        }
        else {
            S[k] = V[j];
            j++;
            inversions += (values_to_jump - i);
        }
        k++;
    }
    if (i > h) {
        for (int r = j; r < m; r++) {
            S[k++] = V[r];
        }
    }
    else {
        for (int r = i; r < h; r++) {
            S[k++] = U[r];
        }
    }
}

void mergesort(int n, int S[]) {
    int * U;
    int * V;
    if (n > 1) {
        const int h = n / 2;
        const int m = n - h;
        U = new int[h];
        V = new int[m];
        divarray(S, U, V, n);
        mergesort(h, U);
        mergesort(m, V);
        merge(h, m, U, V, S);
    }
    //delete[] U;
    //delete[] V;
}

//int main(int argc, char** argv) {
//    int arr [] = {27, 10, 12, 20, 25, 13, 15, 22};
//    
//    mergesort(8, arr);
//    int counter = 0;
//    while (counter < 8) {
//        cout << arr[counter] << " ";
//        counter++;
//    }
//}

int main(int argc, char** argv) {
    string input;
    string temp;
    int size = 0;
    int spaceloc = 0;
    int * students;
    bool lineflag = 0;
    
    getline(cin, input);
    
    while (input != "0") {
        if (!lineflag) {
            size = atoi(input.c_str());
            lineflag = 1;
        }
        else {
            students = new int[size];
            for (int i = 0; i < size; i++) {
                spaceloc = input.find(" ");
                if (spaceloc > 0) {
                    temp = input;
                    input = input.substr(spaceloc + 1);
                    temp.erase(spaceloc, temp.length());
                }
                else {
                    temp = input;
                }
                students[i] = atoi(temp.c_str());
            }
            lineflag = 0;
            inversions = 0;
            mergesort(size, students);
            
//            for (int j = 0; j < size; j++) {
//                cout << students[j] << " - ";
//            }
            //cout << endl;
            cout << inversions << endl;
            delete[] students;
        }
        
        getline(cin, input);
    }
    
    delete[] students;
    return 0;
}


