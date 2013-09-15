#!/bin/bash
# simple script to download and install the
# google logging library and ceres-solver library
wget http://google-glog.googlecode.com/files/glog-0.3.3.tar.gz
tar xvf glog-0.3.3.tar.gz
cd glog-0.3.3
./configure
make -j2
sudo make install
cd ..
wget http://ceres-solver.googlecode.com/files/ceres-solver-1.7.0.tar.gz
tar xvf ceres-solver-1.7.0.tar.gz
sudo apt-get install libatlas-base-dev libeigen3-dev libsuitesparse-dev
mkdir ceres-bin
cd ceres-bin
cmake ../ceres-solver-1.7.0 -DGFLAGS=OFF
make -j2
make test
sudo make install
