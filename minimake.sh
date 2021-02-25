#!/bin/sh

build_dir=build

if [ $# -eq 1 ] && [ "$1" == "test" ]; then
	# compile and test
	cmake -S . -B $build_dir -DBUILD_TESTING=ON && ( cd $build_dir && make ) \
	&& ( cd $build_dir && ctest --output-on-failure ./) \
	&& echo -e "Tests ran: \e[92mok\e[39m." \
	|| { echo -e "Tests ran: \e[91mNOPE\e[39m."; false; }
elif [ $# -eq 1 ] && [ "$1" == "clean" ]; then
	# clean all files which are specified in .gitignore 
	git clean -d -f -X
elif [ $# -eq 0 ]; then
	# compile and copy printf binary and lib to root folder
	cmake -S . -B $build_dir -DBUILD_TESTING=OFF && ( cd $build_dir && make ) \
	&& cp $build_dir/src/libprintf.a ./ \
	&& echo -e "You can include \e[92mlibprintf.a\e[39m in your library." \
	|| { echo -e "Compilation ran: \e[91mNOPE\e[39m."; false; }
else
	cat<<-EOF
	usage:
	  $0       -> compile
	  $0 test  -> compile and test
	  $0 clean -> remove build files 
	EOF
fi

