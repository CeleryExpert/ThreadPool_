#include "../include/ThreadPool/task.h"

Task:: Task(int pri){
    pri_ = pri;
    task_id_ = IdGenerator::getInstance().currentId();
}

IdGenerator:: IdGenerator(){
    counter_ = 1;
}

IdGenerator& IdGenerator:: getInstance(){
    static IdGenerator gen;
    return gen;
}

int64_t IdGenerator:: currentId(){
    int64_t ans = counter_.load(std::memory_order_relaxed);
    next();
    return ans;
}

void IdGenerator:: next(){
    counter_.fetch_add(1,std::memory_order_relaxed);
}
