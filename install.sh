#!/bin/bash

INSTALL_GMP=false
erase=false
while getops ":g:e:-:" opt;
do
	case $opt in
		g)
			INSTALL_GMP=true
			;;
		e)
			erase=true
			;;
		-)
			case "$OPTARG" in
				gmp)
					INSTALL_GMP=true
					;;
				erase)
					erase=true
					;;
				*)
					echo "Invalid option: --$OPTARG" >&2
					;;
			esac
			;;
		\?)
			echo "Invalid option: -$OPTARG" >&2
			;;
	esac	
done

if [ "$INSTALL_GMP" ]
then
	mkdir deps
	cd deps
	curl -L -o "gmp.tar" https://gmplib.org/download/gmp/gmp-6.3.0.tar.xz
	tar -xjf "gmp.tar"
	rm "gmp.tar"
	cd gmp
	./configure --enable-cxx
	make
	make check
	make install
	cd ../..
fi

mkdir build
cd build
cmake ..
cmake --build .
cd ..
if [ "$erase" ]
then
	rm -rf build
fi
