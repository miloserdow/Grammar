[![Build Status](https://travis-ci.org/miloserdow/Grammar.svg?branch=master)](https://travis-ci.org/miloserdow/Grammar)

# What's this?
This is my homework in formal languages. You can find here 3 algos including GLL/GLR.
Project uses *CMake* for build automation and *googletest framework* for testing.

# How to build it?
1. Clone this repository
```bash
$ git clone git@github.com:miloserdow/Grammar
```
2. Change directory to downloaded repository directory
```bash
cd Grammar
```
3. Make sure you have **make**, **cmake** *(>= 3.5.1)* and **g++** *(>= 4.9)*
4. Run build script
```bash
$ chmod +x runit.sh
$ ./runit.sh
```
Script should create *build* directory, configure and build project there. Then it shoud run all the unit tests.

# How to manually build it?
If you don't like my script for some reason you may consider building it all by hands, it's not hard, really ;)
Just create directory inside repository and run cmake inside it:
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
make
```

# How to manually run it?
Inside build directory:
```bash
./Grammar ../test/grammars/Grammar1.dot ../test/graphs/skos.dot res.dat
```
Then program will ask your input to select algorithm to run. Please be aware that *MatrixSolver* does not support Graphvis input *(.dot files)* for grammars.

# Do I really need to build it?
If you just want to check if tests are passing, you can always refer to Travis (continious integration platform). You can access last build log (with testing protocol) by clicking icon on top of this readme file or via this link: https://travis-ci.org/miloserdow/Grammar
Travis config is in .travis.yml file in this repository
