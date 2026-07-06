#include <filesystem>

namespace fp
{
    typedef std::filesystem::path path;

    inline const path parentDir = std::filesystem::current_path().parent_path();
    inline const path assetsDir = parentDir / "assets";
    inline const path testsDir = parentDir / "tests";
    inline const path imageTestsDir = testsDir / "images";

}