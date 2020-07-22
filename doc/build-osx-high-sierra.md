# Mac OS X High Sierra Build Instructions and Notes

The commands in this guide should be executed in a Terminal application. The built-in one is located in /Applications/Utilities/Terminal.app.

## Preparation

Install the OS X command line tools:

```
xcode-select --install
```

When the popup appears, click Install.

Then install Homebrew from https://brew.sh

## Dependencies

```
brew install openssl berkeley-db4 miniupnpc
brew link --force berkeley-db4
brew upgrade openssl

brew install boost@1.55 --c++11 
brew link boost@1.55 --force
```

## Download LiteDoge Core

Clone the litedoge source code and cd into litedoge

```
git clone git@github.com:suchapp/litedoge.git && cd litedoge
```

## Optional: build and run headless litedoged daemon

Configure and build the headless litedoge binaries to verify that everything is working

```
cd src/

make -f makefile.osx-homebrew
```

### Running headless litedoged daemon

LiteDoge Core is now available at ./src/litedoged

Before running, it's recommended you create an RPC configuration file.

```
echo -e "rpcuser=litedogerpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/LiteDoge/litedoge.conf"

chmod 600 "/Users/${USER}/Library/Application Support/LiteDoge/litedoge.conf"
```

The first time you run litedoged, it will start downloading the blockchain. This process may take several days.

You can monitor the download process by looking at the debug.log file:

```
tail -f $HOME/Library/Application\ Support/LiteDoge/debug.log
```

Other commands:

```
./src/litedoged -daemon # Starts the bitcoin daemon.
./src/litedoged --help # Outputs a list of command-line options.
./src/litedoged help # Outputs a list of RPC commands when the daemon is running.
```

## Building the LiteDoge-QT app without QT Creator

Install dependencies using homebrew

```
brew install qt qrencode
```

Configure and build LiteDoge-QT
```
/usr/local/Cellar/qt/5.10.0_1/bin/qmake -config release litedoge-qt.pro "USE_UPNP=1" "USE_QRCODE=1" "RELEASE=1"

make -f Makefile 
```

Package LiteDoge in .dmg
```
sudo easy_install appscript

python2.7 contrib/macdeploy/macdeployqtplus LiteDoge-Qt.app -add-qt-tr da,de,es,hu,ru,uk,zh_CN,zh_TW -dmg -fancy contrib/macdeploy/fancy.plist -verbose 2
```

# Notes

Tested on macOS 10.13 High Sierra on 64-bit Intel processor only.

Original source: https://github.com/bitcoin/bitcoin/blob/master/doc/build-osx.md