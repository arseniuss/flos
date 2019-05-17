#!/bin/bash

VERSION=8.0.0
RC=rc3
ARCH=x86_64
FLOS_ARCH=amd64
HOST=linux-gnu-ubuntu-18.04

wget -nc https://prereleases.llvm.org/$VERSION/$RC/clang+llvm-$VERSION-$RC-$ARCH-$HOST.tar.xz
rm -rf clang+llvm-$VERSION-$RC-$ARCH-$HOST
tar xf clang+llvm-$VERSION-$RC-$ARCH-$HOST.tar.xz
rm -rf ../../$FLOS_ARCH/clang+llvm-$VERSION
mkdir -p ../../$FLOS_ARCH/clang+llvm-$VERSION
cp -v -r ./clang+llvm-$VERSION-$RC-$ARCH-$HOST/* ../../$FLOS_ARCH/clang+llvm-$VERSION 
rm -rf clang+llvm-$VERSION-$RC-$ARCH-$HOST
