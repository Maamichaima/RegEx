# Regex Engine in C++

A lightweight Regular Expression (Regex) engine implemented in C++. This project provides a basic regex parser and matching engine that supports character matching, special character classes, quantifiers, and backtracking.

The goal of this project is to understand how regular expression engines work internally by implementing the parsing and matching logic without relying on the standard regex library.

## Features

- **Literal characters:** Match exact characters.
- **Wildcard (`.`):** Match any single character.
- **Character classes:** Match specific characters or ranges.
- **Special character classes:** Match digits, non-digits, whitespace, and non-whitespace.
- **Quantifiers:** Support `*`, `+`, and `?`.
- **Backtracking:** Reconsider previous matching decisions when a later pattern element fails.
- **Full-string matching:** Check whether the entire input string matches the pattern.

## Supported Regex Syntax

| Syntax | Description | Example |
|---|---|---|
| `a` | Matches the exact character `a` | `abc` |
| `.` | Matches any single character | `a.c` |
| `\d` | Matches any digit (`0-9`) | `\d\d` |
| `\D` | Matches any non-digit | `\D+` |
| `\s` | Matches whitespace characters | `\s` |
| `\S` | Matches non-whitespace characters | `\S+` |
| `\w` | Matches alphanumeric characters | `\w+` |
| `\W` | Matches non-alphanumeric characters | `\W` |
| `[abc]` | Matches one character from the specified set | `[abc]` |
| `[a-z]` | Matches a character within a range | `[a-z]+` |
| `*` | Matches zero or more occurrences | `a*` |
| `+` | Matches one or more occurrences | `a+` |
| `?` | Matches zero or one occurrence | `a?` |

## How It Works

The engine is divided into two main stages:

### 1. Regex Parsing

The `parce_expretion()` function reads the regex pattern character by character and converts it into a sequence of `RegEx` objects stored in a `std::deque`.

Each element contains:

- `content`: The character or character-set content.
- `type`: The token type (literal, digit, whitespace, wildcard, etc.).
- `quantifier`: The repetition rule applied to the token.

For example:

```cpp
std::string pattern = "\\d+\\.\\d+";
std::deque<RegEx> tokens = parce_expretion(pattern);
```

The parser identifies special characters and converts them into the corresponding token types and quantifiers.

### 2. Regex Matching

The `test()` function processes the parsed tokens against the input string.

It checks each character according to the token type and quantifier.

When a token uses `*`, `+`, or `?`, the engine may need to reconsider how many characters it consumes.

This is handled using a backtracking mechanism.

### 3. Backtracking

The engine uses a `std::stack<BacktrackElement>` to save previous matching decisions.

Each backtracking element stores:

- `isBacktrack`: Indicates whether the token can give back matched characters.
- `charTaken`: Number of characters consumed by the token.
- `regex`: The corresponding regex token.

If a later token fails, `tryBacktrack()` attempts to reduce the number of characters consumed by a previous quantifier and retries matching.

## Project Structure

```text
.
├── RegEx.hpp
├── RegEx.cpp
├── parsing.cpp
├── matching.cpp
└── main.cpp
```

*Note: Adapt the filenames above to match your actual project structure.*

## Usage

Include the header file:

```cpp
#include "RegEx.hpp"
```

Use the `isMatch()` function to test a pattern against an input string:

```cpp
#include "RegEx.hpp"

int main()
{
    std::string pattern = "\\d+\\.\\d+";
    std::string input = "123.45";

    if (isMatch(pattern, input))
        std::cout << "Matched!" << std::endl;
    else
        std::cout << "Not matched!" << std::endl;

    return 0;
}
```

**Expected output:**

```text
Matched!
```

## Compilation

Compile your source files using a C++ compiler:

```bash
c++ -Wall -Wextra -Werror *.cpp -o regex
```

Run the executable:

```bash
./regex
```

## Technologies

- **Language:** C++
- **Standard Library:** `std::deque`, `std::stack`, `std::string`
- **Concepts:** Parsing, tokenization, pattern matching, quantifiers, backtracking.

## Limitations

This is a basic regex engine and does not implement the complete regular expression standard.

Currently, it does not support:

- Grouping with `()`.
- Alternation with `|`.
- Anchors such as `^` and `$`.
- Negated character sets such as `[^abc]`.
- Advanced quantifiers such as `{2,5}`.

## Learning Objectives

This project explores fundamental concepts behind regex engines:

- Understanding regular expression syntax.
- Building a simple parser.
- Representing patterns using custom data structures.
- Implementing matching algorithms.
- Understanding greedy matching and backtracking.
- Managing matching states using stacks and deques.

