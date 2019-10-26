/*
 * "Copyright 2019 Dmitry Boldin"
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "dynamic_lib.h"  //NOLINT


const int* generate_array(int d) {
    int* arr = malloc(sizeof(int)*d);
    for (int i = 0; i < d; ++i) {
//        Generation of random int from -89(min temp on earth)
//        to 49(max temp on earth)
        arr[i] = rand() % (49 + 1 - -89) + -89; //NOLINT
    }
    return arr;
}

int get_highest_diff(const int *arr, int start, int end) {
    int max_difference = -1, max_index = -1;
    int tmp;
    for (int i = start; i < end-1; ++i) {
        tmp = arr[i] - arr[i+1];
        if (tmp > max_difference) {
            max_difference = tmp;
            max_index = tmp + 1;
        }
    }
    return max_index;
}
