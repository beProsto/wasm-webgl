@echo off

echo Compiling C++ with LLVM Clang:
powershell clang++ --target=wasm32 -std=c++17 -nostdlib '-Wl,--no-entry' '-Wl,--export-all' '-Wl,--allow-undefined' -o public/main.wasm src/main.cpp src/utils/src/malloc.cpp src/utils/src/winreqanim.cpp
echo Finished!
echo ---

cd public
echo Running the Server on http://localhost:8080/
python -m http.server 8080