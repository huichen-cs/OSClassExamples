# Measuring TLB Misses for Huge Page Size

Note that you can only TLB  measurements on physical machines instead of
virtual machines.

Run the worker program with or without huage page allocation, and then
use the following to measure the TLB hits and misses 
```
sudo \
  perf stat \
  -e dTLB-loads,dTLB-load-misses,iTLB-loads,iTLB-load-misses -I 5000 \
  -p $(ps -u `whoami` | grep worker | head -1 | cut -d' ' -f1)
```


Use the following to count `clear_huge_page`
```
sudo \
  stap  \ 
  -e 'global huge_clear probe kernel.function("clear_huge_page").return {\
    huge_clear [execname(), pid()] <<<  \
    (gettimeofday_us() - @entry(gettimeofday_us()))}'
```


