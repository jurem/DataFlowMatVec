#!/bin/bash

exe="$1"
repeat=${2:-3}
pause=${3:-3}

name=${exe#../}
name=${name%%/*}

logfile="$name.txt"
echo $logfile

test -f "$logfile" && exit

# warm up
"$exe" -n 512 >/dev/null

# benchmark
for ((n = 1024; n <= 16384; n += 1024)); do
	for ((r = 0; r < $repeat; r++)); do
		sleep $pause
		"$exe" -n $n 2>&1 | tee -a "$logfile"
	done
done

