# Neuro: Template project 

CLI for creation and implementation of new modules in the main neural network stream

## Creation Modules

- GCD: finding the greatest common divisor. (Module for testing)
- Template (in process): creating your own neural network based on a ready-made template.
- Parsing (features): getting information from the Internet by key text.
- Vision (features): object recognition.
- Text Handler (features): chatting.

## Implementation Modules (Features)

- Matrix: write the matrix of neural network.
- Memory: save data in the neural network memory.


## Build and Run

```bash
git clone git@github.com:PrefectSol/Neuro.git
cd Neuro/
cmake .
make
./Neuro
```


## Custom run

To set custom settings, create a conf.json using the ```create``` command, change the settings in the created file, then ```run``` the utility using the run command.

To view the hints to the ```conf.json``` using the ```help``` command


## Dependencies

 - [CMake](https://github.com/Kitware/CMake)

 - [JsonCpp](https://github.com/open-source-parsers/jsoncpp)

    ### Installation on Linux (Arch)
    ```bash
    sudo pacman -S cmake jsoncpp
    ```

    ### Installation on Windows
    ```bash
    winget install cmake
    ```

## Personal comment

```rust
// The basic structure for creating the simplest neural networks using the CLI is ready.
// I changed the structure of the project and now everything works as a template.
// But unfortunately because of this, the learning rate of neural networks has dropped from 0.4 to 2-5
// seconds.
```
