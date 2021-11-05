//
// Created by Kostyukovich_V_A on 11/5/2021.
//

#ifndef OSISP4_THREADSMANAGEMENT_QUEUETASK_H
#define OSISP4_THREADSMANAGEMENT_QUEUETASK_H

#include <vector>
#include <string>

using namespace std;

struct QueueTask
{
    vector<string>::iterator begin;
    vector<string>::iterator end;
};


#endif //OSISP4_THREADSMANAGEMENT_QUEUETASK_H