#!/bin/bash
# Change directory to 'nprolog'.
# If this fails (e.g., directory does not exist), exit immediately with status 1.
cd /home/sasagawa/nprolog || exit 1
# Run the 'npl' program with the '-n' option.
./npl -n
