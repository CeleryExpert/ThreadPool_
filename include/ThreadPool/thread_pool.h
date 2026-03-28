#pragma once
#include<thread>
#include<vector>
#include<queue>
#include "task.h"

class ThreadPool{
public:
private:
    std::vector<std::thread> threads_;
    std::priority_queue<Task> task_queue_;
    std::atomic<bool> is_Running_;
};