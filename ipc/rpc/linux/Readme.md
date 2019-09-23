# Remote Procedure Call

This is the example provided in the Linux Journal article
- [Remote Procedure Calls](https://www.linuxjournal.com/article/2204)


## File Listing

- [avg.x](avg.x). This file defines the RPC protocol. 
- [avg_proc.c](avg_proc.c). This is part of the server or the callee
- [ravg.c](ravg.c). This is part of the client or the caller.
- [Makefile](Makefile). 

## Compilation 

### Compiling the RPC Protocol
```
rpcgen avg.x
```

The output are 4 files:
- avg.h.
- avg_xdr.c.  The XDR routines used by both the client and the server.
- avg_clnt.c. The stub program for the client (caller).
- avg_svc.c.  The main program for the server (callee).

### Compiling the XDR Routines
Both the client (the caller) and the server (the callee) share the
XDR routines in avg_xdr.c. 
```
cc -c -o avg_xdr.o avg_xdr.c
```

### Compiling the Client (or Caller)
```
cc -c -o ravg.o ravg.c 
cc -c -o avg_clnt.o avg_clnt.c
cc -o ravg ravg.o avg_clnt.o avg_xdr.o
```

### Compiling the Server (or Callee)
```
cc -c -o avg_proc.o avg_proc.c
cc -c -o avg_svc.o avg_svc.c
cc -o avg_svc avg_proc.o avg_svc.o avg_xdr.o
```

### Makefile
We define the compilation procedures in the [Makefile](Makefile). For the impatient, run `make` to compile this example.

## Running the Programs
We need to run the server (the callee) first, and run the client (the caller)
second; however, we must ensure we have had the `rpcbind` package installed. 

### Installing the `rpcbind` Package
```
sudo apt-get install rpcbind
```

### Running the Server (the Callee)

```
avg_svc &
```

### Quering Server Status
We can query the server status, e.g., 
```
/usr/sbin/rpcinfo -p localhost
```
or
```
/usr/sbin/rpcinfo
```
The output includes lines like
```
program version netid     address                service    owner
22855    1      udp       0.0.0.0.214.175        -          unknown
22855    1      tcp       0.0.0.0.223.49         -          unknown
```
We notice that the program number "22855" is identical to what we specified
in [avg.x](avg.x).


### Running the Client (the Caller)
```
./ravg localhost 1 2 3
```

## RPC Service Maintenance

### Killing the RPC Service Process (the Callee)
We can use the kill command to terminate the RPC service process, such as, 
if the service process id is 12345, we do
```
kill 12345
```
Alternatively, we can use the killall command to terminate the services
matching the program name, i.e., 
```
killall avg_svc
```

### Unregistering RPC Service
A RPC service registration remains in the system unless explicitly removed
even if we terminate the process that associate with it. Observe the
following commands and outputs:
```
$ ./avg_svc &
[1] 4153
$ ./ravg localhost 1 2 3
value   = 1.000000e+00
value   = 2.000000e+00
value   = 3.000000e+00
average = 2.000000e+00
$ killall avg_svc
$ /usr/sbin/rpcinfo
   program version netid     address                service    owner
     22855    1    udp       0.0.0.0.164.39         -          unknown
     22855    1    tcp       0.0.0.0.178.39         -          unknown
$ ./ravg localhost 1 2 3
value   = 1.000000e+00
value   = 2.000000e+00
value   = 3.000000e+00
call failed:: RPC: Unable to receive; errno = Connection refused
Segmentation fault
$
```

To unregistering the RPC service, we do
```
sudo /usr/sbin/rpcinfo -d 22855 1 
```

Notice if we run the client program again, we observe a different 
error message, such as, 
```
$ ./ravg localhost 1 2 3
value   = 1.000000e+00
value   = 2.000000e+00
value   = 3.000000e+00
localhost: RPC: Program not registered
$
```

If we run the `rpcinfo` command again, we shall see the RPC serve is 
no long appear in the registered RPC service list. 



