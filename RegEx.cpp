#include "RegEx.hpp"

RegEx::RegEx(char content, TokenType type)
{
	this->content = content;
	this->type = type;
	this->quantifier = EXACTLY_ONE;
}