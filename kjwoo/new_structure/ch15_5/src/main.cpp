#include <condition_variable>
#include <exception>
#include <functional>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>
class ThreadPool {
    size_t num_threads_;
    std::vector<std::thread> worker_threads_;
    std::queue<std::function<void()>> jobs_;
    std::mutex m_job_q_;
    std::condition_variable cv_job_q_;
    bool stop_all;

public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();
    void workerThread();
    void EnqueueJob(std::function<void()> job);
};

ThreadPool::ThreadPool(size_t num_threads) : num_threads_(num_threads), stop_all(false) {
    worker_threads_.reserve(num_threads_);
    for (size_t i = 0; i < num_threads_; i++) {
        worker_threads_.emplace_back([this]() { this->workerThread(); });
    }
}
void ThreadPool::workerThread() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_job_q_);  // 큐에 접근할때 락을 건다.
        cv_job_q_.wait(
            lock, [this]() { return !this->jobs_.empty() || stop_all; });  // job큐가 비었거나 stop_all이 true이면 대기.
        if (stop_all && this->jobs_.empty()) {
            return;  // job이 다 비었고 job도 없으면 스레드 종료
        }
        std::function<void()> job = std::move(jobs_.front());
        jobs_.pop();
        lock.unlock();
        job();
    }
}
void ThreadPool::EnqueueJob(std::function<void()> job) {
    if (stop_all) {
        throw std::runtime_error("ThreadPool 사용 중지됨.");
    }
    {
        std::lock_guard<std::mutex> lock(m_job_q_);  // lock 걸고
        jobs_.push(std::move(job));                  // job 추가
    }  // 괄호끝나면서 lock_guard소멸 - unlock 자동
    cv_job_q_.notify_one();  // 스레드 하나 깨움.
}

ThreadPool::~ThreadPool() {
    stop_all = true;
    cv_job_q_.notify_all();
    for (auto& t : worker_threads_) {
        t.join();
    }
}
void work(int t, int id) {
    printf("%d start \n", id);
    std::this_thread::sleep_for(std::chrono::seconds(t));
    printf("%d end after %ds\n", id, t);
}

int main() {
    ThreadPool pool(3);

    for (int i = 0; i < 10; i++) {  // job 10개를 큐에 추가.
        pool.EnqueueJob([i]() { work(i % 3 + 1, i); });
    }
}
