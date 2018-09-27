#!/bin/bash

# TODO
./source/scripts/ubuntu-setup.sh -verbose

. ./source/scripts/linux-setup.sh

env -i - \
    ROOT=\ \
    fakechroot chroot $ROOT /bin/gnu/bash --rcfile /config/gnu/bash/rc.sh
