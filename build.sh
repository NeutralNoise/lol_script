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
  else
    echo "We really do not know what $1 is."
  fi
else
  echo Compiling Debug build.
  (cd lolVM && make)
  (cd lolCompiler && make)
fi
echo DONE!
