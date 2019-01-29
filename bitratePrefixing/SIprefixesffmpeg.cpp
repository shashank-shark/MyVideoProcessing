#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec(const char* cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    auto pipe = popen(cmd, "r");
    
    if (!pipe) throw std::runtime_error("popen() failed!");
    
    while (!feof(pipe))
    {
        if (fgets(buffer.data(), 128, pipe) != nullptr)
            result += buffer.data();
    }
    
    auto rc = pclose(pipe);
    
    if (rc == EXIT_SUCCESS)
    {
        std::cout << "SUCCESS\n";
    }
    else
    {
        std::cout << "FAILED\n";
    }
    
    return result;
}

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Start\n";
    std::string res;
    
    res = exec("ffmpeg -i ../bird.mp4 -b:v 1500000 output.mp4");

    /* also could be written as */

    res = exec("ffmpeg -i ../bird.mp4 -b:v 1500K output.mp4");
    res = exec("ffmpeg -i ../bird.mp4 -b:v 1.5M output.mp4");
    res = exec("ffmpeg -i ../bird.mp4 -b:v 0.0015G output.mp4");

    std::cout << "OUTPUT" << res << std::endl;
    cout<<"End\n";
    return 0;
}