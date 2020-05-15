# Measuring TLB Misses for Huge Page Size

Note that you can only TLB  measurements on physical machines instead of
virtual machines.

Run the worker program with or without huage page allocation, e.g.,
with huge page allocation, 

```
time LD_PRELOAD=/usr/lib/i386-linux-gnu/libhugetlbfs-2.20.so \
  HUGETLB_MORECORE=yes ./worker 2048 8
```

and without huge page allocation,

```
time ./worker 2048 8
```

Use the following to monitor huage page allocation
```
./queryhugepage.sh
```

Use the following to measure the TLB hits and misses 
```
sudo \
  perf stat \
  -e dTLB-loads,dTLB-load-misses,iTLB-loads,iTLB-load-misses -I 5000 \
  -p $(ps -A | grep "[[:space:]]worker$" | \
    head -1 | sed -E -e s/^[[:space:]]+//g | cut -d' ' -f1)
```


Use the following to count `clear_huge_page`
```
sudo \
  stap  \ 
  -e 'global huge_clear probe kernel.function("clear_huge_page").return {\
    huge_clear [execname(), pid()] <<<  \
    (gettimeofday_us() - @entry(gettimeofday_us()))}'
```



