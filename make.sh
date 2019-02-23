#!/usr/bin/env bash

set -e
SELF_DIR="$(dirname $(readlink -f $0))"
cd "$SELF_DIR"

function set_flag() {
    local append=false

    if [[ "$1" == "--append" ]]; then
        shift
        append=true
    fi

    local var="$1"; shift
    declare -n ref="$var" 
    if [[ "$ref" == "" ]]; then
        ref="$@"
    elif [[ "$append" == true ]]; then
        ref="$ref $@"
    fi
}

COMMON_FLAGS="-I$CS_DEV_PATH/include -I../include -fPIC -O3"
DEFAULT_CXXFLAGS="-std=c++14 -shared -s $COMMON_FLAGS"
DEFAULT_CFLAGS="$COMMON_FLAGS"
DEFAULT_LDFLAGS="-L$CS_DEV_PATH/lib -lcovscript -lpthread"
DEFAULT_CXX=g++
DEFAULT_CC=gcc

set_flag CC $DEFAULT_CC
set_flag CXX $DEFAULT_CXX
set_flag --append CFLAGS $DEFAULT_CFLAGS
set_flag --append CXXFLAGS $DEFAULT_CXXFLAGS
set_flag --append LDFLAGS $DEFAULT_LDFLAGS

while [[ "$1"x != ""x ]]; do
    arg="$1"; shift
    case "$arg" in
        --cxxflags=* ) CXXFLAGS="${arg##--cxxflags=}" ;;
        --ldflags=* ) LDFLAGS="${arg##--ldflags=}" ;;
        "--" ) break ;;
    esac
done

mkdir -p build
cd build
mkdir -p imports
$CC $CFLAGS -c ../sqlite3.c
$CXX $CXXFLAGS ../sqlite.cpp ./sqlite3.o $LDFLAGS -o ./imports/sqlite.cse
rm ./sqlite3.o