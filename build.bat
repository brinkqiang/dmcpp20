
rem - clone code
rem git clone https://github.com/brinkqiang/dmcpp.git
rem pushd dmcpp
rem git submodule update --init --recursive

rmdir /S /Q build
mkdir build
pushd build
cmake -A x64 -DCMAKE_BUILD_TYPE=debug ..
cmake --build . --config debug
popd

rem pause
