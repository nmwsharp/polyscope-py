set -e
# rm -rf build
cd ~/Code/polyscope-py
mv src/polyscope_bindings /tmp/polyscope_bindings
mkdir -p build
cd build
cmake ..
make -j 4
mv polyscope_bindings.cpython-36m-x86_64-linux-gnu.so ../src/

cd ../src
set +e

ln -s ~/Code/polyscope-py/test/assets ~/Code/polyscope-py/src/assets
ln -s ~/Code/polyscope-py/test/polyscope_test.py ~/Code/polyscope-py/src/polyscope_test.py

python3.6 polyscope_test.py

python3.6 test.py

# cleanup
cd ..
mv /tmp/polyscope_bindings src/polyscope_bindings
rm src/polyscope_bindings.cpython-36m-x86_64-linux-gnu.so
rm -r ~/Code/polyscope-py/src/assets
rm -r ~/Code/polyscope-py/src/polyscope_test.py
rm src/*.png
