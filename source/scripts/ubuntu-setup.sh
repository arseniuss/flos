

function install-link() {
    #REWRITE
    
    # whereis gives location of programs
    # dpkg -S on first location gives package name to install 
}

function install-program() {
    local pkg=$1
    local prog=$2
    local name=$3
    
    command -v $prog &> /dev/null
    if [ ! $? -eq 0 ]; then
    
        sudo apt install -y $pkg
        if [ $? -eq 0 ]; then
            
            command -v $prog &> /dev/null
            if [ ! $? -eq 0 ]; then
                echo "Required program $prog don't exist!"
                exit 1
            fi
        
            install-link $prog $name
        fi
    else
        install-link $prog $name
    fi
}

if [[ "$1" == "-verbose" ]]; then
    verbose=1
fi

if [ $verbose ]; then
    echo "This script setups environment variables for Ubuntu distribution"
    echo
fi

#               package      program            link name
install-program clang-5.0    clang-5.0          clang
install-program lld-6.0      ld.lld-6.0         ld
install-program binutils     as                 as
install-program llvm-5.0     llvm-objdump-5.0   objdump
install-program binutils     cpp                cp
install-program coreutils    mkdir              mkdir
install-program coreutils    rm                 rm
install-program bash         bash               bash
install-program fakechroot   fakechroot         fakechroot
install-program coreutils    ls                 ls
install-program gcc          gcc                gcc
