# Cluster


Running boot.sh at Boot on Raspberry Pi (Network-Ready)

This document explains how to automatically run your boot.sh script at boot time on a Raspberry Pi, ensuring the network is fully up before execution.

1. Prepare the boot.sh Script
Place your script in /home/username/nprolog/boot.sh with the following content:

sudo nano /home/username/nprolog/boot.sh

```
#!/bin/bash
# Change directory to 'nprolog'.
# If this fails (e.g., directory does not exist), exit immediately with status 1.
cd /home/username/nprolog || exit 1
# Run the 'npl' program with the '-n' option.
./npl -n
```


Make sure the script has execute permission:

```
sudo chmod +x /home/username/nprolog/boot.sh
```


2. Create a systemd Service for Network-Ready Boot Execution

Create the systemd service file /etc/systemd/system/npl.service

sudo nano /etc/systemd/system/npl.service

```
[Unit]
Description=Run N-Prolog at boot after network is ready
After=network-online.target
Wants=network-online.target

[Service]
ExecStart=/home/username/nprolog/boot.sh
WorkingDirectory=/home/username
User=usename
Restart=on-failure

[Install]
WantedBy=multi-user.target
```


Key points:

- After=network-online.target ensures the script runs after the network is up.

- Wants=network-online.target requests the network to be brought up before starting


## restore child 

```
git fetch origin
git reset --hard origin/master
```

## systemctl

```
systemctl enable npl.service

systemctl enable npl.service

```