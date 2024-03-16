#!/usr/bin/env python3

import os
os.remove("output.txt")
os.system(r"./runner.sh")

outputs = []
with open("./output.txt","r") as f:
    for line in f:
        outputs.append(line.strip("\n"))

proper_outputs = []
for i in range(22):
    with open(f"../data/output{i+1}.txt", "r") as f:
        for line in f:
            proper_outputs.append(line.strip("\n"))

correct_ones = 0
for i in range(len(outputs)):
    if (outputs[i] == proper_outputs[i]):
        print("nice!")
        correct_ones += 1

    else:
        print("shit!")
print(f"You got a score of {correct_ones*100/len(outputs)}%\n")
