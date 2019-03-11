# Multithread &pi; Estimator

This program estimates &pi; using a Monte Carlo simulation parallelized
via threads. 

- The version in this directory uses `random_r` for pseudo random number
generation. `random_r` is suitable for use in multithreaded programs where each
thread needs to obtain an independent, reproducible sequence of random numbers
- The version in [usingrandom](usingrandom) uses `random` for pseudo random
generation. Although Linux manual page claims that `random` isn't thread-safe,
`random` in Linux can be used in multithread programs where each thread needs
to obtain an independent, reproducible sequence of random numbers, which is the
result that in Linux `random` is made a synchronized function by using mutexe.
Because of this, this version runs much slower in Linux machine albeit 
producing correct result. 
- Both of the above two versions are written for Linux. The version in
[usinggsl](usinggsl] is a more portable version of the program since it 
uses the GNU Scientific Library (GSL) to generate pseudo random numbers and
the GSL library has been ported to most platforms. 

Of course, to be able to compile the version in the [usinggsl](usinggsl)
directory, we must install the GSL library.  

To install it on Debian Linux, we do,
```
apt-get install libgsl-dev
```


To install it on Open Solaris (or Open Indiana), we do,
```
pkg install gsl
```
In addition, we must also install the `gcc` compilier on Open Solaris 
(or Open Indiana), for which, we do,
```
pkg install build-essential
```


