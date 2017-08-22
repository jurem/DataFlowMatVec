#!/bin/bash

source libprepare.sh


cd ..
src_prjs="StripesRow StripesCol"
pipes="2 4 8 16 32 64 128"


function list {
	for p in $src_prjs; do
		for c in $pipes; do
			dst=${p}P$c
			echo $dst
		done
	done
}


function prepare {
	for p in $src_prjs; do
		for c in $pipes; do
			src=$p
			dst=${p}P$c
			cp_prj $src $dst && set_stripes $dst 128 && set_pipes $dst $c
		done
	done
}


function makeall {
	for p in $src_prjs; do
		for c in 2 4 8 16 32; do
			dst=${p}P$c
			pushd . >/dev/null
			cd $dst/RunRules/DFE
			make
			popd >/dev/null
		done
	done
}


$1

exit 0
