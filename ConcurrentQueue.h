/*
 * ConcurrentQueue - A C++ template class for a thread-safe concurrent queue. It's very simple you write it yourself in an hour.
 * Author: Apurv Kumar
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ConcurrentQueue {
  std::queue<T> internalQueue;
  std::mutex internalMutex;
  std::condition_variable internalCondition;

public:
  void push(const T&);
  void push(T&&);
  T pop();
  bool isEmpty();
  size_t size();
};

template <typename T>
void ConcurrentQueue<T>::push(const T& value) {
  std::unique_lock<std::mutex> lock(internalMutex);
  internalQueue.push(value);
  internalCondition.notify_one();
}

template <typename T>
void ConcurrentQueue<T>::push(T&& value) {
  std::unique_lock<std::mutex> lock(internalMutex);
  internalQueue.push(std::move(value));
  internalCondition.notify_one();
}

template <typename T>
T ConcurrentQueue<T>::pop() {
  std::unique_lock<std::mutex> lock(internalMutex);
  internalCondition.wait(lock, [this] {return not(internalQueue.empty());});
  T value = std::move(internalQueue.front());
  internalQueue.pop();
  return value;
}

template <typename T>
bool ConcurrentQueue<T>::isEmpty() {
  std::unique_lock<std::mutex> lock(internalMutex);
  return internalQueue.empty();
}

template <typename T>
size_t ConcurrentQueue<T>::size() {
  std::unique_lock<std::mutex> lock(internalMutex);
  return internalQueue.size();
}

#endif
