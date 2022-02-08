#pragma once

#define assert(x) ((void)0)

// To communicate between wasm and js we need function names to not be mangled
// So yeah both import and export essentially does the same thing

#define WASM_EXPORT extern "C"
#define WASM_IMPORT extern "C"

#include "imports.hpp"
#include "winreqanim.hpp"
#include "malloc.hpp"

#include "cstring.hpp"
#include "../../openlibm/include/openlibm.h"
#include "math/math.hpp"
#include "gldef.hpp"
#include "fetch.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "canvas.hpp"
#include "api.hpp"