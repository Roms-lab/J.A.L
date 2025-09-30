#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>

bool Break = false;

// The function that processes each line from the file.
void RunCommand(const std::string& commandLine) {
    std::string Command = commandLine;

    // Commands...

    // J.A.L Exit
    if (Command == "exit" || Command == "Exit") {
        Break = true;
    }
    // J.A.L Credits
    else if (Command == "J.A.L.Credits") {
        std::cout << "Founder and Dev -> Zachary.S" << "\n";
        std::cout << "J.A.L -> Just Another Line" << "\n";
    }
    // J.A.L Ipconfig
    else if (Command == "ipconfig") {
        std::system("ipconfig");
    }
    // J.A.L Task Manager Call
    else if (Command == "taskmgr") {
        std::system("taskmgr");
    }
    // J.A.L Run cmd through J.A.L
    else if (Command == "cmd") {
        std::system("cmd");
    }
    // J.A.L Run powershell through J.A.L
    else if (Command == "powershell") {
        std::system("powershell");
    }
    // J.A.L Ping
    else if (Command.rfind("ping ", 0) == 0) {
        // Extract the IP address or domain from the command string
        std::string target = Command.substr(5); // "ping " is 5 characters long

        // Construct the full command to execute
        std::string full_command = "ping " + target;

        // Use std::system to run the command
        std::system(full_command.c_str());
    }
    // J.A.L Ps Powershell Command
    else if (Command == "ps") {
        std::system("powershell.exe -command ps");
    }
    // J.A.L Kill Powershell Command
    else if (Command.rfind("kill ", 0) == 0) {
        std::string pid_str = Command.substr(5);
        std::string full_command = "powershell.exe -command Stop-Process -Force -Id " + pid_str;
        std::system(full_command.c_str());
    }
    // J.A.L Open File Command
    else if (Command.rfind("open ", 0) == 0) {
        std::string Open_Exe = Command.substr(5);
        std::string Full_Cmd = "start " + Open_Exe;
        std::system(Full_Cmd.c_str());
    }
    // J.A.L Print Command
    else if (Command.substr(0, 8) == "display ") {
        std::string text_to_display = Command.substr(8);
        std::cout << text_to_display << std::endl;
    }
    // J.A.L Pause Command
    else if (Command == "pause") {
        std::string Full_Pause = "powershell.exe -command pause";
        std::system(Full_Pause.c_str());
    }
    // J.A.L Color Command
    else if (Command.rfind("color ", 0) == 0) {
        std::system(("color " + Command.substr(6)).c_str());
    }
    // J.A.L Wait Command
    else if (Command.rfind("wait ", 0) == 0) {
        std::string wait_seconds = Command.substr(5);
        std::string full_command = "timeout /t " + wait_seconds + " /nobreak > nul";
        std::system(full_command.c_str());
    }
    // J.A.L pwd Command
    else if (Command.rfind("pwd", 0) == 0) {
        std::string pwd = Command.substr(3);
        std::string full_pwd = "echo %cd%";
        std::system(full_pwd.c_str());
    }
    // J.A.L cd Command
    else if (Command.rfind("cd ", 0) == 0) {
        std::string cd = Command.substr(3);
        std::string full_cd = "cd " + cd;
        std::system(full_cd.c_str());
    }
    // J.A.L clear Command
    else if (Command.rfind("clear", 0) == 0) {
        std::string clear = Command.substr(5);
        std::string full_clear = "cls";
        std::system(full_clear.c_str());
    }
    // J.A.L cat Command
    else if (Command.rfind("cat ", 0) == 0) {
        std::string cat = Command.substr(4);
        std::string full_cat = "type " + cat;
        std::system(full_cat.c_str());
    }
    // J.A.L pip install Command -- Only if python installed --
    else if (Command.rfind("pip install ", 0) == 0) {
        std::string pip_install = Command.substr(12);
        std::string full_pip = "pip install " + pip_install;
        std::system(full_pip.c_str());
    }
    // J.A.L Empty Line
    else if (Command.empty()) {
        // Do nothing for empty input.
    }
    // J.A.L No Command Found
    else {
        std::cout << "Error Code 001. Command not found.";
    }
}

// Function to read and process the .jalc file based on command-line arguments.
void processJalcFileFromArgs(int argc, char* argv[]) {
    // Check if a file path was provided.
    if (argc < 2) {
        throw std::runtime_error("No file specified. Usage: <program> <filename>");
    }

    // The first command-line argument (argv[1]) is the file path.
    std::string filePath = argv[1];

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            RunCommand(line);
        }
    }

    inputFile.close();
}

int main(int argc, char* argv[]) {
    std::string command;
    std::cout << "-- J.A.L. --" << std::endl;

    // Check if a file is being processed from command-line
    if (argc >= 2) {
        try {
            processJalcFileFromArgs(argc, argv);
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }

    // Interactive loop
    while (!Break) {
        std::cout << "\n";
        std::cout << ">>> ";
        std::getline(std::cin, command);
        RunCommand(command);
    }
    return 0;
}
