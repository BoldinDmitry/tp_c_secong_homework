/*
 * "Copyright 2019 Dmitry Boldin"
 */


#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <assert.h>
#include "static_lib.h"

void test_solution() {
    // count of ints, that will be
    const int d = 2147483647;
    const int* arr;
    arr = generate_array(d);
    struct timespec start, finish;
    double elapsed_mp, elapsed_single;

    clock_gettime(CLOCK_MONOTONIC, &start);
    int max_i = get_highest_diff(arr, 0, d);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed_single = finish.tv_sec - start.tv_sec;
    elapsed_single += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;;

    clock_gettime(CLOCK_MONOTONIC, &start);
    int max_mt = get_highest_diff_mp(arr, d);
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed_mp = finish.tv_sec - start.tv_sec;
    elapsed_mp += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    assert(max_i == max_mt);
    assert(elapsed_single > elapsed_mp);
}


int main() {
    srand(time(NULL));
    test_solution();
    return 0;
}
