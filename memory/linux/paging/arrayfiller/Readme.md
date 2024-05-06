# Experiment


1. run `setup.sh` or `setup2.sh` as root. `setup.sh` is tested on Debian 10 with cgroup v1 while `setup2.sh`
   is tested on Debian 12 with cgroup v2. For instance, Debian 12 with cgroup v2, run
```
sudo ./setup2.sh
```

2. Run `arrayfillerbyrow` via `cgexec`, e.g.,
```
sudo time cgexec -g memory:cisc3320arrayfilldemo ./arrayfillerbyrow
```



3. Run `arrayfillerbycolumn` via `cgexec`
```
sudo time cgexec -g memory:cisc3320arrayfilldemo ./arrayfillerbycolumn
```

4.  While the `arrayfillerbycolumn` is running, run  `showfaults.sh` to show
		page faults statistics.  Alternatively, you can simply use `ps -o
		min_flt,maj_flt PID` where `PID` is the process id of the
		`./arrayfillerbycolumn`.

