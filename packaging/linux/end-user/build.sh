#!/bin/bash

# Changes to GEM++ root directory
here=$PWD/`dirname "$0"`
cd $here
root=../../../
cd $root/build

# Make sure that Makefiles are up to date
find . -name "Makefile" | xargs rm

# Build the project
qmake ../src/GEM++.pro
make

# Build the user and developer documentation
cd ../doc/user
doxygen
cd ../dev
doxygen
cd ../../build/

# Make a package
echo "This build script needs root privileges in order to make a package. Please enter root password if prompted." 
cp $here/description-pak .
rm -rf doc-pak
mkdir doc-pak
cp -R ../doc/user/html doc-pak
cp ../HISTORY doc-pak
cp ../LICENSE doc-pak
cp ../README doc-pak
cp ../THIRD-PARTY-NOTICES doc-pak
sudo checkinstall --install=no --backup=no --pkgname=gem++ --maintainer=julien.lerouge@litislab.fr;
rm -rf doc-pak
rm description-pak

# Moves to the build directory
mv *.deb $here
cd $here
