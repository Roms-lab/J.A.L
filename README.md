# J.A.L.

**J**ust **A**nother **L**ine.

J.A.L. is a hybrid command-line shell and interpreter that elevates the standard terminal experience. Built in C++ for maximum performance, J.A.L. offers its own intuitive command language while seamlessly integrating with and hosting existing shell environments like Batch and PowerShell. It's the ultimate tool for developers who want native speed, modern features, and complete compatibility with existing scripting ecosystems.

## ✨ Key Features

-   **High-Performance Core**: Written entirely in C++, J.A.L. delivers blazing-fast execution for native commands.
-   **Seamless Shell Integration**: Type `cmd` or `powershell` to instantly enter a persistent, interactive session of that shell, all within the J.A.L. terminal.
-   **Smart Command Dispatch**: J.A.L. intelligently routes external commands to the correct underlying shell, so you can run `ipconfig` or any other external command without thinking about where it lives.
-   **Extensible and Modern**: Easily add new commands by writing simple C++ functions and integrating them into J.A.L.'s core.
-   **Command Language**: A clean, intuitive command language for scripting and automation, designed for modern development workflows.

## 🚀 Getting Started

Follow these steps to build and run J.A.L. on your machine using GCC.

### Prerequisites

-   A C++ compiler (like GCC or MinGW on Windows)

### Installation

1.  **Clone the repository**:
    ```sh
    git clone https://github.com/Roms-lab/J.A.L.git
    cd J.A.L
    ```
2.  **Build with GCC**:
    ```sh
    g++ -o jal main.cpp [list-all-other-cpp-files-here] -std=c++17
    ```
    *Note: The `-std=c++17` flag enables modern C++ features. You may need to add additional flags or link specific libraries depending on your implementation.*
3.  **Run J.A.L.**:
    ```sh
    # On Windows
    .\jal.exe
    
    # On Linux/macOS
    ./jal
    ```

## 💻 Usage

J.A.L. offers a straightforward command-line interface.

### Basic Commands

```sh
# A custom J.A.L. command
custom_jal_command arg1 arg2

# Seamlessly switch to PowerShell
powershell
PS C:\> Get-Process | Sort-Object -Descending

# Or switch to Command Prompt
cmd
> dir C:\

# Execute an external command via the integrated shell
ipconfig /all

```
### Supported Operating Systems
**Windows**: ✅

**Linux**: ❌

**MacOs**: ❌
