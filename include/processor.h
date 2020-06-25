#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();

 private:
  long previous_active{0};
  long previous_total{0};
};

#endif