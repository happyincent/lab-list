#!/bin/bash

for level in {0..3};
do
    sed -i "s/-O[0123]/-O$level/" Makefile
    make clean all > /dev/null
    score=0
    
    for i in {1..10};
    do
        score=$(($score+$((timeout 10 make test 2>/dev/null || echo 0) | tail -n1 | cut -d'/' -f1 | tr -dc '0-9')))
    done
    
    echo -O$level grade: $(( $score / $i ))
done
