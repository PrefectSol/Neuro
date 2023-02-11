# Neuro: still preparatory project 

CLI for training and implementation of new modules in neural networks.


## Testing Modules

- GCD: finding the greatest common divisor
- Parsing (features): getting information from the Internet by key text.
- Vision (features): object recognition.

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

## Dependencies

 - [CMake](https://github.com/Kitware/CMake)

 - [JsonCpp](https://github.com/open-source-parsers/jsoncpp)

    ### Installing on Linux
    ```bash
    sudo pacman -S cmake jsoncpp
    ```

    ### Installing on Windows
    ```bash
    winget install cmake
    ```