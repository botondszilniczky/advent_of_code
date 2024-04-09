#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Present
{
    size_t l;
    size_t w;
    size_t h;

    size_t getSurface()
    {
        return (2*l*w) + (2*l*h) + (2*w*h);
    }

    size_t getVolume()
    {
        return l*w*h;
    }

    size_t getSmallestSurface()
    {
        return std::min({l*h, l*w, h*w});
    }

    size_t getSmallestPerimeter()
    {
        return std::min({2*(l+w), 2*(l+h), 2*(w+h)});
    }

};


std::vector<Present> readFile(std::string filename)
{
    std::vector<Present> presents;
    std::ifstream file(filename);
    size_t length;
    size_t width;
    size_t height;
    char trash;
    while (file >> length >> trash >> width >> trash >> height)
    {
        Present present;
        //std::cout << length << " " << width << " " << height << std::endl;
        present.l = length;
        present.w = width;
        present.h = height;
        presents.push_back(present);
    }
    file.close();
    return presents;
}

void solve(std::vector<Present> presents)
{
    size_t result = 0;
    for(Present p : presents)
    {
        result += p.getSurface();
        result += p.getSmallestSurface();
        //std::cout << p.getSurface() << " " << p.getSmallestSurface() << std::endl;
        //std::cout << result << std::endl;
    }
    std::cout << "Result 1:\t" << result << std::endl;
}

void solve2(std::vector<Present> presents)
{
    size_t result = 0;
    for(Present p : presents)
    {
        result += p.getSmallestPerimeter();
        result += p.getVolume();
    }
    std::cout << "Result 2:\t" << result << std::endl;
}

int main(int argc, char const *argv[])
{
    std::vector<Present> presents = readFile("input.txt");
    solve(presents);
    solve2(presents);
    return 0;
}
