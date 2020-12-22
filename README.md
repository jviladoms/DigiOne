# DigiOne

Digione is a software to monitor several digital voice platforms of ham radio DMR,YSF,DCS and M17. DigiOne started as a fork of Dudestar project and has been developed trying to create features wanted in catalan ham radio community.

## Installation

sudo apt install build-essentials git
```
Then, install dependencies
```
sudo apt install cmake qtchooser qt5-qmake libqt5multimedia5-plugins libqt5serialport5-dev qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5 flite-dev libasound2-dev
```
Then move to where you plan to clone things 
```
cd *MY_GIT_DIRECTORY*
```
We need to build `mbelib` first. Move to where you clone git stuff and:
```
git clone https://github.com/szechyjs/mbelib
cd mbelib                           # Move into source folder
mkdir build                         # Create build directory
cd build                            # Move to build directory
cmake ..                            # Create Makefile for current system
make                                # Compiles the library
sudo make install                   # Library is installed into computer
sudo ldconfig     # this is needed to make the library visible
```
then go back to your git directory
```
cd *MY_GIT_DIRECTORY*
```
Then clone the DigiOne repository
```
git clone https://github.com/jviladoms/DigiOne
```
And build:
```
cd DigiOne
qmake
make
```
Then run and try, your mileage may vary
```
./digiOne
```
