#!/bin/bash
# Auto-update script for N-Prolog only


DIR="$HOME/nprolog"
SERVICE="npl.service"

if [ ! -d "$DIR" ]; then
  echo "N-Prolog directory not found."
  exit 0
fi

cd "$DIR"

if systemctl list-unit-files | grep -q "$SERVICE"; then
  systemctl stop "$SERVICE"
fi

git stash push -m 
git pull --rebase
make clean
make -j$(nproc)

if systemctl list-unit-files | grep -q "$SERVICE"; then
  systemctl start "$SERVICE"
fi

echo "N-Prolog update finished."