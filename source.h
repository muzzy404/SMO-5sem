#ifndef SOURCE_H
#define SOURCE_H


class Source
{
public:
  Source();

  int get_delta_time() const;

private:
  int current_time_;

};

#endif // SOURCE_H
