#!/bin/bash

function cp_prj {
	src=$1
	dst=$2

	echo -en "$dst: \t"
	test -e $dst && echo "exists" && return 1

	echo "preparing"

	echo "  copy $src to $dst"
	cp -r $src $dst
}


function set_pipes {
	dst=$1
	cnt=$2

	f=$(egrep -r "PIPE_COUNT = " $dst | cut -d: -f1)
	echo "  set pipes $f: PIPE_COUNT = $cnt"
	{
		rm "$f"
		sed -E -e "s/PIPE_COUNT = [[:digit:]]+/PIPE_COUNT = $cnt/" >"$f"
	} <"$f"
}


function set_stripes {
	dst=$1
	cnt=$2

	f=$(egrep -r "STRIPE_SIZE = " $dst | cut -d: -f1)
	echo "  set stripes $f: STRIPE_SIZE = $cnt"
	{
		rm "$f"
		sed -E -e "s/STRIPE_SIZE = [[:digit:]]+/STRIPE_SIZE = $cnt/" >"$f"
	} <"$f"
}

