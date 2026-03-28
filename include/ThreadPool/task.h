#pragma once
#include <cstdint>
#include <future>
#include <functional>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

class Task {
public:
    Task() = default;

    template <class F, class... Args>
    Task(int64_t task_id, int64_t pri, F&& f, Args&&... args)
        : task_id_(task_id), pri_(pri) {
        task_ = [fn = std::forward<F>(f),
                 params = std::make_tuple(std::forward<Args>(args)...)]() mutable {
            std::apply(std::move(fn), std::move(params));
        };
    }

    void run() {
        if (task_) {
            task_();
        }
    }

    int64_t id() const { return task_id_; }
    int64_t priority() const { return pri_; }

    template <class F, class... Args>
    static auto make_with_future(int64_t task_id, int64_t pri, F&& f, Args&&... args)
        -> std::pair<Task, std::future<std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>>> {
        using Ret = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>;

        auto bound = [fn = std::forward<F>(f),
                      params = std::make_tuple(std::forward<Args>(args)...)]() mutable -> Ret {
            return std::apply(std::move(fn), std::move(params));
        };

        auto packaged = std::make_shared<std::packaged_task<Ret()>>(std::move(bound));
        auto fut = packaged->get_future();

        Task task(task_id, pri, [packaged]() mutable {
            (*packaged)();
        });

        return {std::move(task), std::move(fut)};
    }

    // priority_queue 默认把“最大”元素放在 top，这里让 pri_ 越大优先级越高
    bool operator<(const Task& other) const {
        return pri_ < other.pri_;
    }

private:
    int64_t task_id_{0};
    int64_t pri_{0};
    std::function<void()> task_;
};
