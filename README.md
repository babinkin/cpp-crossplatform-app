# На Macbook:
chmod +x scripts/find_boost_mac.sh
mkdir build && cd build
cmake ..
make
./boost_test

# На Ubuntu:
mkdir build && cd build
cmake ..
make
./boost_test