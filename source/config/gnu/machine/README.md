# Supported machines

This directory contains make confguration files for supported machines.
File naming is: `{name}-{version}.{ext}`,
where:

 - name: name of product
 - version: product version or `generic` if it's possible to compile universal version
 - ext: configuration file extension; `mk` is for GNU make

## Useful information

 1. _clang_ suported processor types and features can be find with command `llc -mtriple=arm-none-eabi -mcpu=help
`