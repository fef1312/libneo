# libneo

libneo is an alternative standard library that wraps around libc.
It comes with an entirely refactored API that is easier and safer
to use than traditional POSIX.  Key features include:

- Sane(ish), standardized error handling
- Minimal undefined behavior
- Significantly less boilerplate
- Memory safe(ish)
- Runs on most POSIX compliant systems (tested on FreeBSD and Linux)
- No Windows support

## Usage

Please note that this project is still in its early development stage.
APIs are subject to arbitrary change without prior notice.

### Dependencies

- A libc implementing at least POSIX.1-2008
- clang (recommended) or GCC
- CMake >= 3.14
- git

### CMake

libneo is distributed as a static library and can be directly included
in a CMake project, e.g. using CMake's `FetchContent` module:

```cmake
include(FetchContent)
FetchContent_Declare(
    neo
    GIT_REPOSITORY https://git.bsd.gay/fef/libneo.git
)
FetchContent_MakeAvailable(neo)

target_link_libraries(${PROJECT_NAME} PRIVATE neo)
```

## License

Copyright &copy; 2021 Fefie <owo@fef.moe>

libneo is non-violent software: you may only use, redistribute,
and/or modify it under the terms of the CNPLv6+ as found in the
LICENSE file or at <https://git.pixie.town/thufie/CNPL>.

libneo comes with ABSOLUTELY NO WARRANTY, to the extent permitted
by applicable law.  See the CNPLv6+ for details.
