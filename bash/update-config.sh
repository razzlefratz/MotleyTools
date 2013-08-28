

  if [ -z ${1} ]; then
	echo argument {1} is empty
	exit 1
elif [ -z ${2} ]; then
	echo argument {2} is empty
	exit 1
elif [ -z ${3} ]; then
	echo argument {3} is empty
	exit 1
else
	name=$(pn --name ${3})
	type=$(pn --type ${3})
fi

  if [ -f ${1}/${name}.${HOSTNAME}.${type} ]; then
	echo install -m 0644 -o root -g root ${1}/${name}.${HOSTNAME}.${type} ${2}/${3}
elif [ ! -f ${2}/${3} ]; then
	echo install -m 0644 -o root -g root ${1}/${3} ${2}/${3}
elif [ ${2}/${3} -nt ${log} ]; then
	echo install -m 0644 -o root -g root ${1}/${3} ${2}/${3}
fi

