#include <iostream>
#include <cstdlib>
#include <string>

// -------------------------------------------------
// GLOBAL STATE
// -------------------------------------------------
bool Break = false;          // stops the whole interpreter
bool UsePowerShell = false;  // true when we are in PowerShell mode
bool UseCmd = false;         // true when we are in Cmd mode

// -------------------------------------------------
// RUN ONE COMMAND
// -------------------------------------------------
void RunCommand(std::string& Command) {
    std::getline(std::cin >> std::ws, Command);

    // -------------------------------------------------
    //  If we are already in Cmd mode, forward the line to cmd.exe
    // -------------------------------------------------
    if (UseCmd && Command != "exitcmd") {
        // Escape double quotes for the /c argument
        std::string escaped = Command;
        size_t pos = 0;
        while ((pos = escaped.find('\"', pos)) != std::string::npos) {
            escaped.insert(pos, "\\");
            pos += 2;               // skip the inserted backslash and the quote
        }
        std::string cmd_line = "cmd /c \"" + escaped + "\"";
        std::system(cmd_line.c_str());
        return;                    // back to the input loop
    }

    // -------------------------------------------------
    //  If we are already in PowerShell mode, forward the line to PowerShell
    // -------------------------------------------------
    if (UsePowerShell && Command != "exitps") {
        // Escape double quotes for the PowerShell argument
        std::string escaped = Command;
        size_t pos = 0;
        while ((pos = escaped.find('\"', pos)) != std::string::npos) {
            escaped.insert(pos, "\\");
            pos += 2;
        }
        std::string ps_cmd = "powershell -NoLogo -NoProfile -Command \"" + escaped + "\"";
        std::system(ps_cmd.c_str());
        return;
    }

    // -------------------------------------------------
    //  Normal J.A.L. commands
    // -------------------------------------------------

    // J.A.L Exit
    if (Command == "exit" || Command == "Exit") {
        Break = true;
    }
    // J.A.L Credits
    else if (Command == "J.A.L.Credits") {
        std::cout << "Founder and Dev -> Zachary.S\n";
        std::cout << "J.A.L -> Just Another Line\n";
    }
    // J.A.L Ipconfig
    else if (Command == "ipconfig") {
        std::system("ipconfig");
    }
    // J.A.L Task Manager Call
    else if (Command == "taskmgr") {
        std::system("taskmgr");
    }

    // -------------------------------------------------
    //  Mode handling (PowerShell & Cmd)
    // -------------------------------------------------
    // Start PowerShell mode
    else if (Command == "ps" || Command == "powershell") {
        UsePowerShell = true;
        UseCmd = false;   // make the modes exclusive
        std::cout << "[PowerShell mode] Type commands – they will be executed via PowerShell.\n";
        std::cout << "Enter \"exitps\" to return to normal J.A.L. prompt.\n";
    }
    // Leave PowerShell mode
    else if (Command == "exitps") {
        UsePowerShell = false;
        std::cout << "[PowerShell mode] exited.\n";
    }
    // Start Cmd mode
    else if (Command == "cmd") {
        UseCmd = true;
        UsePowerShell = false;   // make the modes exclusive
        std::cout << "[Cmd mode] Type commands – they will be executed via cmd.exe.\n";
        std::cout << "Enter \"exitcmd\" to return to normal J.A.L. prompt.\n";
    }
    // Leave Cmd mode
    else if (Command == "exitcmd") {
        UseCmd = false;
        std::cout << "[Cmd mode] exited.\n";
    }

    // -------------------------------------------------
    //  The rest of the original commands (unchanged)
    // -------------------------------------------------
    else if (Command.rfind("ping ", 0) == 0) {
        std::string target = Command.substr(5);
        std::system(("ping " + target).c_str());
    }
    else if (Command.rfind("kill ", 0) == 0) {
        std::string pid_str = Command.substr(5);
        std::system(("powershell.exe -command Stop-Process -Force -Id " + pid_str).c_str());
    }
    else if (Command.rfind("open ", 0) == 0) {
        std::string Open_Exe = Command.substr(5);
        std::system(("start " + Open_Exe).c_str());
    }
    else if (Command.substr(0, 8) == "display ") {
        std::cout << Command.substr(8) << std::endl;
    }
    else if (Command == "pause") {
        std::system("powershell.exe -command pause");
    }
    else if (Command == "date") {
        std::system("date /t");
        std::system("time /t");
    }
    else if (Command.rfind("color ", 0) == 0) {
        std::system(("color " + Command.substr(6)).c_str());
    }
    else if (Command.rfind("wait ", 0) == 0) {
        std::string wait_seconds = Command.substr(5);
        std::system(("timeout /t " + wait_seconds + " /nobreak > nul").c_str());
    }
    else if (Command.rfind("pwd", 0) == 0) {
        std::system("echo %cd%");
    }
    else if (Command.rfind("cd ", 0) == 0) {
        std::system(("cd " + Command.substr(3)).c_str());
    }
    else if (Command.rfind("clear", 0) == 0) {
        std::system("cls");
    }
    else if (Command.rfind("cat ", 0) == 0) {
        std::system(("type " + Command.substr(4)).c_str());
    }
    else if (Command.rfind("pip install ", 0) == 0) {
        std::system(("pip install " + Command.substr(12)).c_str());
    }
    else if (Command.empty()) {
        // nothing
    }
    else {
        std::cout << "Error Code 001. Command not found.";
    }
}

// -------------------------------------------------
int main() {
    std::string Command;
    std::cout << "-- J.A.L. --";

    while (true) {
        std::cout << "\n";
        RunCommand(Command);
        if (Break) break;
    }
    return 0;
}
