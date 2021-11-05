//
// Created by Kostyukovich_V_A on 11/5/2021.
//

#ifndef OSISP4_THREADSMANAGEMENT_QUEUETASKEXECUTORSERVICE_H
#define OSISP4_THREADSMANAGEMENT_QUEUETASKEXECUTORSERVICE_H

#include "../threadPoolTaskService/ThreadPoolTaskService.h"

using namespace std;

class QueueTaskExecutorService
{
public:
    QueueTaskExecutorService(vector<string>& vector, int threadsCount);
    ~QueueTaskExecutorService();
    void execute();
    vector<string> getVector();
private:
    void distributeTasks(vector<string>& vector);
    void submitTask(vector<string>& vector, int begin, int end);
    void mergeSort(vector<string>& vector);
private:
    vector<string> source;
    int threadsCount;

    ThreadPoolTaskService* threadPoolService;
};


#endif //OSISP4_THREADSMANAGEMENT_QUEUETASKEXECUTORSERVICE_H