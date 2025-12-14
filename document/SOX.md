# Sox Library

This library uses Sox to play sounds. Its purpose is to represent a sequence of numbers as a melody.

# Installation
sudo apt install sox

# Usage
use_module(sox).

sox_play(N).


N is an integer between -60 and 67. C4 corresponds to 0, which is equivalent to MIDI note 60.
For example:

C4 = 0
D4 = 2
...


Each note is played for 0.4 seconds.