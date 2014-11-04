#!/usr/bin/env python3

for row in range(1, 5):
    for col in range(1, 8):
        name = "Block"
        health = 1
        if col == 4:
            health += 2
        elif col == 2 or col == 6:
            health += 1

        print(name, row, "-", col, ",", health, ",", row, ",", col, sep = "")

