#include "components.hpp"

InputOption inputOption(bool password)
{
    InputOption option{InputOption::Default()};
    option.multiline = false;
    option.password = password;
    return option;
}