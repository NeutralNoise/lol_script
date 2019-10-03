#!/bin/bash
echo Building lol_script!
if [ "$1" != "" ]; then
  if [ $1 == release ]; then
    echo Compiling $1 build.
    (cd lolVM && make release)
    (cd lolCompiler && make release)
  elif [ $1 = check ]; then
    echo Compiling $1 build.
    (cd lolVM && make check)
    (cd lolCompiler && make check)
  elif [ $1 = clean ]; then
    echo Cleaning build.
    (cd lolVM && make clean && rm -f -r Debug)
    (cd lolCompiler && make clean && rm -f -r Debug)
  else
    echo "We really do not know what $1 is."
  fi
  echo $1 build finished
else
  echo Compiling Debug build.
  (cd lolVM && make)
  (cd lolCompiler && make)
  echo Debug build finished
fi
echo DONE!
