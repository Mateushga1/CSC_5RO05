#include "Thread.h"
#include <stdexcept>

Thread::Thread(int id) : id(id) {
    pthread_attr_init(&posixThreadAttrId);
}

Thread::~Thread() {
    pthread_attr_destroy(&posixThreadAttrId);
}

void Thread::start(int priority) {
    if (started) throw std::runtime_error("Thread already started");
    started = true;

    int policy;
    pthread_attr_getschedpolicy(&posixThreadAttrId, &policy);
    sched_param schedParam;
    schedParam.sched_priority = priority;
    pthread_attr_setschedparam(&posixThreadAttrId, &schedParam);

    chrono.restart();
    pthread_create(&posixThreadId, &posixThreadAttrId, call_run, this);
}

void Thread::join() {
    if (started) pthread_join(posixThreadId, nullptr);
}

bool Thread::isStarted() const {
    return started;
}

long Thread::duration_ms() const {
    return chrono.lap_ms();
}

int Thread::getMaxPrio(int policy) {
    return sched_get_priority_max(policy);
}

int Thread::getMinPrio(int policy) {
    return sched_get_priority_min(policy);
}

void Thread::setMainSched(int policy) {
    sched_param schedParam;
    schedParam.sched_priority = (policy == SCHED_OTHER) ? 0 : getMaxPrio(policy);
    if (pthread_setschedparam(pthread_self(), policy, &schedParam) != 0) {
        throw std::runtime_error("Failed to set scheduling policy.");
    }
}

int Thread::getMainSched(int policy) {
    int current_policy;
    sched_param param;
    pthread_getschedparam(pthread_self(), &current_policy, &param);
    return current_policy;
}

void* Thread::call_run(void* v_thread) {
    Thread* thread = static_cast<Thread*>(v_thread);
    thread->run();
    thread->chrono.stop();
    return nullptr;
}
