#include <iostream>
#include <cstdlib>
#include <string>

bool Break = false;

void RunCommand(std::string& Command) {
    std::getline(std::cin >> std::ws, Command);

    // Commands

    // J.A.L Exit
    if (Command == "exit" or Command == "Exit") {
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
    // J.A.L Empty Line
    else if (Command.empty()) {
        // Do nothing for empty input.
    }
    // J.A.L No Command Found
    else {
        std::cout << "Error Code 001. Command not found.";
    }
}

int main() {
    std::string Command;
    std::cout << "-- J.A.L. --";

    while (true) {
        std::cout << "\n";
        // Run Selected Command
        RunCommand(Command);

        if (Break == true) {
            break;
        }
    }
    return 0;
}
