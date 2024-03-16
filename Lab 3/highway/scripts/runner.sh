#!/usr/bin/env bash

for i in $(seq 0 20);
do
    ./main < ../data/input$i.txt >> output.txt
done
