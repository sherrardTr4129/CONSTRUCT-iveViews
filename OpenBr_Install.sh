 Install CMake 2.8.10.1
sudo apt-get install -y cmake cmake-curses-gui 
 
wget http://netcologne.dl.sourceforge.net/project/opencvlibrary/opencv-unix/2.4.5/opencv-2.4.5.tar.gz
tar -xf opencv-2.4.5.tar.gz
cd opencv-2.4.5
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
sudo make install
cd ../..
rm -rf opencv-2.4.5*
 
sudo apt-get install qt5-default libqt5svg5-dev qtcreator
 
git clone https://github.com/biometrics/openbr.git
cd openbr
git submodule init
git submodule update
 
mkdir build # from the OpenBR root directory
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
sudo make install
 
