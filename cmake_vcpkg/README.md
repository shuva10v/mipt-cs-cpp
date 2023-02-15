# Integrate vcpkg with cmake

## vcpkg

* To start work with vcpkg in a new git repo add it as a submodule:
```sh
git submodule add git@github.com:microsoft/vcpkg.git
```
* To start work with vcpkg with this git repo just fetch vcpkg:
```sh
git submodule update --init --recursive
```
* Run ``bootstrap-vcpkg.sh``

Hint: if cmake can not detect vcpkg try to delete build folter and rerun cmake

## cmake

Out of source build:
```sh
mkdir build
cd build
cmake ../
cmake --build .
```

Links:
* [CMake documentation](https://cmake.org/cmake/help/latest/index.html)
* [Vcpkg configuration docs][https://github.com/microsoft/vcpkg]
* [CMake examples](https://github.com/ttroy50/cmake-examples)
* [spdlog examples](https://github.com/gabime/spdlog)