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

void escapedCharacter(std::deque< std::deque<Element> >& C, char escapedChar) {
    switch (escapedChar)
    {
        case 'd':
            C.back().push_back(Element(DIGIT, '\0'));
            break;
        case 'D':
            C.back().push_back(Element(NOTDIGIT, '\0'));
            break;
        case 'w':
            C.back().push_back(Element(ALPHANUM, '\0'));
            break;
        case 'W':
            C.back().push_back(Element(NOTALPHANUM, '\0'));
            break;
        case 's':
            C.back().push_back(Element(WHITESPACE, '\0'));
            break;
        case 'S':
            C.back().push_back(Element(NOTWHITESPACE, '\0'));
            break;
        default:
            C.back().push_back(Element(LITTERAL, escapedChar));
            break;
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
		case '\\':
			if(i + 1 >= std.size())
			{
				std::cout << "eroor ?";
				exit(1);
			}
			escapedCharacter(dq, str[i]);
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

void print_stack(std::stack<BacktrackElement> backtrackStack)
{
	while(!backtrackStack.empty())
	{
		std::cout << "quantifier = " << backtrackStack.top().regex.quantifier 
		<< ", content = " << backtrackStack.top().regex.content << " chartaken " << backtrackStack.top().charTaken << std::endl; 
		backtrackStack.pop();
	}
}

std::stack<BacktrackElement> backtrackStack;

bool tryBacktrack(std::stack<BacktrackElement> &backtrackStack, size_t &index, std::deque<RegEx>::iterator &it)
{
	while (!backtrackStack.empty())
	{
		if (backtrackStack.top().isBacktrack && backtrackStack.top().charTaken)
		{
			backtrackStack.top().charTaken--;
			index--;
			return true;
		}
		else
		{
			index -= backtrackStack.top().charTaken;
			backtrackStack.pop();
			it--;
		}
	}
	return false;
}

bool test(std::string str, std::deque<RegEx> dq)//. [] \d \s \w
{
    size_t i = 0;
    size_t tmp = 0;
    std::deque<RegEx>::iterator it = dq.begin();


    while (it != dq.end())
    {
		if (i >= str.size())
		{
			if (tryBacktrack(backtrackStack, i, it))
				continue ;
			return false;
		}
		char c = str[i];
        if (it->type == LITTERAL)
        {
            if (it->quantifier == EXACTLY_ONE)
            {
                if (c != it->content)
				{
					if (tryBacktrack(backtrackStack, i, it))
						continue ;
                    return false;
				}
				backtrackStack.push({false, 1, *it});
                i++;
                it++;
            }
            else if (it->quantifier == ZERO_OR_MORE)
            {
				int j = 0;
				while (str[i] && str[i] == it->content)
				{
					j++;
					i++;
				}
				backtrackStack.push({true, j, *it});
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
				{
					backtrackStack.push({true, 1, *it});
                    i++;
				}
				else
					backtrackStack.push({true, 0, *it});
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
    std::string ex = "t?t*t";
    std::deque<RegEx> dq = parce_expretion(ex);

	// print(dq);

    std::string testStr = "t";
    if (test(testStr, dq))
        std::cout << "Matched!" << std::endl;
    else
        std::cout << "Not matched!" << std::endl;
	print_stack(backtrackStack);
    return 0;
}