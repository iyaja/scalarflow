<h1 align="center"> ScalarFlow: TensorFlow But Dumber</h1>

## Building

We use CMake to manage the build system. To generate build files and build the project from scratch, run the following commands from the root directory of the project.

> Note: these instructions are for the `master` branch only. For EWS-specific instructions, please visit the `ews` branch, which has ready-to-use makefiles. The steps below will run on EWS as well, but involve a few more commands.

```
mkdir build
cd build
cmake ../
cmake --build .
```

The final command (`cmake --build .`), if sucessful, will build the `libscalarflow.a` library file along with the executables that run the algorithms. These files will be `build/` directory of the project.

## Executables

- `main`: Entry point to run a sample of implemented algorithms. Takes a single `.sfg` file as input and presents a simple text-based interface to run different algorithms on the parsed graph.

## Tests

There are multiple options to run the test suite. The simplest is via the CTest framework, which will use your ative build system to build an run the tests via Catch2. You can run these tests from the `build/` sub-directory using CTest:

```
ctest
```

Alternatively, if you're using the Makefile on the `ews` branch, you can build and run the tests directly from `make`:

```
make test
```

If you'd like to run the catch tests directly without going thorugh CTest, you can instead run the `catch` binary directly from the `build/` directory with the usual Catch2 flags:

```
./catch
```