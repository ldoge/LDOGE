# LiteDoge full-node copy-paste installation guide

Copy-paste unix commands to run a full litedoge node and start staking. 

## Server and operating system

Litedoge runs on any unix or bsd server. Even Raspberry PI. In this guide I'll focus on Ubuntu 16.04 running on cloud server.

Here are few host providers who offer cheap virtual private servers (vps) for international customers:

- https://www.hetzner.com/virtual-server
- https://contabo.com/?show=vps
- https://aws.amazon.com/ec2/ 

## Update server and install dependencies

Log in as root to your server:

```
ssh root@server-ip-address
```

or

```
sudo su -
```

Update the OS:

```
apt update -qqy --fix-missing \
	&& apt-get upgrade -y \
	&& apt-get clean -y \
	&& apt-get autoremove -y --purge
```

Install dependencies:

```
apt install build-essential -y \
	&& apt install libssl-dev -y \
	&& apt install libdb++-dev -y \
	&& apt install libboost-all-dev -y \
	&& apt install libminiupnpc-dev -y \
	&& apt install git -y
```

## Create user

You don't want start litedoge node with the root user. Create user `litedoge` without log-in rights.

```
sudo useradd -s /usr/sbin/nologin -m litedoge
```

## Download and build litedoge

Clone the updated litedoge repository:

```
cd /home/litedoge && git clone https://github.com/vashshawn/LDOGE litedoge

sudo chown -R litedoge:litedoge litedoge  
```

Build it with command:

```
cd /home/litedoge/litedoge/src && sudo -u litedoge make -f makefile.unix
```

### Build issues

Commands above cloned the original LDOGE repository. If you have problems building it, clone this repository using command `cd /home/litedoge && git clone https://github.com/suchapp/litedoge` and try building it again. 

## Linking 

Move litedoged to path:

```
cp /home/litedoge/litedoge/src/litedoged /bin/litedoged
```

## Configure litedoged

Create the config directory:

```
sudo -u litedoge mkdir /home/litedoge/.litedoge
```

Create the config file `litedoge.conf`

Note: you need to add strong `rpcpassword` before copy-pasting this:

```
cat << "EOF" | sudo tee /home/litedoge/.litedoge/litedoge.conf

addnode=23.152.0.212
addnode=167.160.36.7
addnode=198.245.50.213
addnode=85.24.143.58
addnode=176.9.140.80
addnode=85.169.119.40
addnode=50.142.213.254
addnode=192.52.167.158
addnode=45.50.58.160
addnode=24.76.220.10
addnode=174.102.232.161
addnode=82.44.44.253
addnode=68.36.216.167
addnode=76.18.225.234
addnode=98.193.5.149
addnode=173.68.191.206
addnode=24.44.96.51
addnode=86.205.155.158
# addnode=192.169.7.131
# addnode=167.160.36.13
# addnode=74.118.157.122
# addnode=167.160.36.9
# addnode=185.69.55.165
# addnode=72.241.235.204

# If you get too many errors in initial sync, try limiting maxconnections to 3
#maxconnections=3

# Release your LDOGEs by setting staking=0 or reservebalance to needed amount
#reservebalance=99999999999
staking=1
stake=1

daemon=1
server=1
rpcuser=litedogerpc
rpcpassword=
rpcallowip=127.0.0.1
rpcport=9332

txindex=1

EOF
```

## Optional: Bootstrap blockchain

You can download the blockchain to make initial sync faster. You'll find it from bitcointalk's litedoge threads or discord chat.

If `bootstrap.zip` is not available, just skip this step. Initial sync will take few days.

## Create systemd service to start litedoge automatically

We want our node to start automatically after a reboot or crash. Create a systemd service for it.

```
cat << "EOF" | sudo tee /lib/systemd/system/litedoge.service
[Unit]
Description=Litedoge daemon
After=network.target

[Service]
ExecStart=/bin/litedoged -datadir=/home/litedoge/.litedoge
WorkingDirectory=/home/litedoge/.litedoge
Type=forking
User=litedoge
Restart=on-failure
PrivateTmp=true
PrivateDevices=yes
ProtectSystem=full
SyslogIdentifier=LDOGE
RestartSec=30

[Install]
WantedBy=multi-user.target
Alias=litedoge.service

EOF
```

Enable the service:

```
systemctl daemon-reload && sudo systemctl enable litedoge.service
```

Every time you change something in `/lib/systemd/system/litedoge.service`, you need to run `systemctl daemon-reload`.

## Start the service

```
service litedoge start
```

Since we have created an alias for the service, we will be able to work with it in the future as follows:

```
service litedoge start|stop|restart|status
```

## Create `ldoge` run script for daemon

```
cat << "EOF" | sudo tee /bin/ldoge

/bin/litedoged -datadir=/home/litedoge/.litedoge "$@"

EOF
```

Chmod 

```
chmod a+x /bin/ldoge
```

## Show litedoged status

```
ldoge getinfo
```

## Follow litedoged logs

```
tail -f /home/litedoge/.litedoge/debug.log
```

## Backup wallet.dat

First encrypt your wallet:

```
ldoge encryptwallet your-strong-password-here

service litedoge restart
```

Then copy `/home/litedoge/.litedoge/wallet.dat` and store it somewhere safe.

## Wait for sync to complete

While waiting for sync to complete, read more about LiteDoge at:

Official website: http://www.ldoge.tech/

Reddit: https://reddit.com/r/litedoge

Discord: https://discord.gg/BX9XVMS

Bitcointalk thread 1: https://bitcointalk.org/index.php?topic=1077390.0

Bitcointalk thread 2: https://bitcointalk.org/index.php?topic=1308769.0

Original repository and development guide: https://github.com/vashshawn/LDOGE

and 

```
ldoge help
```

## Receive LDOGE

When blockchain is fully synced, use ´getnewaddress´ to get a new LDOGE address:

```
ldoge getnewaddress
```

command returns address-hash like `dJ68iVea94kWWgR4DFStwMnUzZUs4uVDhS`. Send your LDOGEs to your address.

Wait few seconds and check your balance:

```
ldoge getbalance
```

## Start staking

Unlock wallet for staking

```
ldoge walletpassphrase your-strong-password-here 99999999 true
```

Check staking status

```
ldoge getstakinginfo

ldoge getmininginfo
```

## Send LDOGE

Move staking profits back to other wallet (replace hash with your address):

```
ldoge walletpassphrase your-strong-password-here 99999999

ldoge sendtoaddress dJ68iVea94kWWgR4DFStwMnUzZUs4uVDhS amount-ldoge-to-send
```

## Thanks

If you found this guide useful, please consider sending some LDOGE to `dJ68iVea94kWWgR4DFStwMnUzZUs4uVDhS`. 

Send message to https://www.reddit.com/u/suchapp if you have ideas how to improve this guide!

Thanks for staking litedoge! 
