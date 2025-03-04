#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
  struct timeval tv;
  int ret;

  ret = gettimeofday(&tv);
  if(ret < 0) {
    printf(2, "gettimeofday failed\n");
    exit();
  }
  
  printf(1, "Seconds: %d, Microseconds: %d\n", tv.tv_sec, tv.tv_usec);
  exit();
}
