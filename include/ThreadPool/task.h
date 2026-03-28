#pragma once
#include <thread>
#include <atomic> 

class Task
{
public:
    Task(int);
    Task(Task &&) = default;
    Task(const Task &) = delete;
    Task operator = (const Task&) = delete;
    virtual ~Task() = default;
    virtual void exec() = 0;
    bool operator < (const Task &o) const;
protected:
    int64_t pri_;
    int64_t task_id_;
};


class IdGenerator{
public:
    IdGenerator(const IdGenerator&) = delete;
    IdGenerator operator = (const IdGenerator&) =delete;
    static IdGenerator& getInstance();
    void next();
    int64_t currentId();
private:
    std::atomic<int64_t>  counter_;
    IdGenerator();
};


