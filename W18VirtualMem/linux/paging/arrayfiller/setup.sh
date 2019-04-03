#!/bin/bash

# check OS
grep -q "Debian GNU/Linux" /etc/os-release > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo ">>>> This script is only tested on Debian Linux." 
    echo ">>>> You may revise this script to run on other Linux distributions."
    echo ">>>> Exiting for now  ..."
    exit 1
fi
name=`grep PRETTY_NAME /etc/os-release | sed -e 's/^[[:space:]]*PRETTY_NAME[[:space:]]*=[[:space:]]*\"\(.*\)\"/\1/'`
echo ">>>> You are on a ${name} system."

# install cgroup-tools
which cgcreate > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo ">>>> Install the cgroup-tools package ..."
    apt-get -y install cgroup-tools 
    if [ $? -ne 0 ]; then
        echo ">>>> Failed to install cgroup-tools. "
        echo ">>>> Are you running this as root? "
        echo ">>>> Exiting ..."
        exit 1
    fi
fi
echo ">>>> The cgroup-tools is installed."

# enable cgroup memory controller and swap accounting
if [ ! -f /etc/default/grub ]; then
    echo ">>>> File /etc/default/grup is not accessiable."
    echo ">>>> Exiting ..."
    exit 1
fi
line=`grep GRUB_CMDLINE_LINUX_DEFAULT /etc/default/grub`
echo ${line} | grep -q "cgroup_enable=memory swapaccount=1"
if [ $? -ne 0 ]; then
    value=`echo ${line} | sed 's/^.*grub_cmdline_linux_default[[:space:]]*=[[:space:]]*\"\(.*\)\"/\1/'`
    newline="grub_cmdline_linux_default=\"${value} cgroup_enable=memory swapaccount=1\""
    echo ">>>> the line in /etc/default/grub:"
    echo ">>>>    ${line}"
    echo ">>>> is to be replaced by "
    echo ">>>>    ${newline}"
    echo ">>>> enter y to confirm, n to give up. y/n?"
    while read answer; do
        if [ "x${answer}" == "xy" -o "x${answer}" == "xn" ]; then
            break
        fi
        echo ">>>> enter y to confirm, n to give up. y/n?"
    done
    if [ ${answer} == "N" ]; then
        echo ">>>> You chose to give up. Exiting ..."
        exit 1
    fi
    backupfn=/etc/default/grub.bu.`date +%Y%m%d%H%M%S`
    cp /etc/default/grub ${backupfn}
    if [ $? -ne 0 ]; then
        echo ">>>> Failed to backup /etc/default/grub to ${backupfn}"
        echo ">>>> Exiting ..."
        exit 1
    fi
    sed -i -e "s/${line}/${newline}/" /etc/default/grub
    if [ $? -ne 0 ]; then
        echo ">>>> Failed to update /etc/default/grub."
        echo ">>>> Exiting ..."
        exit 1
    fi
fi
echo ">>>> The cgroup memory controller and swap accounting are enabled."

/usr/sbin/update-grub
if [ $? -ne 0 ]; then
    echo ">>>> Failed to update grub config."
    echo ">>>> Are you running this as root?"
    exit 1
fi
echo ">>>> Updated grub config".

cat >> /etc/cgconfig.conf << END
group app/arrowfillerdemo {
  memory {
    memory.limit_in_bytes = 500000000;
  }
}
END

cat >> /etc/cgrules.conf << END
    *:arrayfillbycolumn       memory      app/arrowfillerdemo/
    *:arrayfillbyrow          memory      app/arrowfillerdemo/
END

cgconfigparser -l /etc/cgconfig.conf
cgrulesengd

cat /proc/`pidof arrayfillbycolumn`/cgroup | grep app

smem -P arrayfillbycolumn


#cgcreate -g memory:/cisc3320arrayfilldemo
#echo $(( 64 * 4 * 1024 )) > /sys/fs/cgroup/memory/cisc3320arrayfilldemo/memory.limit_in_bytes
#echo $(( 128 * 1024 * 1024 )) > /sys/fs/cgroup/memory/cisc3320arrayfilldemo/memory.memsw.limit_in_bytes

#cgexec -g memory:cisc3320arrayfilldemo arrayfillerbycolumn
