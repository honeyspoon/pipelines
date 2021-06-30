#!/bin/sh
file=$1
nb_pass=$2
echo $file $nb_pass

pipe_all() {
	local cmd="cat $file "

	if [[ ! -z "${@}" ]]
	then
		echo a $@ b
		cmd+=" | "
		cmd+=`sed -e "s/ / | /pg" <<< $@`
	fi

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
for i in `seq 0 ${nb_pass}`
do
	pipeline_1+=(pass)
done

time pipe_all "${pipeline_1[@]}"

