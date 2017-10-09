#ifndef SOURCE_H
#define SOURCE_H


class Source
{
public:
  Source(const long);

  long get_priority() const { return priority_; }

  double delta_time()       const;
  double get_current_time() const { return current_time_; }

private:
  const long priority_;

  double current_time_;

};

#endif // SOURCE_H
