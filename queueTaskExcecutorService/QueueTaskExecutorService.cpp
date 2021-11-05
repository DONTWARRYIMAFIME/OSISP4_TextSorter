//
// Created by Kostyukovich_V_A on 11/5/2021.
//

#include "QueueTaskExecutorService.h"

using namespace std;

QueueTaskExecutorService::QueueTaskExecutorService(std::vector<string>& vector, int threadsCount)
{
    this->source = vector;
    this->threadsCount = threadsCount;
    this->threadPoolService = new ThreadPoolTaskService(1, threadsCount);
}

QueueTaskExecutorService::~QueueTaskExecutorService()
{
    delete threadPoolService;
}


void QueueTaskExecutorService::execute()
{
    distributeTasks(this->source);
    mergeSort(this->source);
}

void QueueTaskExecutorService::distributeTasks(std::vector<string>& vector)
{
    if (vector.empty())
    {
        return;
    }

    int mainPartsCount = vector.size() / threadsCount;
    int leftPartsCount = vector.size() % threadsCount;

    int offset = 0;
    for (int i = 0; i < mainPartsCount; i++)
    {
        submitTask(vector, offset, threadsCount);
        offset += threadsCount;
    }

    if (leftPartsCount > 0)
    {
        submitTask(vector, offset, leftPartsCount);
    }

    threadPoolService->waitAndClose();
}

void QueueTaskExecutorService::submitTask(std::vector<string>& vector, int begin, int end)
{
    QueueTask task;
    task.begin = vector.begin() + begin;
    task.end = vector.begin() + begin + end;

    threadPoolService->submitTask(task);
}


void QueueTaskExecutorService::mergeSort(std::vector<string>& vector)
{
    if (vector.size() == 0)
    {
        return;
    }

    int mainPartsCount = vector.size() / threadsCount;
    auto curr = vector.begin() + threadsCount;
    for (int i = 0; i < mainPartsCount - 1; i++)
    {
        std::inplace_merge(vector.begin(), curr, curr + threadsCount);
        curr += threadsCount;
    }
}

vector<string> QueueTaskExecutorService::getVector()
{
    return source;
}