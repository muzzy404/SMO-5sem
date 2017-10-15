#ifndef COUNTER_H
#define COUNTER_H


class Counter
{
private:
  static long rejected_;
  static long total_;

  static double buffer_time_;

public:

  static void add_to_rejected() { ++rejected_; }
  static void add_to_total()    { ++total_;    }

  static void add_to_buffer_time(const double delta) { buffer_time_ += delta; }

  static long get_rejected() { return rejected_; }
  static long get_total()    { return total_;    }
};

#endif // COUNTER_H
