#!/bin/sh
file=$1
nb_pass=$2
echo $file $nb_pass

pipe_all() {
	local cmd="cat $file | "

	cmd+=`sed -n -e "s/ / | /pg" <<< $@`
	cmd+=" > /dev/null"

	echo $cmd
	eval $cmd
}

pass() {
	build/pass
}

pass_unbuffered() {
	stdbuf -i0 -o0 build/pass
}

pipeline_1=()
for i in `seq ${nb_pass}`
do
	pipeline_1+=(pass)
done

time pipe_all "${pipeline_1[@]}"

