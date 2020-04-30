#ifndef TIMER_H
#define TIMER_H

const size_t MAX_TIMEOUTS = 20;
const size_t MAX_INTERVALS = 20;


struct Timeout {
  void (*fn)();
  unsigned long runAtMillis;
};

struct Interval {
  void (*fn)();
  unsigned long runAtMillis;
  unsigned long interval;
};


class Timer
{
  private:
    Interval* intervals[MAX_INTERVALS];
    Timeout* timeouts[MAX_TIMEOUTS];

  public:
    Timer() {
    }

    size_t setTimeout(void (*fn)(), unsigned long timeout){
      for (size_t i = 0; i < MAX_TIMEOUTS; i++) {
        if (timeouts[i] == NULL) {
          timeouts[i] = new Timeout{
            fn,
            millis() + timeout
          };

          return i;
        }
      }
    }


    size_t setInterval(void (*fn)(), unsigned long interval){
      for (size_t i = 0; i < MAX_INTERVALS; i++) {
        if (intervals[i] == NULL) {
          intervals[i] = new Interval{
            fn,
            millis() + interval,
            interval
          };

          return i;
        }
      }
    }

    void clearTimeout(size_t id){
      delete timeouts[id];
      timeouts[id] = NULL;
    }

    void clearInterval(size_t id){
      delete intervals[id];
      intervals[id] = NULL;
    }

    void loop () {
      unsigned long currentMillis = millis();

      for (size_t i = 0; i < MAX_INTERVALS; i++) {
        if (intervals[i] != NULL) {
          if (intervals[i]->runAtMillis <= currentMillis) {
            intervals[i]->fn();
            intervals[i]->runAtMillis += intervals[i]->interval;
          }
        }
      }

      for (size_t i = 0; i < MAX_TIMEOUTS; i++) {
        if (timeouts[i] != NULL) {
          if (timeouts[i]->runAtMillis <= currentMillis) {
            timeouts[i]->fn();
            this->clearTimeout(i);
          }
        }
      }
    }

};

#endif
