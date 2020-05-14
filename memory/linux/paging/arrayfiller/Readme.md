# Experiment

1. run `setup.sh` as root, e.g.,
```
sudo ./setup.sh
```

2. Run `arrayfillerbyrow` via `cgexec`, e.g.,
```
sudo time cgexec -g memory:cisc3320arrayfilldemo ./arrayfillerbyrow
```



3. Run `arrayfillerbycolumn` via `cgexec`
```
sudo time cgexec -g memory:cisc3320arrayfilldemo ./arrayfillerbycolumn
```

4.  While the `arrayfillerbycolumn` is running, run  `showfaults.sh`
