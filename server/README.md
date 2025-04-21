# server


make build-release
make start-release


wscat --connect ws://localhost:8080/chat
sudo apt install node-ws


# install
sudo apt-get install -y git gcc g++ cmake make \
  libboost-dev libboost-program-options-dev \
  libyaml-cpp-dev libfmt-dev libspdlog-dev \
  libgtest-dev libgmock-dev libbenchmark-dev

sudo apt-get install ninja-build
sudo apt-get install libssl-dev

# dop
sudo apt install -y libcrypto++-dev libcrypto++-utils
sudo apt install -y libc-ares-dev