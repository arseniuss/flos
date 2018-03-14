#!/bin/bash

if [ "$1" == "" ]; then
    echo "No architecture provided!"
    exit 1
fi

git clone https://github.com/travisg/toolchains ../gcc-cc
sudo apt install --yes \
    texinfo
    
gpg2 --keyserver hkp://keys.gnupg.net --recv-keys 4AE55E93
gpg2 --keyserver hkp://keys.gnupg.net --recv-keys C3C45C06
gpg2 --keyserver hkp://keys.gnupg.net --recv-keys FF325CF3
gpg2 --keyserver hkp://keys.gnupg.net --recv-keys 98C3739D
gpg2 --keyserver hkp://keys.gnupg.net --recv-keys 765C61E3
gpg2 --keyserver hkp://keys.gnupg.net --recv-keys 28C67298
cd ../gcc-cc && \
./updatetoolvers && \
./doit -f -a $1 -s -o ../../$1

