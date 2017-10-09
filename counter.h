#ifndef COUNTER_H
#define COUNTER_H


class Counter
{
private:
  static long rejected_;
  static long total_;

public:

  static void add_to_rejected() { ++rejected_; }
  static void add_to_total() { ++total_; }

  static long get_rejected() { return rejected_; }
  static long get_total() { return total_; }

};

#endif // COUNTER_H
