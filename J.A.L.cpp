#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

// -------------------------------------------------
// GLOBAL STATE
// -------------------------------------------------
bool Break = false;          // stops the whole interpreter
bool UsePowerShell = false;  // true when we are in PowerShell mode
bool UseCmd = false;         // true when we are in Cmd mode

// -------------------------------------------------
// CONVERT JAL TO C
// -------------------------------------------------

module J.A.L_Converter;

// -------------------------------------------------
// RUN ONE COMMAND (now accepts a constant string reference)
// This version is safer for processing commands from a file
// since it doesn't modify the input string.
// -------------------------------------------------
void RunCommand(const std::string& Command) {
    // -------------------------------------------------
    //  Mode handling and normal J.A.L. commands
    // -------------------------------------------------
    std::string current_command = Command;

    if (UseCmd && current_command != "exitcmd") {
        std::string escaped = current_command;
        size_t pos = 0;
        while ((pos = escaped.find('\"', pos)) != std::string::npos) {
            escaped.insert(pos, "\\");
            pos += 2;
        }
        std::string cmd_line = "cmd /c \"" + escaped + "\"";
        std::system(cmd_line.c_str());
        return;
    }

    if (UsePowerShell && current_command != "exitps") {
        std::string escaped = current_command;
        size_t pos = 0;
        while ((pos = escaped.find('\"', pos)) != std::string::npos) {
            escaped.insert(pos, "\\");
            pos += 2;
        }
        std::string ps_cmd = "powershell -NoLogo -NoProfile -Command \"" + escaped + "\"";
        std::system(ps_cmd.c_str());
        return;
    }

    // J.A.L Exit
    if (current_command == "exit" || current_command == "Exit") {
        Break = true;
    }
    // J.A.L Credits
    else if (current_command == "J.A.L.Credits") {
        std::cout << "Founder and Dev -> Zachary.S\n";
        std::cout << "J.A.L -> Just Another Line\n";
    }
    // J.A.L Ipconfig
    else if (current_command == "ipconfig") {
        std::system("ipconfig");
    }
    // J.A.L Task Manager Call
    else if (current_command == "taskmgr") {
        std::system("taskmgr");
    }
    else if (current_command == "RDC") {
        std::system("mstsc");
    }
    // Start PowerShell mode (now only for the 'powershell' command)
    else if (current_command == "powershell") {
        UsePowerShell = true;
        UseCmd = false;
        std::cout << "[PowerShell mode] Type commands – they will be executed via PowerShell.\n";
        std::cout << "Enter \"exitps\" to return to normal J.A.L. prompt.\n";
    }
    // Leave PowerShell mode
    else if (current_command == "exitps") {
        UsePowerShell = false;
        std::cout << "[PowerShell mode] exited.\n";
    }
    // Start Cmd mode
    else if (current_command == "cmd") {
        UseCmd = true;
        UsePowerShell = false;
        std::cout << "[Cmd mode] Type commands – they will be executed via cmd.exe.\n";
        std::cout << "Enter \"exitcmd\" to return to normal J.A.L. prompt.\n";
    }
    // Leave Cmd mode
    else if (current_command == "exitcmd") {
        UseCmd = false;
        std::cout << "[Cmd mode] exited.\n";
    }
    else if (current_command.rfind("ping ", 0) == 0) {
        std::string target = current_command.substr(5);
        std::system(("ping " + target).c_str());
    }
    else if (current_command.rfind("kill ", 0) == 0) {
        std::string pid_str = current_command.substr(5);
        std::system(("powershell.exe -command Stop-Process -Force -Id " + pid_str).c_str());
    }
    else if (current_command.rfind("open ", 0) == 0) {
        std::string Open_Exe = current_command.substr(5);
        std::system(("start " + Open_Exe).c_str());
    }
    else if (current_command.substr(0, 8) == "display ") {
        std::cout << current_command.substr(8) << std::endl;
    }
    else if (current_command == "pause") {
        std::system("powershell.exe -command pause");
    }
    else if (current_command == "date") {
        std::system("date /t");
        std::system("time /t");
    }
    else if (current_command.rfind("color ", 0) == 0) {
        std::system(("color " + current_command.substr(6)).c_str());
    }
    else if (current_command.rfind("wait ", 0) == 0) {
        std::string wait_seconds = current_command.substr(5);
        std::system(("timeout /t " + wait_seconds + " /nobreak > nul").c_str());
    }
    else if (current_command.rfind("pwd", 0) == 0) {
        std::system("echo %cd%");
    }
    else if (current_command.rfind("cd ", 0) == 0) {
        std::system(("cd " + current_command.substr(3)).c_str());
    }
    else if (current_command.rfind("clear", 0) == 0) {
        std::system("cls");
    }
    else if (current_command.rfind("cat ", 0) == 0) {
        std::system(("type " + current_command.substr(4)).c_str());
    }
    else if (current_command.rfind("pip install ", 0) == 0) {
        std::system(("pip install " + current_command.substr(12)).c_str());
    }
    else if (current_command.rfind("ps", 0) == 0) {
        // Execute the "ps" command directly via the system shell
        // This relies on "ps" being aliased or available in the system path
        std::system("powershell -command ps");
    }
    else if (current_command.rfind("JCompile", 0) == 0) {
        ConvertJAL();
        std::cout << "Finsied Compiling. See Output.c for Source.\n";
    }
    else if (current_command.empty()) {
        // nothing
    }
    else {
        std::cout << "Error Code 001. Command not found.";
    }
}

// -------------------------------------------------
int main(int argc, char* argv[]) {
    std::cout << "-- J.A.L. --";
    std::string Command;

    // Check if a file path was provided as a command-line argument
    if (argc > 1) {
        std::string filePath = argv[1];
        std::ifstream inputFile(filePath);

        if (!inputFile.is_open()) {
            std::cerr << "\nError: Could not open file " << filePath << std::endl;
            return 1;
        }

        std::cout << "\nExecuting commands from file: " << filePath << std::endl;
        while (std::getline(inputFile, Command)) {
            // Check for mode-specific keywords before trimming whitespace
            if ((UseCmd && Command == "exitcmd") || (UsePowerShell && Command == "exitps") || Command == "exit") {
                RunCommand(Command);
            }
            else {
                // Trim leading whitespace for command parsing
                size_t first_char = Command.find_first_not_of(" \t\n\r");
                if (std::string::npos != first_char) {
                    Command = Command.substr(first_char);
                }
                else {
                    Command = ""; // Line was only whitespace
                }
                RunCommand(Command);
            }
            if (Break) break;
        }
        inputFile.close();
    }
    else {
        // Original loop for interactive console input
        while (true) {
            std::cout << "\n";
            std::getline(std::cin >> std::ws, Command);
            RunCommand(Command);
            if (Break) break;
        }
    }
    return 0;
}
