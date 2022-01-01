#!/bin/sh
# Needs root
if [ `id -u` != 0 ] ; then
	echo "Need root!"
	exit
fi

SCRIPT=$(readlink -f "$0")
SCRIPTPATH=$(dirname "$SCRIPT")

if [ $# -gt 0 ]; then
    FILE="$1"
    shift
    if [ -f "$FILE" ]; then
        INFO="$(head -n 1 "$FILE")"
    fi
else
    echo "Usage: $0 <filename>"
    exit 1
fi

if [ -e "$(which git)" ]; then
    # clean 'dirty' status of touched files that haven't been modified
    git diff >/dev/null 2>/dev/null 

    # get a string like "v0.6.0-66-g59887e8-dirty"
    DESC="$(git describe --dirty 2>/dev/null)"

    # get a string like "2012-04-10 16:27:19 +0200"
    TIME="$(git log -n 1 --format="%ci")"
fi

if [ -n "$DESC" ]; then
    NEWINFO="#define BUILD_DESC \"$DESC\""
else
    NEWINFO="// No build information available"
fi

# only update build.h if necessary
if [ "$INFO" != "$NEWINFO" ]; then
    echo "$NEWINFO" >"$FILE"
    echo "#define BUILD_DATE \"$TIME\"" >>"$FILE"
fi

# Dependencies
apt-get update || exit
apt-get install -y gcc g++ autoconf libtool libboost-all-dev pkg-config make libminiupnpc-dev || exit
# Can't find libdb 4.8 in debian repos
dpkg -i $SCRIPTPATH/libdb4.8_4.8.24-1ubuntu1_i386.deb || exit
dpkg -i $SCRIPTPATH/libdb4.8-dev_4.8.24-1ubuntu1_i386.deb || exit
dpkg -i $SCRIPTPATH/libdb4.8++_4.8.24-1ubuntu1_i386.deb || exit
dpkg -i $SCRIPTPATH/libdb4.8++-dev_4.8.24-1ubuntu1_i386.deb || exit

git clone https://github.com/ldoge/LDOGE.git
cd litedoge
./autogen.sh
./configure
make
