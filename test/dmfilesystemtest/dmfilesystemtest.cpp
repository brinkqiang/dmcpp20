#include <fstream>
#include <iostream>
#include <filesystem>
#include <direct.h>

int main()
{
    std::filesystem::create_directories("sandbox/a/b");
    std::ofstream("sandbox/file1.txt");
    std::ofstream("sandbox/file2.txt");
    for (auto& p : std::filesystem::directory_iterator("sandbox"))
    {
        std::cout << std::filesystem::canonical(p) << std::endl;
    }
    std::filesystem::remove_all("sandbox");

    rmdir("sandbox");
}
