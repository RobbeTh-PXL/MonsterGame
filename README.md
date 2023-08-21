# MonsterGame

A game about killing monsters

## How to install

To run a C++ program on a clean Windows PC, you'll need to follow these general steps:

1. **Install a C++ Compiler**:
   You need a C++ compiler to compile and build your C++ code into an executable file. One popular option for Windows is **MinGW-w64**, which provides the GCC compiler for Windows.

   - Download the MinGW-w64 installer: https://mingw-w64.org/doku.php
   - During installation, make sure to select the "Add to PATH" option so you can access the compiler from the command prompt.

2. **Clone this project**:
   Use gitbash or any other github client to clone this repo.

3. **Open Command Prompt**:
   Press `Win + R`, type `cmd`, and press Enter to open the Command Prompt.

4. **Navigate to Your Program Directory**:
   Use the `cd` command to navigate to the directory where your C++ files are located.

5. **Compile Your Code**:
   Use the compiler to compile your code. For example, if you have a file named `MonsterGame.cpp`, you can compile it like this using MinGW-w64:
   
   ```sh
   g++ -o Game MonsterGame.cpp
   ```

   This will generate an executable file named `myprogram.exe`.

6. **Run the Executable**:
   Once your program is compiled, you can run it from the command prompt:
   
   ```sh
   Game
   ```

Remember that you need to install a C++ compiler on the clean Windows PC before you can compile and run your code. Additionally, ensure that you have the necessary libraries (like `iostream`, `fstream`, etc.) included correctly in your code.

If you're using an Integrated Development Environment (IDE) like Visual Studio, Code::Blocks, or CLion, the process may differ slightly, but the general steps remain the same: install a compiler, create your code files, compile, and run. IDEs often simplify this process by providing a graphical interface for managing projects, code editing, compilation, and execution.
