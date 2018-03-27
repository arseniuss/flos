#!/bin/bash

CMD=$@
FILEDIR=$(dirname $0)

source $FILEDIR/linux-setup.sh $1

if [ ! -z "$1" ]; then
    shift
    exec "$@"
fi


