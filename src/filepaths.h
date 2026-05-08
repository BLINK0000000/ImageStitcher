#include <filesystem>

namespace fp
{
    inline const std::filesystem::path parentDir = std::filesystem::current_path().parent_path();
    inline const std::filesystem::path assetsDir = parentDir / "assets";
    inline const std::filesystem::path testsDir = parentDir / "tests";
    
    inline const std::filesystem::path leftImagePath = assetsDir / "leftTest.png";
    inline const std::filesystem::path rightImagePath = assetsDir / "rightTest.png";
    
    inline const std::filesystem::path leftImageOutTestPath = testsDir / "images/leftOutTest.png";
    inline const std::filesystem::path rightImageOutTestPath = testsDir / "images/rightOutTest.png";

}