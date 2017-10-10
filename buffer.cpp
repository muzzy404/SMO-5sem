#include "buffer.h"
#include "counter.h"

#include <stdexcept>
#include <algorithm>

#include <iostream>

Buffer::Buffer(const int size) :
  occupied_(0)
{
  buffer_ = std::vector<Request_ptr>(size, nullptr);
}

void Buffer::add(const Request_ptr request)
{
  if (request == nullptr) {
    throw std::invalid_argument("request null ptr");
  }

  for(auto it = buffer_.begin(); it != buffer_.end(); ++it) {
    if (*it == nullptr) {
      *it = request;
      ++occupied_;
      return;
    }
  }

  // all places are occupied
  Counter::add_to_rejected();
}

void Buffer::print_reqs() const
{
  for(Request_ptr req : buffer_) {
    if (req == nullptr) {
      std::cout << "null\n";
      continue;
    }
    std::cout << req->get_priority() << "." << req->get_number() << "\n";
  }
}

/*Buffer::Request_ptr Buffer::get()
{
  // if no requests in buffer
  if (occupied_ == 0)
  {
    return nullptr;
  }

  std::vector<Request_ptr> all_requests(occupied_);

  // take all references to requests without nullptr
  std::copy_if(buffer_.begin(), buffer_.end(), all_requests.begin(),
              [](Request_ptr const & request)
              { return (request != nullptr); });

  auto min = std::min_element(all_requests.begin(), all_requests.end(),
                  [] (Request_ptr const & left, Request_ptr const & right)
                  {
                    auto left_priority  = left->get_priority();
                    auto right_priority = right->get_priority();

                    // if sources of requests are not the same
                    if (left_priority != right_priority) {
                      return left_priority < right_priority;
                    }

                    // if sources of requests are the same
                    return left->get_number() < right->get_number();
                  });

  // now find in buffer a place of min request to release place
  for(auto it = buffer_.begin(); it != buffer_.end(); ++it) {
    if (*it == *min) {
      *it = nullptr;
    }
  }

  --occupied_;
  return *min;
}*/

Buffer::Request_ptr Buffer::get()
{
  // if no requests in buffer
  if (occupied_ == 0)
  {
    return nullptr;
  }

  // find first not empty place
  int min;
  for (int i = 0; ; ++i) {
    if (buffer_[i] != nullptr) {
      min = i;
      break;
    }
  }

  for(int i = (min + 1); i < buffer_.size(); ++i) {
      if (buffer_[i] == nullptr) {
        continue;
      }

      auto current_priority = buffer_[i]->get_priority();
      auto min_priority     = buffer_[min]->get_priority();

      // if priorities are not the same
      if (current_priority < min_priority) {
        min = i;
        continue;
      }

      // if priorities are the same
      if (current_priority == min_priority) {
        if (buffer_[i]->get_number() < buffer_[min]->get_number()) {
          min = i;
        }
      }

  } // end of min search

  Request_ptr request = buffer_[min];
  buffer_[min] = nullptr;
  --occupied_;

  return request;
}

