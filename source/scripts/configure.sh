#!/bin/bash

#
#
#

[ -z "$TARGETOS" ] && TARGETOS=`uname`
[ -z "$TARGETARCH" ] && TARGETARCH=`uname -m`
[ -z "$HOSTOS" ] && HOSTOS=`uname`
[ -z "$HOSTARCH" ] && HOSTARCH=`uname -m`

[ -z "$ROOT" ] && ROOT=../..

[ "$TAREGETARCH" == "x86_64" ] && TARGETARCH=amd64
[ "$HOSTARCH" == "x86_64" ] && TARGETARCH=amd64

#
#
#

USEGCCCC=no

while getopts h?-: arg; do
    case $arg in
        h | \? ) help ;;
        - ) LONGOPTARG="${OPTARG#*=}"
            case $OPTARG in
                help ) help ;;
                gcc-cc ) USEGCCCC="yes" ;;
                '' )        break ;; # "--" terminates argument processing
                * )         echo "$0 illegal option -- $OPTARG" >&2 ;;
            esac ;;
    esac
done
shift $((OPTIND-1)) # remove parsed options and args from $@ list


#
#
#

REQUIRED_TOOLS=(
    "AR ar" 
    "AS as" 
    "CC gcc" 
    "OBJDUMP objdump" 
    "LD ld"
    "PP cpp"
    "CPP g++"
)

function add-config() {
    echo "$@" >> config.mk
}

function add-tool-config() {
    for tool in "${REQUIRED_TOOLS[@]}"
    do
        TOOL=($tool)
        
        if [ ! -f "$1/${TOOL[1]}" ]; then
            echo "Tool ${TOOL[1]} not found!" >&2
            exit 1
        else
            add-config "${TOOL[0]}=$1/${TOOL[1]}"
        fi
    done
}

rm -f config.mk

if [ "$USEGCCCC" == "yes" ]; then
    if [ -d "../gcc-cc" ]; then
        . ../gcc-cc/toolvers

        case $ARCH in
        arm) TARGET=$ARCH-eabi ;;
        *) TARGET=$ARCH-elf ;;
        esac
        
        TOOLDIR=$ROOT/$ARCH/$TARGET-$GCCVER-$HOSTOS-$HOSTARCH
        
        if [ -d "$TOOLDIR" ]; then
            TOOLDIR=`readlink -e $TOOLDIR`
            
            add-tool-config "$TOOLDIR/bin/$TARGET/bin"
        else
            echo "GCC cross-compiler not found! ($TOOLDIR)"
            exit 1
        fi
    else
        echo "unimplemented: outside source tree"
        exit 1
    fi
else
    TOOLDIR="/usr/bin"
    
    add-tool-config "$TOOLDIR"
fi

if [ -f "$ROOT/flos.info" ]; then
    add-config "ROOT=$ROOT"
    add-config "CFLAGS=-I$ROOT/include"
fi

echo -e "\nindent:\n\tindent \$(SRCS) \$(HDRS)\n\n" >> config.mk
echo -e "\ndistclean::\n\trm config.mk\n\n" >> config.mk
echo -e "\n.PHONY: indent distclean\n\n" >> config.mk
