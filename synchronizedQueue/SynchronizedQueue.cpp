//
// Created by Kostyukovich_V_A on 11/5/2021.
//

#include "SynchronizedQueue.h"

SynchronizedQueue::SynchronizedQueue()
{
    InitializeCriticalSectionAndSpinCount(&popCriticalSection, 1024);
    InitializeCriticalSectionAndSpinCount(&pushCriticalSection, 1024);
}

SynchronizedQueue::~SynchronizedQueue()
{
    DeleteCriticalSection(&popCriticalSection);
    DeleteCriticalSection(&pushCriticalSection);
}

void SynchronizedQueue::pushTask(QueueTask& task)
{
    EnterCriticalSection(&pushCriticalSection);
    this->sQueue.push(task);
    LeaveCriticalSection(&popCriticalSection);
}

QueueTask SynchronizedQueue::popTask() {
    EnterCriticalSection(&popCriticalSection);
    QueueTask task = this->sQueue.front();
    this->sQueue.pop();
    LeaveCriticalSection(&popCriticalSection);

    return task;
}