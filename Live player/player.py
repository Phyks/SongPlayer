#!/usr/bin/env python3

# ============================================================================
# This script allows you to play music using a chorizo (or whatever food you
# like) keyboard ! See README for more info and links.

# As all the other scripts in this repository, I release it under a very
# permissive license. To make a long story short : do whatever you want with
# this script (but try to have fun :), I don't mind. It would be cool to quote
# the origin of the script if you reuse it, but you don't have to. I'd like to
# be noticed of what you did cool with it (if you think it's worth). :)
# Ah, I almost forgot : If by chance we ever meet and you think this script is
# worth, you can buy me a soda :)
#
#                                                                   Phyks
# =============================================================================

from sound4python import sound
from multiprocessing import Process
import math

class _Getch:
    """Gets a single character from standard input.  Does not echo to the
screen."""
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getch()

getch = _Getch()

def play_wave(frequency=440, nb_secs=1.):
    sine_wave = []
    for i in range(math.ceil(nb_secs*framerate)+1):
        sine_wave.append(int(16384*math.sin(2*math.pi*frequency*i/framerate)))

    sound(sine_wave)

framerate = 16000
processes = []
frequency = 440

print("Running... Press q to quit.")
running = True
while running:
    char = getch()
    if char == "q":
        running = False
        continue
    elif char == "a":
        frequency = 440
    elif char == "b":
        frequency = 493.88
    elif char == "c":
        frequency = 523.25
    elif char == "d":
        frequency = 587.33
    elif char == "e":
        frequency = 659.26
    elif char == "f":
        frequency = 698.46
    elif char == "g":
        frequency = 783.99
    else:
        continue

    print("Playing "+char.upper())
    processes.append(Process(target=play_wave, args=(frequency, 0.2)))
    processes[-1].start()

for i in processes:
    i.join()
