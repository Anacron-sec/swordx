#!/usr/bin/env sh
docker container run --rm -v "$PWD":/usr/src/swordx -w /usr/src/swordx gcc:8.1.0 make clean && make -j