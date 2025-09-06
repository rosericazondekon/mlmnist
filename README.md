# mlmnist

## Overview
Small C++ project that reads the original MNIST image and label files, processes them and splits the dataset into training/validation/test sets. The project builds a shared library and includes a small `main` program that demonstrates loading and splitting the dataset.

## What this repository contains
- [`src/`](./src/) — C++ source files
- [`include/`](./include/) — headers for the project
- [`main.cpp`](./main.cpp) — small demo program that loads MNIST files and prints status
- [`Makefile`](./Makefile) — builds the shared library and the `bin/main` executable
- [`mnist_data/`](./mnist_data/) — (not included) directory where MNIST files should live

## Prerequisites
- A C++ compiler with C++20 support (e.g. g++ 11+ or clang++ with C++20)
- `make`
- `wget` or `curl` to download datasets

On macOS, Xcode command line tools provide `clang++` and `make`.

## Build and run
The Makefile is configured to build the library and then compile & run the `main` program by default.

From the project root run:

```bash
make        # builds lib and runs bin/main (which executes the demo)
```

If you only want to compile and run the demo (without the library step) use:

```bash
make run-main
```

To clean build products:

```bash
make clean
```

## MNIST dataset — where to get it
You can get the original MNIST files from the internet. For this project, I downloaded them from [here](https://github.com/mrgloom/MNIST-dataset-in-different-formats/tree/master/data/Original%20dataset). The following files are required and should be placed in the `mnist_data/` directory at project root:

- [`train-images.idx3-ubyte`](https://raw.githubusercontent.com/mrgloom/MNIST-dataset-in-different-formats/master/data/Original%20dataset/train-images.idx3-ubyte)
- [`train-labels.idx1-ubyte`](https://raw.githubusercontent.com/mrgloom/MNIST-dataset-in-different-formats/master/data/Original%20dataset/train-labels.idx1-ubyte)

One simple way is to use `curl` or `wget` to download the raw files. 
Here is an example commands with `wget` that downloads the four files into the `mnist_data/` folder:

```bash
# create the directory if it doesn't exist, then enter it
if [ ! -d mnist_data ]; then
  mkdir -p mnist_data
fi
cd mnist_data

wget -O mnist_data/train-images.idx3-ubyte \
  https://raw.githubusercontent.com/mrgloom/MNIST-dataset-in-different-formats/master/data/Original%20dataset/train-images.idx3-ubyte

wget -O mnist_data/train-labels.idx1-ubyte \
  https://raw.githubusercontent.com/mrgloom/MNIST-dataset-in-different-formats/master/data/Original%20dataset/train-labels.idx1-ubyte
```

## Expected file layout after downloading

```
mnist_data/
  train-images.idx3-ubyte
  train-labels.idx1-ubyte
  t10k-images.idx3-ubyte
  t10k-labels.idx1-ubyte
```

## Troubleshooting
- If `make` fails due to compiler version, ensure your compiler supports C++20: `g++ --version` or `clang++ --version`.
- If the demo complains it can't find files, verify `mnist_data/` exists and files are named exactly as above and readable.
- On macOS you may see `.dylib` naming preferences; this project builds a `.so` for portability. If you prefer `.dylib`, feel free to edit the [`Makefile`](./Makefile).

