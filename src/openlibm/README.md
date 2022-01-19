## OpenLibm

This project uses [OpenLibm](https://openlibm.org) as an alternative to the standard math library.

OpenLibm was compiled using [gnu-make for windows](http://gnuwin32.sourceforge.net/packages/make.htm).
Downloaded from the [github repository](https://github.com/JuliaMath/openlibm),
compiled using the `make ARCH=wasm32` command.

The compiled `libopenlibm.a` file wasn't accepted by clang as a proper library, so it had to be converted into a random library using `ranlib`.
Final operation looked like this: `llvm-ranlib libopenlibm.a`.
`llvm-ranlib` comes along with [llvm clang for windows](https://llvm.org/builds).

Treat things above as "tips" for windows users when trying to use clang for wasm compilation on windows.