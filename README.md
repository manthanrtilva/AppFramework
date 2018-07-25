
git clone ...
git submodule init
git submodule update
cd AppFramework
mkdir build
cd build
cmake -DENABLE_TESTS=ON ../code/
cmake --build .
