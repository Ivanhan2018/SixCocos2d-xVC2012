#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

using namespace std;

pthread_cond_t condition;
pthread_mutex_t signalMutex;
pthread_mutex_t eventMutex;
int finishedTask = -1;

void* task(void *data)
{
    int num = *(int*)data;
    // Do some
    sleep(9-num);
    // Task finished
    pthread_mutex_lock(&eventMutex); // lock until the event will be processed by main thread
    pthread_mutex_lock(&signalMutex); // lock condition mutex
    finishedTask = num; // memorize task number
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&signalMutex); // unlock condtion mutex
}

int main(int argc, char *argv[])
{
    pthread_t thread[10];

    pthread_cond_init(&condition, NULL);
    pthread_mutex_init(&signalMutex, NULL); // First mutex locks signal
    pthread_mutex_init(&eventMutex, NULL); // Second mutex locks event processing

    int numbers[10];

    for (int i = 0; i < 10; i++) {
        numbers[i] = i;
        printf("created %d\n", i); // Creating 10 asynchronous tasks
        pthread_create(&thread[i], NULL, task, &numbers[i]);
    }

    for (int i = 0; i < 10;)
    {
        if (finishedTask >= 0) {
            printf("Task %d finished\n", finishedTask); // handle event
            finishedTask = -1; // reset event variable
            i++;
            pthread_mutex_unlock(&eventMutex); // unlock event mutex after handling
        } else {
            pthread_cond_wait(&condition, &signalMutex); // waiting for event
        }
    }

    return 0;
}