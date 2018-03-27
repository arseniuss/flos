#!/bin/bash

unset ROOT
unset ARCH

# exports ROOT as ../.. from current script
export ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../.." && pwd )"

echo ROOT is $ROOT

if [ ! -z "$1" ]; then 
    case $1 in
        amd64|x86_64 ) export ARCH=amd64 ;;
        arm64|aarch64 ) export ARCH=arm64 ;;
        * ) echo Unknown architecture $1; exit 1 ;;
    esac
else
    ARCH=`uname -m`
    case $ARCH in
        x86_64 ) export ARCH=amd64 ;;
        * ) echo Unknown architecture!; exit 1 ;;
    esac
fi

echo ARCH is $ARCH
