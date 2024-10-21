# GCC Documentation

To install GCC documentation on Debian Linux 10, do,

```sh
echo deb \
  http://deb.debian.org/debian buster-backports main contrib non-free | \
  sudo tee /etc/apt/sources.list.d/buster-backports.list
sudo apt update
sudo apt install -t buster-backports gcc-doc
```
