//
// Created by Kostyukovich_V_A on 11/3/2021.
//

#include "ThreadPoolTaskService.h"

ThreadPoolTaskService::ThreadPoolTaskService(int minThreads, int maxThreads) {
    pool = CreateThreadpool(nullptr);
    if (pool == nullptr)
    {
        exit(1);
    }

    InitializeThreadpoolEnvironment(&callbackEnvironment);
    SetThreadpoolCallbackPool(&callbackEnvironment, pool);

    cleanupGroup = CreateThreadpoolCleanupGroup();
    if (cleanupGroup == nullptr)
    {
        DestroyThreadpoolEnvironment(&callbackEnvironment);
        CloseThreadpool(pool);
        exit(1);
    }
    SetThreadpoolCallbackCleanupGroup(&callbackEnvironment, cleanupGroup, nullptr);
    work = CreateThreadpoolWork(WorkCallBack, &sQueue, &callbackEnvironment);

    SetThreadpoolThreadMinimum(pool, minThreads);
    SetThreadpoolThreadMaximum(pool, maxThreads);
}

void ThreadPoolTaskService::waitAndClose()
{
    CloseThreadpoolCleanupGroupMembers(cleanupGroup, false, nullptr);
    CloseThreadpoolCleanupGroup(cleanupGroup);
    CloseThreadpool(pool);
}

void ThreadPoolTaskService::submitTask(QueueTask& task)
{
    sQueue.pushTask(task);
    SubmitThreadpoolWork(work);
}

void ThreadPoolTaskService::WorkCallBack(PTP_CALLBACK_INSTANCE, PVOID parameter, PTP_WORK)
{
    auto _sQueue = static_cast<SynchronizedQueue*>(parameter);
    QueueTask queueTask = _sQueue->popTask();

    sort(queueTask.begin, queueTask.end);
}
