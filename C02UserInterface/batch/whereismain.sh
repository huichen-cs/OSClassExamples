#!/bin/bash

function look_for_main() {
  find $1 -type f -exec grep -H -i "main" {} \;
}

if [ $# == 0 ]; then
  SEARCHPATH=./
  look_for_main ${SEARCHPATH}
else
  for SEARCHPATH in "$@"; do
    look_for_main ${SEARCHPATH}
  done
fi
