//
// Created by Kostyukovich_V_A on 11/3/2021.
//

#ifndef OSISP4_THREADSMANAGEMENT_QUEUETASKEXECUTOR_H
#define OSISP4_THREADSMANAGEMENT_QUEUETASKEXECUTOR_H

#include "../synchronizedQueue/SynchronizedQueue.h"

using namespace std;

class ThreadPoolTaskService
{
public:
    ThreadPoolTaskService(int minThreads, int maxThreads);

    void submitTask(QueueTask& task);

    void waitAndClose();

private:
    static void CALLBACK WorkCallBack(PTP_CALLBACK_INSTANCE, PVOID parameter, PTP_WORK);

private:
    PTP_POOL pool;
    PTP_CLEANUP_GROUP cleanupGroup;
    TP_CALLBACK_ENVIRON callbackEnvironment{};
    PTP_WORK work;

    SynchronizedQueue sQueue;
};


#endif //OSISP4_THREADSMANAGEMENT_QUEUETASKEXECUTOR_H