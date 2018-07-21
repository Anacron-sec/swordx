# SwordX

Copyright © Michele Biondi, Samuele Cucchi

This is the repository for the project of Operating Systems lab at University of Camerino, Italy.

SwordX is a command line tool to count word occurences inside of files.

## Installation
Inside program folder

```shell
make
make install # as root
```

You should be able to use the 'swordx' command from anywhere.

As an alternative you can build files using Docker, the steps become (run as root):
```shell
# make sure to remove old compiled files

./build_docker.sh
make install
```

## Remove

To remove the program just run as root inside program folder

```shell
make uninstall
```

## Usage

To list all options run:

```shell
swordx --help
```
By default the program will save results in a file called 'swordx.out' inside current folder.

## Examples

Read words from file sample.txt and sample2.txt
```shell
swordx sample.txt sample2.txt
```

Read words from folder samples and write results to 'output.txt' and sort results by occurences
```shell
swordx sample/ -s -o output.txt
```

## Development
To run tests you need the cunit framework, on debian based systems you need to run as root:

```shell
apt-get update
apt-get install libcunit1 libcunit1-dev
```

Next you can run tests using:
```shell
make # if you didn't run it previously
make test
```
