#!/bin/bash
# GEM++ Installation Script
if [ -d $HOME/bin/GEM++ ]; then
    echo "> $HOME/bin/GEM++ already exists, the old install will be overwritten.";
	read -p "> Do you really want to continue ? [y/N] : " -r
    if [[ $REPLY =~ ^[Yy]$ ]]; then
		echo "Removing the old install..."
        rm -rf $HOME/bin/GEM++;
	else
		echo "Installation aborted."
		exit 1;
    fi;
fi;
echo "GEM++ installation in progress..."
if [ ! -d $HOME/bin ]; then
	mkdir $HOME/bin;
fi;
mkdir $HOME/bin/GEM++
cp -R bin/ $HOME/bin/GEM++
cp -R lib/ $HOME/bin/GEM++

echo " ###########################"
echo " # End of the installation #"
echo " ###########################"
echo " In order to complete the installation, please export these"
echo " environment variables (if not already done previously), e.g."
echo " in your .bashrc startup script."

dist=`uname -s | awk '{print tolower($0)}'`
if [[ `uname -m` == x86_64 ]]; then # 64bits
	dist=${dist}64
else # x86 = 32 bits
	dist=${dist}32
fi;
echo " export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/opt/gurobi560/$dist/lib"
echo " export PATH=\$PATH:\$HOME/bin/GEM++/bin"
