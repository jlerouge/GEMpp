#!/bin/bash
# GEM++ Installation Script
if [ -f $HOME/bin/GEM++ ]; then
    echo "> GEM++ is already installed.";
	read -p "> Do you really want to overwrite it ? [y/N] : " -r
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        echo "The previous installation will be overwritten." 
	else
		echo "Installation aborted."
		exit 1;
    fi;
fi;
echo "GEM++ installation in progress..."
mkdir $HOME/bin/GEM++
cp -R bin/ $HOME
cp -R lib/ $HOME

echo " ###########################"
echo " # End of the installation #"
echo " ###########################"
echo " In order to complete the installation, please export this"
echo " environment variables (if not already done previously), e.g."
echo " in your .bashrc profile script."

dist=`uname -s | awk '{print tolower($0)}'`
if [[ `uname -m` == x86_64 ]]; then # 64bits
	dist=${dist}64
else # x86 = 32 bits
	dist=${dist}32
fi;
echo " export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/opt/gurobi563/$dist/lib"

