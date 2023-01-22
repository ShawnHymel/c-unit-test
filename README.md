# C/C++ Unit Test Demo with CppUTest

This repository is a simple template that demonstrates how to construct automated unit tests with [CppUTest](http://cpputest.github.io/). A full written tutorial with video on using this repository can be [found here](https://www.digikey.com/en/maker/projects/writing-cc-unit-tests-with-cpputest/7776121323b74ae7b20725cf06163537).

Contents:
 * *.github/workflows* - GitHub Actions workflows for automatically running tests
 * *src/* - Source code and component (*average/*) for building the demo application
 * *tests/* - Unit tests for the component (*average/*)
 * *Dockerfile* - Creates a Docker image that automatically runs all unit tests with CppUTest
 * *Makefile* - For building the application or running the unit tests

Note that directions below are given for Debian-based Linux flavors (e.g. Ubuntu). They should work in macOS, but you will probably need to install dependencies via [Homebrew](https://brew.sh/) instead of *apt*. If you are on Windows, I recommend installing [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) with an Ubuntu image.

## Build Application

Make sure you have the following installed:

```
sudo apt update
sudo apt install -y build-essential
```

To build and run the application, clone this repository and navigate to this directory in a terminal. Run the following:

```
make
./app.elf
```

You should see an output showing that the average of the array is `1.00000`.

## Run Tests Locally

To run the unit tests locally, you will need to first download and build CppUTest. From this directory, run:

```
sudo apt install autoconf automake libtool
mkdir tools
wget https://github.com/cpputest/cpputest/releases/download/v4.0/cpputest-4.0.tar.gz
tar xf cpputest-4.0.tar.gz
mv cpputest-4.0/ tools/cpputest/
cd tools/cpputest/
autoreconf -i
./configure
make
cd ../..
```

Then, we can run the unit tests using CppUTest with:

```
make test
```

You should see the CppUTest output log that looks something like:

```
Running average_tests
..
OK (2 tests, 2 ran, 2 checks, 0 ignored, 0 filtered out, 0 ms)
```

Clean up the tests with:

```
make test_clean
```

## Run Tests in Docker Image

If you don't want to install CppUTest on your host machine, you can run the tests inside of a Docker container. First, make sure that you have [Docker Desktop](https://www.docker.com/) installed. From this directory, run:

```
docker build -t unit-tests-image -f Dockerfile .
docker run --rm unit-tests-image
```

You should see the output of the Docker container with the CppUTest log:

```
Running average_tests
..
OK (2 tests, 2 ran, 2 checks, 0 ignored, 0 filtered out, 0 ms)
```

## Run Tests with GitHub Actions

To see the fully automated procedure of running these tests inside of a GitHub Actions workflow, simply fork this repository, clone it, and check in some trivial new code. Go to the Actions tab in your version of the repository, and you should see the workflow in action (which simply constructs and runs the Docker image described above).

## Adding a New Component

Create your component's .c and .h files under a new directory (with the component name) in *src/*. Feel free to modify *src/main.c* to demonstrate your new component.

In the top-level *Makefile*, add your component's directory to `CFLAGS` so that make knows where to find the associated .h file(s). Also, append your .c source file to `CSOURCES`. Note: the Makefile is only designed to build C applications. You'll need to modify it if you wish to build applications writtn in C++.

Copy the *average/* directory in *tests/* and rename it to your component's name. Modify *test.cpp* in your component test directory to fully test your component's functionality. Refer to the [CppUTest manual](http://cpputest.github.io/manual.html) as necessary. 

Note the `extern "C" {...}` clause in *test.cpp* for running tests on components written in C. See [this documentation](https://github.com/cpputest/cpputest/blob/master/README_CppUTest_for_C.txt) for more information about running CppUTest on C components.

Change `COMPONENT_NAME` in the unit test *Makefile* to your component's name (it must match the name of your unit test directory found in *tests/*).

Run `make` from your unit test directory to perform just the tests for your component. Run `make test` from the top-level directory of this repository to run all unit tests.

## License

All code, unless otherwise noted, is licensed under the [Zero-Clause BSD (0BSD) license](https://opensource.org/licenses/0BSD).

Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.