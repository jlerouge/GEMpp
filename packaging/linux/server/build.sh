#!/bin/bash

QT_VERSION="5.4.1"

# Changes to GEM++ root directory
here=$PWD/`dirname "$0"`
cd $here
root=../../..
cd $root/build

# Make sure that Makefiles are up to date
find . -name "Makefile" | xargs rm

# Build the project
qmake ../src/GEM++.pro
make

# Guess kernel and architecture
dist=`uname -s | awk '{print tolower($0)}'`
if [[ `uname -m` == x86_64 ]]; then # 64bits
	dist=${dist}64
else # x86 = 32 bits
	dist=${dist}32
fi;

# Get date
today=`date +"%Y%m%d"`

# Make a package
echo "This build script needs root privileges in order to make a package. Please enter root password if prompted."
cd $here
rm -rf GEM++
rm -rf bin
rm -rf lib
mkdir GEM++
cp -R $root/build/$dist/release/bin GEM++
cp -R $root/build/$dist/release/lib GEM++
cp $root/src/dependencies/Qt/$dist/$QT_VERSION/*.so* GEM++/lib
cp -R $root/src/dependencies/Qt/$dist/$QT_VERSION/imageformats GEM++/bin/
cp -R $root/src/dependencies/Qt/$dist/$QT_VERSION/platforms GEM++/bin/
cp install.sh GEM++

makeself GEM++/ gem++_${today}_${dist}.run "GEM++ : Graph Extraction and Matching C++ toolkit" ./install.sh
rm -rf GEM++

