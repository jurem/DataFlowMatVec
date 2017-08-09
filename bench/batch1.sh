#!/bin/bash

source libprepare.sh


cd ..
src_prjs="RowRow RowCol ColRow ColCol"


function list {
	for p in $src_prjs; do
		for c in 2 4 8 16 32; do
			dst=${p}P$c
			echo $dst
		done
	done
}


function prepare {
	for p in $src_prjs; do
		for c in 2 4 8 16 32; do
			src=$p
			dst=${p}P$c
			cp_prj $src $dst && set_pipes $dst $c
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
