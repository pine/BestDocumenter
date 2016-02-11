# BestDocumenter [![Build Status](https://travis-ci.org/pine613/BestDocumenter.svg?branch=master)](https://travis-ci.org/pine613/BestDocumenter)
Count your document contributions

## Requirements
### Mac OS X
First, you must install [Homebrew](http://brew.sh/).

```
$ brew install cmake curl gflags
```

### Ubuntu (14.04)
First, you must install gcc 5 or higher.

```
$ sudo add-apt-repository ppa:ubuntu-toolchain-r/test
$ sudo apt-get update
$ sudo apt-get install gcc-5 g++-5
```

And, please install dependency libs.

```
$ sudo apt-get install cmake libgflags-dev libcurl4-openssl-dev
```

## Build
### Mac OS X

```
$ cmake .
$ make
```

### Ubuntu (14.04)

```
$ CXX=/usr/bin/g++-5 cmake .
$ make
```

## Test
This project uses [Catch](https://github.com/philsquared/Catch) as test framework.

```
$ ./bin/best_documenter_test -s
```

## License
BSD License
