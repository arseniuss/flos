#!/bin/bash

unset ROOT
unset ARCH
unset OS

# exports ROOT as ../.. from current script
export ROOT=$(readlink -f $(dirname `readlink -f ${BASH_SOURCE[0]}`)/../..)

echo ROOT is $ROOT

[ ! -z "$1" ] && ARCH=$1 || ARCH=`uname -m`

case $ARCH in
        x86_64|amd64 ) export ARCH=amd64 ;;
        x86|i386 ) export ARCH=x86 ;;
        aarch64|arm64 ) export ARCH=arm64 ;;
        everything|any) unset ARCH ;;
        * ) echo Unknown architecture!; exit 1 ;;
    esac
    
    
export OS=flos
export HOST=gnu-linux
    
echo ARCH is $ARCH
echo OS is $OS
echo HOST is $HOST
echo ========================================
