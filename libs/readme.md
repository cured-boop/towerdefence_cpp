### README.md

#### LIBS Directory

##### **In this directory, you are required to place all the external libraries** <-- says description
**TODO: Make sure includes refer to this directory and move libs here. Should setup.sh be modified to install to here?**

This directory is intended for all external libraries that your project depends on.

#### List of External Libs

- **SFML (Simple and Fast Multimedia Library):** Used for windowing, graphics, GUI, etc.
- **JSON for Modern C++ (nlohmann/json):** Used for JSON parsing and serialization.

#### How to Add Libraries Automatically

1. **Open terminal in the root directory (tower-defence-tran-duong-6)**
2. **Run setup.sh (This will install all the needed dependencies automatically)**
   *(If you lack permission to run it, execute this first: chmod +x setup.sh)*
    ```bash
    chmod +x setup.sh
    ```
    ```bash
    ./setup.sh
    ```
3. **Run 'make' (This will compile the project)**
    ```bash
    make
    ```
4. **Run './main' (This will run the program)**
    ```bash
    ./main
    ```


#### How to Add Libraries Manually

1. **SFML:**
   - **Option 1: Git Submodule**:
     ```bash
     git submodule add https://github.com/SFML/SFML.git libs/SFML
     ```
   - **Option 2: Direct Download:**
     - Download SFML from [SFML Download](https://www.sfml-dev.org/download.php).
     - Extract and place it in the `libs/SFML` directory.

2. **JSON for Modern C++:**
   - **Option 1: Git Submodule:**
     ```bash
     git submodule add https://github.com/nlohmann/json.git libs/json
     ```
   - **Option 2: Direct Download:**
     - Download from [JSON for Modern C++ GitHub](https://github.com/nlohmann/json/releases).
     - Extract and place it in the `libs/json` directory.

# Original course description below

# LIBS directory
In this directory, you are required to place all the external libraries your project depends on. 
Although, in principle, you can use git submodules (and place them under this directory), 
for the sake of easily compiling your application, placing the source code of the 
open source libraries is also fine. However, this approach is not applicable to
large dependencies, such as QT.



# List of External Libs

1. [Project1](https://someproject.com/download)
2. [Project2](https://anotherproject.com/download)


> If you are using already compiled library, place it in this folder, and set the linker options appropriately.
> The inlcude files of the dependent library should also be placed in this folder.

