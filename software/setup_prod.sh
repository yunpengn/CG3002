#!/bin/sh

echo "Trying to download Berry Conda ..."
wget https://github.com/jjhelmus/berryconda/releases/download/v2.0.0/Berryconda3-2.0.0-Linux-armv7l.sh

echo "\nTrying to install Berry Conda ..."
chmod +x Berryconda3-2.0.0-Linux-armv7l.sh
./Berryconda3-2.0.0-Linux-armv7l.sh

echo "\nTrying to install all dependencies ..."
conda install numpy
conda install pandas
conda install scipy
conda install scikit-learn

echo "\nList out all installed dependencies ..."
conda list

echo "\nEnvironment setup completed."
