#pragma once

#include <string>

struct parse_return
{
    int i;
    int val;
    bool err = false;
};

parse_return eval_expr(std::string expr);

parse_return parse_expression(int i, std::string s);

parse_return parse_term(int i, std::string s);

parse_return parse_number(int i, std::string s);

int skip_leading_whitespace(int i, std::string s);