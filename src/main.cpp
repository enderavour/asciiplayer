#include "include/asciiplayer.hpp"

int32_t main(int32_t argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: asciivid <*.mp4>\n";
        return -1;
    }

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    std::string video_name = std::string(argv[1]);
    char cmd[50];
    std::sprintf(cmd, "ffmpeg -i %s -vn audio.wav", video_name.c_str());
    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);
    si.dwFlags |= STARTF_USESTDHANDLES;
    HANDLE hNull = CreateFileA("NUL", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
    si.hStdOutput = hNull;
    si.hStdInput = hNull;
    si.hStdError = hNull;

    std::cout << "Extracting audio..." << std::endl;
    CreateProcessA(
        nullptr,
        cmd,
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &si,
        &pi
    );

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hNull);
    std::cout << "Ready!" << std::endl;

    std::system("cls");

    DWORD dws = player::set_terminal_attrs(h, 100, 30);
    SetConsoleCursorPosition(h, {0, 0});
    player::display(video_name, "audio.wav", 100, 30, h);

    system("cls");

    CONSOLE_CURSOR_INFO ci{dws, true};
    SetConsoleCursorInfo(h, &ci);

    std::cout << "Deleting audio...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::system("del audio.wav");
    return 0;
}