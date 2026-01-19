
This repository implements a sokoban game. The game can be played with the command line or with a graphical user interface. The graphical user interface is implemented using the library GTKMM-4.0.
For now, it only works on linux.

Here is a capture of the game:

<img width="421" height="382" alt="image" src="https://github.com/user-attachments/assets/2866d920-df44-4f8d-8bc0-d366778978e7" />


# Prerequisites
You must install the following libraries before building the application:

```bash
# install gtkmm-4.0
sudo apt-get install libgtkmm-4.0-dev
```

# Build the application
To build the application using cmake, use the following commands:

```bash
# configure cmake
cmake -B build -G "Unix Makefiles"
# go to build directory
cd build
# compile the binaries
make
```

# Run the GUI application
Before running the GUI application, you should define the following variable:
```bash
export SOKOBAN_ASSETS=<path to the directory assets in your system (provide an absolute path finishing with a /)>
# for instance, the SOKOBAN_ASSETS can be set to /home/<userName>/sokoban/assets/
```
Then, run the application as any program:
```bash
# run the GUI application
./sokoban

# you can also provide a path to a sokoban map
./sokoban <path to sokoban map>
```

# Running the command line application
```bash
./sokobanCmdLine <path to the sokoban map>
```

