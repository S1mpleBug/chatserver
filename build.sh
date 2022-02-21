#!/bin/bash

set -x

rm -fr `pwd`/build/*
cd `pwd`/build &&
    cmake .. &&
    make