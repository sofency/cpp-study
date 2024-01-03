#pragma once
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
using namespace std;

typedef function<void(void*)> callback;

template <class T>
class Task {
 public:
  Task() {
    function = nullptr;
    arg = nullptr;
  }
  Task(callback f, void* arg) {
    function = f;
    this->arg = (T*)arg;
  }
  callback function;
  T* arg;
};

template <class T>
class TaskQueue {
 public:
  TaskQueue(int queue_size);
  ~TaskQueue();
  void addTask(const Task<T>& task);
  Task<T> takeTask();

  inline unsigned int taskNumber() { return taskQueue.size(); }

 private:
  queue<Task<T>> taskQueue;
  mutex mtx;
};

template <class T>
TaskQueue<T>::TaskQueue() {}

template <class T>
TaskQueue<T>::~TaskQueue() {}

template <class T>
void TaskQueue<T>::addTask(const Task<T>& task) {
  lock_guard<mutex> lock(mtx);
  taskQueue.push(task);
}

template <class T>
Task<T> TaskQueue<T>::takeTask() {
  lock_guard<mutex> lock(mtx);
  Task<T> task;
  if (!taskQueue.empty()) {
    task = taskQueue.front();
    taskQueue.pop();
  }
  return task;
}
