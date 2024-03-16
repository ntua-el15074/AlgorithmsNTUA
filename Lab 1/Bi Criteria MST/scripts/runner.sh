#!/usr/bin/env bash

for i in $(seq 1 29);
do
    ./main < ../data/input$i.txt >> output.txt
done
