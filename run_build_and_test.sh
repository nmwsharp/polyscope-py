set -e
# rm -rf build
cd ~/Code/polyscope-py
rm -rf src/polyscope_bindings
mkdir -p build
cd build
cmake ..
make -j 4
mv polyscope_bindings.cpython-36m-x86_64-linux-gnu.so ../src/

cd ../src
python3.6 test.py
