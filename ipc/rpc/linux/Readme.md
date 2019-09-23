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

