#include "RegEx.hpp"


int main()
{
    std::string ex = "\\d+.\\d+\r\n";
    std::deque<RegEx> dq = parce_expretion(ex);

	// print(dq);
    std::string testStr = "8.5\r\n";
    if (isMatch(ex, testStr))
        std::cout << "Matched!" << std::endl;
    else
        std::cout << "Not matched!" << std::endl;
    return 0;
}