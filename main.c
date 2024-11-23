#include <stdio.h>
#include <stdbool.h>

#define TASKS_AMOUNT 3
#define QUANTUM 3

typedef struct {
    int id;
    int arrivalTime;
    int remainingTime;
    int finishTime;
    bool finished;
} Task;

int getNextTask(int currentTaskId, int currentExecutionTime, Task *tasks);

int executeTasksWithRoundRobinAlgorithm(Task *tasks) {
    int currentExecutionTime = 0;
    int currentQuantum = 0;
    int currentTaskId = 0;
    bool allTasksExecuted = 0;

    while (!allTasksExecuted) {
        while (currentQuantum < QUANTUM && currentTaskId >= 0) {
            currentExecutionTime++;

            (tasks+currentTaskId)->remainingTime--;

            if ((tasks+currentTaskId)->remainingTime == 0) {
                (tasks+currentTaskId)->finished = true;
                (tasks+currentTaskId)->finishTime = currentExecutionTime;
                break;
            }

            currentQuantum++;
        }

        currentTaskId = getNextTask(currentTaskId, currentExecutionTime, tasks);
        currentQuantum = 0;

        if (currentTaskId == -1) currentExecutionTime++;

        if (currentTaskId == -2) allTasksExecuted = true;
    }

    return currentExecutionTime;
}

int getNextTask(int currentTaskId, int currentExecutionTime, Task *tasks) {
    int traversedTasksAmount = 0;
    bool allTasksExecuted = true;

    if (currentTaskId == TASKS_AMOUNT - 1) currentTaskId = 0;
    else currentTaskId++;

    while (traversedTasksAmount < TASKS_AMOUNT) {
        if (!(tasks+currentTaskId)->finished) {
            allTasksExecuted = false;

            if (currentExecutionTime >= (tasks+currentTaskId)->arrivalTime) return currentTaskId;
        }

        if (currentTaskId == TASKS_AMOUNT-1) currentTaskId = 0;
        else currentTaskId++;

        traversedTasksAmount++;
    };

    if (!allTasksExecuted) return -1;
    else return -2;
}

int main(void) {
    Task tasks[TASKS_AMOUNT] = {};

    for (int i = 0; i < TASKS_AMOUNT; i++) {
        tasks[i].id = i;

        if (i > 0) {
            printf(("Task %d arrival time: "), i+1);
            scanf("%d", &tasks[i].arrivalTime);
        }
        else {
            tasks[i].arrivalTime = 0;
        }

        printf(("Task %d length: "), i+1);
        scanf("%d", &tasks[i].remainingTime);
        printf("\n");
    }

    int totalExecutionTime = executeTasksWithRoundRobinAlgorithm(tasks);

    printf("%-4s %-14s %-17s %-17s\n", "id", "Arrival Time", "Finishing Time", "Turnaround Time");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < TASKS_AMOUNT; i++) {
        printf("%-4d %-14d %-17d %-17d\n", tasks[i].id, tasks[i].arrivalTime, tasks[i].finishTime, tasks[i].finishTime - tasks[i].arrivalTime);
    }

    return 0;
}
