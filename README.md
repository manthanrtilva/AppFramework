[![Travis Build master ](https://travis-ci.org/manthanrtilva/AppFramework.svg?branch=master)](https://travis-ci.org/manthanrtilva/AppFramework)
[![Travis Build development ](https://travis-ci.org/manthanrtilva/AppFramework.svg?branch=development)](https://travis-ci.org/manthanrtilva/AppFramework)
# How to build
```
git clone https://github.com/manthanrtilva/AppFramework.git
git submodule init
git submodule update
cd AppFramework
mkdir build
cd build
cmake -G "Visual Studio 15 2017" -DENABLE_TESTS=ON ../code/
cmake --build .
```
