#!/usr/bin/env python3

for row in range(1, 5):
    for col in range(1, 8):
        name = "Block"
        if col == 4:
            name = "Ultra" + name
        elif col == 2 or col == 6:
            name = "Super" + name

        print(name, row, "-", col, ",", row, ",", col, sep = "")

