#!/usr/bin/bash
#
#inside the folder where i cloned submission repository, make exercise folders
cd ~/Desktop/entrega
mkdir ex00 ex01 ex02
cd -
# clean for exercise folder compiled objects.
cd ex00
make clean
cd -
cd ex01
make clean
cd -
cd ex02
make clean
cd -
# copy submission files
#
cp ex00/Makefile ~/Desktop/entrega/ex00/Makefile
cp ex00/*.hpp ~/Desktop/entrega/ex00/
cp ex00/*.cpp ~/Desktop/entrega/ex00/
cp ex01/Makefile ~/Desktop/entrega/ex01/Makefile
cp ex01/*.hpp ~/Desktop/entrega/ex01/
cp ex01/*.cpp ~/Desktop/entrega/ex01/
cp ex02/Makefile ~/Desktop/entrega/ex02/Makefile
cp ex02/*.hpp ~/Desktop/entrega/ex02/
cp ex02/*.cpp ~/Desktop/entrega/ex02/

# Inside submission repository check that every thinh works properly
cd ~/Desktop/entrega/ex00
make
./convert
make clean
cd -
cd ~/Desktop/entrega/ex01
make
./serialize
make clean
cd -
cd ~/Desktop/entrega/ex02
make
./identify
make clean
cd -
