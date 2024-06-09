#include <fmt/core.h>

#include <iostream>
#include <thread>

#include "shape.h"

Rectangle::Rectangle(int width, int height) : width_(width), height_(height) {}

int Rectangle::GetSize() const {
    std::thread t([this]() { std::cout << "Calulate .." << std::endl; });
    t.join();

    fmt::print("width : {}\n", width_ * height_);

    // 직사각형의 넓이를 리턴한다.
    return width_ * height_;
}