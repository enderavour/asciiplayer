#ifndef ASCIIPLAYER_IMPL_H
#define ASCIIPLAYER_IMPL_H

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <chrono>

namespace player
{
    DWORD set_terminal_attrs(HANDLE &hCons, int16_t width, int16_t height);
    std::string img_to_ascii(const cv::Mat &m);
    void display(const std::string &path, const std::string &audpath, int32_t width, int32_t height, HANDLE &buf);
};

#endif