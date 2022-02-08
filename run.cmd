@echo off

echo Compiling C++ with LLVM Clang:
powershell clang++ --target=wasm32 -std=c++17 -nostdlib -fno-exceptions -ffreestanding '-Wl,--no-entry' '-Wl,--export-all' '-Wl,--allow-undefined' -O2 -o public/wasm/main.wasm src/main.cpp src/utils/src/malloc.cpp src/utils/src/winreqanim.cpp src/utils/src/fetch.cpp src/utils/src/cstring.cpp -L./src/openlibm/ -lopenlibm
echo Finished!
echo ---

cd public
echo Running the Server on http://localhost:8080/
python -m http.server 8080