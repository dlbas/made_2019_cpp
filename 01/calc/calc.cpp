#include <string>
#include <iostream>
#include <ctype.h>

#include "calc.hpp"

parse_return eval_expr(std::string s)
{
    int i = skip_leading_whitespace(0, s);

    return parse_expression(i, s);
}

parse_return parse_expression(int i, std::string s)
{
    i = skip_leading_whitespace(i, s);

    int state = 0;

    parse_return ret;

    while (i < s.length())
    {
        i = skip_leading_whitespace(i, s);

        if (isdigit(s.at(i)))
        {
            parse_return r = parse_number(i, s);
            if (r.err)
            {
                return r;
            }
            int num = r.val;
            i = r.i;
            state += num;
        }
        else if (s[i] == '+')
        {
            i = skip_leading_whitespace(i + 1, s);
            parse_return r = parse_term(i, s);
            if (r.err)
            {
                return r;
            }
            i = r.i;
            state += r.val;
        }
        else if (s[i] == '-')
        {
            i = skip_leading_whitespace(i + 1, s);
            parse_return r = parse_term(i, s);
            if (r.err)
            {
                return r;
            }
            i = r.i;
            state -= r.val;
        }
        else if (s[i] == '*')
        {
            i = skip_leading_whitespace(i + 1, s);
            parse_return r = parse_term(i, s);
            if (r.err)
            {
                return r;
            }
            i = r.i;
            state *= r.val;
        }
        else if (s[i] == '/')
        {
            i = skip_leading_whitespace(i + 1, s);
            parse_return r = parse_term(i, s);
            if (r.err)
            {
                return r;
            }
            i = r.i;
            state /= r.val;
        }
        else
        {
            ret.err = true;
            std::cerr << "error parsing token " << s[i] << std::endl;
            return ret;
        }
    }

    ret.val = state;
    return ret;
}

parse_return parse_number(int i, std::string s)
{
    int j = i;

    while (j < s.length() && isdigit(s[j]))
    {
        j++;
    }

    parse_return ret;

    std::string substr = s.substr(i, j);
    if (substr.length() == 0)
    {
        ret.i = j;
        ret.err = true;
        return ret;
    }

    ret.i = j;
    ret.val = std::stoi(substr);
    return ret;
}

parse_return parse_term(int i, std::string s)
{
    parse_return ret;

    if (i >= s.length())
    {
        ret.err = true;
        return ret;
    }

    ret = parse_number(i, s);

    if (ret.err)
    {
        return ret;
    }

    i = ret.i;
    int n = ret.val;

    i = skip_leading_whitespace(ret.i, s);

    if (i >= s.length() || s[i] != '*' && s[i] != '/')
    {
        ret.i = i;
        ret.val = n;
        return ret;
    }

    char symbol = s[i];

    i = skip_leading_whitespace(i + 1, s);

    if (symbol == '*')
    {
        ret = parse_term(i, s);
        ret.val = n * ret.val;
        return ret;
    }
    else if (symbol == '/')
    {
        ret = parse_term(i, s);
        ret.val = n / ret.val;
        return ret;
    }

    std::cerr << "wrong token in term " << s[i] << std::endl;
    ret.err = true;
    return ret;
}

int skip_leading_whitespace(int i, std::string s)
{
    for (int j = i; j < s.length(); j++)
    {
        if (!isspace(s[j]))
        {
            return j;
        }
    }

    return i;
}