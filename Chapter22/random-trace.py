#!/usr/bin/env python3
# Author: Simon Kaemmer

from __future__ import print_function
from optparse import OptionParser
import subprocess
import os
import random


parser = OptionParser()
parser.add_option('-n', '--number', default=10, help='Number of random integers to generate', action='store', type='int', dest='number')
parser.add_option('-m', '--maxvalue', default=10, help='Biggest VPN to refer to', action='store', type='int', dest='maxvalue')
parser.add_option('-p', '--policy', default='FIFO', help='replacement policy: FIFO, LRU, OPT, UNOPT, RAND, CLOCK', action='store', type='string', dest='policy')
parser.add_option('-l', '--locality', default='0', help='Sortes the random accesses to create locality 1', action='store', type='int', dest='locality')
parser.add_option('-b', '--clockbits', default='2', help='How many clockbits', action='store', type='int', dest='clockbits')

(options, args) = parser.parse_args()

file = open("random-trace", "w")

def noLocality():
    s = ""

    for x in range(options.number):
        s += str(random.randint(0, options.maxvalue)) + ","
        #file.write(str(random.randint(0, options.maxvalue)) + "\n")
    
    s = s[:-1]
    return s

def useLocality():
    i = []
    s = ""

    for x in range(options.number):
         i.append(random.randint(0, options.maxvalue))

    i.sort()

    for v in i:
        s += (str(v) + ",")

    s = s[:-1]
    return s

if options.locality == 1:
    os.system("python3 ./paging-policy.py -c -a " + useLocality() + " -p " + str(options.policy) + " -b " + str(options.clockbits))
else:
    os.system("python3 ./paging-policy.py -c -a " + noLocality() + " -p " + str(options.policy) + " -b " + str(options.clockbits))


