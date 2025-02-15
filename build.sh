mkdir libs
git clone https://github.com/memflow/memflow-qemu
cd memflow-qemu
cargo build --release --all-features
cp target/release/libmemflow_qemu.so ../libs
cd ..

git clone https://github.com/memflow/memflow-win32
cd memflow-win32
cargo build --release --all-features
cp target/release/libmemflow_win32.so ../libs
cd ..

git clone https://github.com/memflow/memflow
cd memflow/memflow-ffi
cargo build --release --all-features
cd ../
cp target/release/libmemflow_ffi.so ../libs
cd ..

mkdir bin
g++ main.cpp memory.cpp render.cpp game.cpp -o bin/cs2-radar -lSDL2 -lSDL2_image  -lSDL2_gfx -std=c++17 -lmemflow_ffi

echo "can be ran using sudo ./bin/cs2-radar"
