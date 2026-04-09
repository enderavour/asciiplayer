#include "include/asciiplayer.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "include/miniaudio.h"

const int32_t WIDTH = 100;
const int32_t HEIGHT = 30;
const int32_t FPS = 265;

const std::string_view ASCII_CHARS = " .:-=+*#%@";

DWORD player::set_terminal_attrs(HANDLE &hCons, int16_t width, int16_t height)
{
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hCons, &cci);
    SMALL_RECT sm = {420, 51, 102, 32};
    cci.bVisible = false;
    SetConsoleScreenBufferSize(hCons, {102, 80});
    SetConsoleWindowInfo(hCons, TRUE, &sm);
    SetConsoleCursorInfo(hCons, &cci);
    return cci.dwSize;
}

std::string player::img_to_ascii(const cv::Mat &m)
{
    int32_t rows = m.rows;
    int32_t cols = m.cols;

    std::string ascii;

    for (int32_t i = 0; i < rows; ++i)
    {
        for (int32_t j = 0; j < cols; ++j)
        {
            uchar pixv = m.at<uchar>(i, j);

            int ind = (pixv * (ASCII_CHARS.size() - 1)) / 255;
            ascii += ASCII_CHARS[ind];
        }
        ascii += "\n";
    }
    return ascii;
}

void player::display(const std::string &path, const std::string &audpath, int32_t width, int32_t height, HANDLE &buf)
{
    cv::VideoCapture vc(path);
    ma_engine eng;
    ma_engine_init(nullptr, &eng);

    cv::Mat frame, grayframe;

    ma_engine_play_sound(&eng, audpath.c_str(), nullptr);
    while (vc.read(frame))
    {
        SetConsoleCursorPosition(buf, {0, 0});

        cv::cvtColor(frame, grayframe, cv::COLOR_BGR2GRAY);

        cv::resize(grayframe, grayframe, cv::Size(width, height));

        std::string ascii = player::img_to_ascii(grayframe);

        std::cout << ascii << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    }

    vc.release();
    ma_engine_uninit(&eng);
}


