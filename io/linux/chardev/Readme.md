# Building a Linux Driver

This is a simple character device driver appearing in
[LKMPG](https://code.freedombone.net/bashrc/LKMPG/).

## Preparing Environment

We use Debian Linux. In Debian Linux, install necessary packages by issuing
the command

```sh
sudo apt-get install build-essentials kmod linux-headers-$(uname -r)
```

## Building the Driver Module

The driver is a Linux kernel module. To compile, use make

```sh
make
```

## Loading the Driver Module

Use `insmod` to load the driver module, i.e., as root, run the following

```sh
insmod chardev.ko
```

To verify that we load the driver module successfully, use `lsmod` to
list loaded kernel modules

```sh
lsmod | grep chardev
```

The output should resemble the following,

```text
chardev                16384  0
```

In addition, we should also examine the system log file `/var/log/message`, for
which, run the following as root,

```sh
tail /var/log/messages
```

The output should include the following

```text
Dec  2 11:53:54 debian10 kernel: [ 1562.269831] chardev: loading out-of-tree
 module taints kernel.
Dec  2 11:53:54 debian10 kernel: [ 1562.270028] chardev: module verification
 failed: signature and/or required key missing - tainting kernel
Dec  2 11:53:54 debian10 kernel: [ 1562.270240] I was assigned major number
 246.
Dec  2 11:53:54 debian10 kernel: [ 1562.270270] Device created on /dev/chardev
```

The above output suggests that the system created the device at `/dev/chardev`.
We can verity this by listing the file as in,

```sh
ls -l /dev/chardev
```

The output should be similar to

```text
crw------- 1 root root 246, 0 Dec  2 11:53 /dev/chardev
```

## Client Program

We include a client program that accesses the device via its
device driver. Run the program as root,

```sh
./accesschardev
```

## Removing Driver Module

Use `rmmod` to remote the module, i.e., run the following as root,

```sh
rmmod chardev
```
