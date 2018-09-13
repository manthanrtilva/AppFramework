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
