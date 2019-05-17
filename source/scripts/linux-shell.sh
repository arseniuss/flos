#!/bin/bash

# TODO
./source/scripts/ubuntu-setup.sh -verbose

. ./source/scripts/linux-setup.sh


    

env -i - \
    ROOT=\ \
    fakechroot fakeroot chroot $ROOT /bin/gnu/bash --rcfile /config/gnu/bash/rc.sh
