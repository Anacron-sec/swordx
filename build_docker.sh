#!/usr/bin/env sh
docker container run --rm -v "$PWD":/usr/src/swordx -w /usr/src/swordx gcc:6.4.0 make