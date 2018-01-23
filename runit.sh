#!/bin/bash

export CXX="g++"
export CXX_FLAGS="-w -pedantic -Werror"
export CMAKE_OPTIONS="-DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON"
export BUILD_DIR="./build"

function program_is_installed {
  local return_=1
  type $1 >/dev/null 2>&1 || { local return_=0; }
  echo "$return_"
}

function err {
  echo $1;
  exit 1;
}

if [ $( program_is_installed ${CXX} ) -eq 0 ]; then
  err 'Please install GNU GCC v. 4.9+ (deb package g++-4.9)'
fi

cur=$( ${CXX} -dumpversion )
req="4.9"
if [ "$(printf '%s\n' "$req" "$cur" | sort -V | head -n1)" != "$req" ]; then
  err 'Your GNU GCC is too old, regular expressions will not work properly, please upgrade to 4.9+ (deb package >= g++.4.9)'
fi

if [ $( program_is_installed "make" ) -eq 0 ]; then
  err 'Please install make (deb package ...)'
fi

if [ $( program_is_installed "cmake" ) -eq 0 ]; then
  err 'Please install cmake (deb package cmake)'
fi

if [ $( program_is_installed "perl" ) -ne 0 ]; then
  cur=$( cmake --version | perl -pe '($_)=/([0-9]+([.][0-9]+)+)/' ) ;
  req="3.5.1";
  if [ "$(printf '%s\n' "$req" "$cur" | sort -V | head -n1)" != "$req" ]; then
    err 'Please upgrade CMake to 3.5.1+ (deb package cmake)'
  fi
fi

if [ -d ${BUILD_DIR} ]; then
  rm -rf ${BUILD_DIR}
fi

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

cmake .. ${CMAKE_OPTIONS} || err "Error configuring cmake project"
make || err "Error building project"

echo "BUILD SUCCEEDED"
echo "Running tests now..." && ./runUnitTests
