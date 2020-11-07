#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <thread>
#include <algorithm>
#include <queue>
#include <mutex>
#include <atomic>
#include <future>
#include <random>
#include <chrono>

using namespace std;

random_device rd;
mt19937 mt(rd());
uniform_real_distribution<double> dist(0.0, 1.0);

#define CLIENTS_COUNT 3
#define WORKERS_COUNT 3
#define REQUESTS_COUNT 10
#define MAX_BATCH_SIZE 10

//using Callback = function<void(const Request*, Response)>;
//typedef function<void(const Request*, Response)> Callback;

class EmptyQueue : public runtime_error {
public:
  EmptyQueue() : runtime_error("Empty queue") {}
};

template<typename T>
class SafeQueue {
public:
  void push(T el) {
    scoped_lock lock(mtx);
    q.push(el);
  }

  T pop() {
    T el = q.front();
    q.pop();
    return el;
  }

  size_t size() {
    scoped_lock lock(mtx);
    return q.size();
  }

  size_t unsafe_size() {
    return q.size();
  }

  mutex mtx;

private:
  queue<T> q;
}; 

struct Request {
  string query;
  Request(string query) : query(query) {}
};

struct Response {
  string result;
  int errorCode;
  Response(string result, int errorCode) : result(result), errorCode(errorCode) {}
};

namespace Database {
  vector<Response> BatchRequestTask(vector<Request> requests, string source) {
    vector<Response> responses;
    responses.reserve(requests.size());
    for (int i = 0; i < requests.size(); ++i) {
      responses.push_back(Response(requests[i].query + "w" + source, i));
    }
    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(requests.size() * 2000 * dist(mt))));
    return responses;
  }

  future<vector<Response>> BatchRequest(vector<Request> requests, string source) {
    return async(BatchRequestTask, requests, source);
  }
};

struct BatchedRequest {
  Request request;
  function<void(const Request, Response)> callback;
  BatchedRequest(Request request, function<void(const Request, Response)> callback) : request(request), callback(callback) {}
};

class Batcher {
public:
  bool AddRequest(Request request, function<void(const Request, Response)> callback) {
    cout << "AddRequest: " + request.query + " queue size: " + to_string(requestsQueue.size()) + " needToStop: " + to_string(needToStop) + "\n";
    if (needToStop) return false;
    if (requestsQueue.size() < MAX_BATCH_SIZE) {
      requestsQueue.push(BatchedRequest(request, callback));
      return true;
    }
    else {
      return false;
    }
  }

  void StartProcessingQueue() {
    cout << "StartProcessingQueue\n";
    if (!needToStop) return;
    needToStop = false;
    for (int i = 0; i < WORKERS_COUNT; ++i) {
      workers.push_back(thread(&Batcher::ProcessQueue, this, to_string(i + 1)));
    }
    //processing_queue_future = async(&Batcher::ProcessQueue, this);
  }

  void StopProcessingQueue() {
    cout << "StopProcessingQueue\n";
    if (needToStop) return;
    needToStop = true;
    for (int i = 0; i < WORKERS_COUNT; ++i) {
      workers[i].join();
    }
  }

private:
  void ProcessQueue(string worker_id) {
    cout << "ProcessQueue " + worker_id + "\n";
    int passed = 0;
    while (requestsQueue.size() || !needToStop) {
      if (requestsQueue.size() >= max_batch_size || passed >= max_pending_time) {
        SendBatch(worker_id);
        passed = 0;
      }
      this_thread::sleep_for(1ms);
      passed += 1;
      // need to implement max_pending_time
    }
    cout << "Exiting ProcessQueue\n";
  }

  void SendBatch(string worker_id) {
    vector<BatchedRequest> batch;
    vector<Request> requests;
    {
      // Single lock to avoid spreading requests between workers
      scoped_lock lck(requestsQueue.mtx);
      int batch_size = min(requestsQueue.unsafe_size(), max_batch_size);
      // Check to avoid unneeded work
      if (!batch_size) return;
      for (int i = 0; i < batch_size; ++i) {
        BatchedRequest batchedRequest = requestsQueue.pop();
        batch.push_back(batchedRequest);
        requests.push_back(batchedRequest.request);
        cout << "SendBatch: " + batchedRequest.request.query + "w" + worker_id + " batch " + to_string(batch.size()) + 
          ", left " + to_string(requestsQueue.unsafe_size()) + "\n";
      }
    }
    cout << "SentBatch: " + to_string(batch.size()) + ", left " + to_string(requestsQueue.size()) + " from w" + worker_id + "\n";
    auto result = Database::BatchRequest(requests, worker_id);
    vector<Response> responses = result.get();
    for (int i = 0; i < batch.size(); ++i) {
      batch[i].callback(batch[i].request, responses[i]);
    }
  }

  SafeQueue<BatchedRequest> requestsQueue;
  size_t max_batch_size = 3;
  int max_pending_time = 200; // milliseconds
  atomic<bool> needToStop{ true };
  future<int> processing_queue_future;
  vector<thread> workers;
};

void ResponseCallback(const Request request, Response response) {
  cout << "Callback: " + response.result + "\n";
}

int AddRequests(Batcher* batcher, string client_id, size_t requests_count) {
  for (int i = 1; i <= requests_count; ++i) {
    string request_id = "c" + client_id + "n" + to_string(i);
    while (!batcher->AddRequest(Request(request_id), ResponseCallback)) {
      cout << "Queue is full. Retrying: " + request_id + "\n";
      this_thread::sleep_for(chrono::milliseconds(static_cast<int>(1000 * dist(mt))));
    }
    this_thread::sleep_for(chrono::milliseconds(static_cast<int>(1000 * dist(mt))));
  }
  cout << "Client finished: " + client_id + "\n";
  return 0;
}

int main() {
  Batcher batcher;
  batcher.StartProcessingQueue();
  vector<future<int>> futures;
  futures.resize(CLIENTS_COUNT);
  for (int i = 0; i < CLIENTS_COUNT; ++i) {
    futures[i] = async(AddRequests, &batcher, to_string(i + 1), REQUESTS_COUNT);
  }
  for (int i = 0; i < CLIENTS_COUNT; ++i) {
    futures[i].get();
  }
  batcher.StopProcessingQueue();
}
