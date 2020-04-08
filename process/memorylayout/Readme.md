# C Program Memory Layout

## ASLR

To experiment with this program, it is better to disable the [Address Space Layout Randomization (ASLR)](https://en.wikipedia.org/wiki/Address_space_layout_randomization). 

### ASLR Setting
To examine current ASLR setting, we use either of the two methods, using the `sysctl` command, a preferred method; or viewing the content of a `/proc` file. 

#### Using `sysctl`
Issue the following command,
```
/usr/sbin/sysctl kernel.randomize_va_space
```
The output can be either 0, 1, or 2 while 0 means that the system does not use ASLR; otherwise, the system does use ASLR. 

#### Viewing `/proc` File Content
we view the content of file `/proc/sys/kernel/randomize_va_space` by issuing the following command,
```
cat /proc/sys/kernel/randomize_va_space
```
The output can be either 0, 1, or 2 while 0 means that the system does not use ASLR; otherwise, the system does use ASLR. 

### Disabling ASLR

We can turn off ASLR using the `systcl` command or changing the `/proc` file directly. 

#### Using `sysctl`
To disable ASLR temporarily on the Linux system using the `sysctl` command, issue the following command as root or using sudo,
```
/usr/sbin/sysctl -w kernel.randomize_va_space=0
```
where "temporarily" means that this setting won't survive a system  reboot. 

#### Using `/proc` Filesystem

To disable ASLR temporarily on the Linux system,  we can also directly change the content of the corresponding `/proc` file, i.e., run as root the following command,
```
echo 0 > /proc/sys/kernel/randomize_va_space
```
or if you have had `sudo` set up properly, you could also do the following without switching to root, and switching back to ordinary users. 
```
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```
where "temporarily" means that this setting won't survive a system  reboot. 

#### Surviving Reboot

To disable it permanently, i.e., to disable it and allow the setting to survive after a system reboot, we can place a configuration file in the `/etc/sysctl.d` directory, e.g., we run the `sysctl` command as root,
```
/usr/sbin/sysctl kernel.randomize_va_space > /etc/sysctl.d/01_disable_aslr.conf
```
or using `sudo`,
```
/usr/sbin/sysctl kernel.randomize_va_space | sudo tee /etc/sysctl.d/01_disable_aslr.conf
```

