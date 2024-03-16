#!/usr/bin/env bash

for i in $(seq 1 22);
do
    echo $i
    ./main < ../data/input$i.txt >> output.txt
done
