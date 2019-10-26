/*
 * "Copyright 2019 Dmitry Boldin"
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "static_lib.h"

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

int get_highest_diff_mp(const int* temperatures, int n) {
    int processes_count = 4;

    int status;

    int start, end;
    int k;

    pid_t pid;
    int fd[2];
    pipe(fd);

    int chang_size = n / processes_count;
    int buff[2];
    buff[1] = chang_size;
    for (k = 0; k < processes_count; k++) {
        buff[0] = k;

        write(fd[1], &buff, sizeof(int)*2);

        pid = fork();
        if (pid == -1) {
            printf("SOMETHING WRONG");
            exit(-1);
        } else if (pid == 0) {
            int result[1];
            int params[2];
            read(fd[0], &params, sizeof(int)*2);

            start = params[0] * params[1];
            end = (params[0] + 1) * params[1];
            result[0] = get_highest_diff(temperatures, start, end);

            write(fd[1], &result, sizeof(int));

            exit(0);
        }
    }
    waitpid(pid, &status, 0);
    int answers_of_processes[processes_count]; // NOLINT
    read(fd[0], &answers_of_processes, sizeof(int)*processes_count);

    int max_diff = 0, index = -1;
    for (k = 0; k < processes_count; ++k) {
        if (answers_of_processes[k] > max_diff) {
            index = answers_of_processes[k];
            max_diff = answers_of_processes[k];
        }
    }

    //    Проверяем стыки
    for (int k = 1; k < processes_count - 1; ++k) {
        int tmp = temperatures[k * chang_size] -
                  temperatures[(k + 1) * chang_size];
        if (tmp > max_diff) {
            max_diff = tmp;
            index = (k+1)*chang_size;
        }
    }
    return index;
}
