#include "../include/ThreadPool/mytask.h"
#include<future>
#include<iostream>
#include<functional>


template <class R>
template <typename F, typename... Args>
MyTask<R>::MyTask(int pri, F &&f, Args &&...args) : Task(pri)
{
    auto func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    p_task_ = std::packaged_task<R()>(std::move(func));
}

template <class R>
void MyTask<R>::exec() 
{
    if(p_task_.valid()){
        p_task_();
    }
}