#!/usr/bin/env python3
# Author: Simon Kaemmer

import subprocess as sp
import os

sp.run(["valgrind",  "--log-file=valgrind", "--tool=lackey", "--trace-mem=yes",  "ls"])

file = open("valgrind", "r")
adds = open("addresses", "w")

lines = []

# Unnötige Zeilen rauswerfen und nur Addresse abspeichern
for line in file:
    if line[0] != '=':

        hexInt = int("0x" + line[3:11], 16) # Erst in HexInt umwandeln
        maskedInt = hexInt & 0b11111111111111111111000000000000 # Dann die letzten 12 Bit fürs Offset wegmasken
        shiftedInt = maskedInt >> 12    # Die letzten nun leeren Bits wegshiften
        lines.append(str(shiftedInt) + "\n")

# Fertige Addressen in ein neues File schreiben
for str in lines:
    adds.write(str)

file.close()
adds.close()

os.system("sort addresses | uniq -c | sort -nr")
