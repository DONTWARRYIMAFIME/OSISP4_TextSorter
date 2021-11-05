//
// Created by Kostyukovich_V_A on 11/5/2021.
//

#ifndef OSISP4_THREADSMANAGEMENT_SYNCHRONIZEDQUEUE_H
#define OSISP4_THREADSMANAGEMENT_SYNCHRONIZEDQUEUE_H

#include <queue>
#include <windows.h>
#include "../queueTask/QueueTask.h"

using namespace std;

class SynchronizedQueue
{
public:
    SynchronizedQueue();
    ~SynchronizedQueue();

    void pushTask(QueueTask& task);
    QueueTask popTask();
private:
    queue<QueueTask> sQueue;

    CRITICAL_SECTION pushCriticalSection{};
    CRITICAL_SECTION popCriticalSection{};
};


#endif //OSISP4_THREADSMANAGEMENT_SYNCHRONIZEDQUEUE_H