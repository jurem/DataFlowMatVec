#!/bin/bash

source libprepare.sh


cd ..
src_prjs="Stripes"
stripe_cnts="16 1024"

function list {
	for p in $src_prjs; do
		for c in $stripe_cnts; do
			dst=${p}$c
			echo $dst
		done
	done
}


function prepare {
	for p in $src_prjs; do
		for c in $stripe_cnts; do
			src=$p
			dst=${p}$c
			cp_prj $src $dst && set_stripes $dst $c
		done
	done
}


function makeall {
	for p in $src_prjs; do
		for c in $stripe_cnts; do
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
