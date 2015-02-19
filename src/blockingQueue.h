#pragma once

#include <deque>
#include <pthread.h>
using namespace std;

template <class T>
class BlockingQueue {
private:
    bool _shutdown;
    deque<T> _data;
    pthread_mutex_t _lock;
    pthread_cond_t _cond;
public:
    BlockingQueue() {
        _shutdown = false;
        pthread_mutex_init(&_lock, NULL);
        pthread_cond_init(&_cond, NULL);
    }

    ~BlockingQueue() {
        pthread_mutex_destroy(&_lock);
        pthread_cond_destroy(&_cond);
    }

    void enqueue(T item) {
        pthread_mutex_lock(&_lock);
        _data.push_back(item);
        pthread_cond_signal(&_cond);
        pthread_mutex_unlock(&_lock);
    }

    bool dequeue(T& item) {
        pthread_mutex_lock(&_lock);
        while (_data.size() == 0) {
            pthread_cond_wait(&_cond, &_lock);            
            if(_shutdown) {
                return false;
            }
        }
        item = _data.front();
        _data.pop_front();
        pthread_mutex_unlock(&_lock);
        return true;   
    }

    int size() {
        pthread_mutex_lock(&_lock);
        int size = _data.size();
        pthread_mutex_unlock(&_lock);
        return size;
    }

    void shutdown() {
        _shutdown = true;
        pthread_cond_broadcast(&_cond);
    }
};