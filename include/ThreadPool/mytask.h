#pragma once
#include "task.h"
#include<future>

template<class R>
class MyTask:public Task{
public:
    template<typename F, typename ... Args>
    MyTask(int ,F && , Args && ...);
    MyTask(MyTask&& ) = default;
    MyTask(const MyTask&) = delete;
    MyTask& operator=(const MyTask&) = delete;
    ~MyTask() = default;
    void exec() override;
private:
    std::packaged_task<R()> p_task_;
};

