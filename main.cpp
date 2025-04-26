#include "RegEx.hpp"

void parce_staret(std::deque<RegEx> &dq)
{
	if(dq.empty())
	{
		std::cout << "Error: Empty deque" << std::endl;
		exit (1);
	}
	else if (dq.back().quantifier == EXACTLY_ONE)
	{
		dq.back().quantifier = ZERO_OR_MORE;
	}
	else
	{
		std::cout << "Error: expretion" << std::endl;
		exit (1);
	}
}

void parce_optional(std::deque<RegEx> &dq)
{
	if(dq.empty())
	{
		std::cout << "Error: Empty deque" << std::endl;
		exit (1);
	}
	else if (dq.back().quantifier == EXACTLY_ONE)
	{
		dq.back().quantifier = ZERO_OR_ONE;
	}
	else
	{
		std::cout << "Error: expretion" << std::endl;
		exit (1);
	}
}

void print(std::deque<RegEx> dq)
{
	int i = 0;
	std::deque<RegEx>::iterator it = dq.begin();

	while(it != dq.end())
	{
		std::cout << "Element " << i++ << ": content = " << it->content 
                  << ", quantifier = " << it->quantifier 
                  << ", type = " << it->type << std::endl;
		it++;
	}
}

void parce_plus(std::deque<RegEx> &dq, char c)
{
	if(dq.empty())
	{
		std::cout << "Error: Empty deque" << std::endl;
		exit (1);
	}
	else if (dq.back().quantifier == EXACTLY_ONE)
	{
		dq.push_back(RegEx(dq.back().content, LITTERAL));
		dq.back().quantifier = ZERO_OR_MORE;
	}
	else
	{
		std::cout << "Error: expretion" << std::endl;
		exit (1);
	}
}

std::deque<RegEx> parce_expretion(std::string str)//p.**
{
	int i = 0;
	std::deque<RegEx> dq;

	while(str[i])
	{
		switch (str[i])
		{
		case '.':
			dq.push_back(RegEx(str[i], ANYTHING));
			dq.back().quantifier = EXACTLY_ONE;
			i++;
			continue;
		case '*':
			parce_staret(dq);
			i++;
			continue;
		case '?':
			parce_optional(dq);
			i++;
			continue;
		case '+':
			parce_plus(dq, str[i]);
			i++;
			continue;
		default:
			dq.push_back(RegEx(str[i], LITTERAL));
			dq.back().quantifier = EXACTLY_ONE;
			// std::cout << "content " << dq.back().content << " type " << dq.back().type << "\n";
			i++;
			continue;
		}
		i++;
	}
	return dq;
}

bool test(std::string str, std::deque<RegEx> dq)//a* 
{
    size_t i = 0;
    size_t tmp = 0;
    std::deque<RegEx>::iterator it = dq.begin();
	std::stack<BacktrackElement> backtrackStack;


    while (it != dq.end())
    {
		if (i >= str.size())
		{
			//i--
			return false;
		}
		char c = str[i];
		// char c = (i < str.size()) ? str[i] : '\0';
		// std::cout << "char -> " << it->content << "\n";
        if (it->type == LITTERAL)
        {
            if (it->quantifier == EXACTLY_ONE)
            {
                if (c != it->content)
				{

                    return false;
				}
				BacktrackStack.push({false, 1, *it});
                i++;
                it++;
            }
            else if (it->quantifier == ZERO_OR_MORE)
            {
				int j = 0;
				while (str[i] == it->content)
				{
					j++;
					i++;
				}
				it++;
				// if (backtrackStack.empty())
				//newdq.push aq
                // if (c == it->content)
				// {
                //     i++;
				// 	//newdq.top().
				// }
                // else
                //     it++;
            }
            else if (it->quantifier == ZERO_OR_ONE)
            {
                if (c == it->content)
                    i++;
                it++;
            }
        }
        else
        {
            std::cout << "Error: Unsupported type in RegEx" << std::endl;
            return false;
        }
    }
	std::cout << i << "\n";
    return (i == str.size() && it == dq.end());
}


int main()
{
    std::string ex = "t*d";
    std::deque<RegEx> dq = parce_expretion(ex);

	print(dq);

    std::string testStr = "ttttt";
    if (test(testStr, dq))
        std::cout << "Matched!" << std::endl;
    else
        std::cout << "Not matched!" << std::endl;

    return 0;
}