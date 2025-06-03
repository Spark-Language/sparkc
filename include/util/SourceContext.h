//
// Created by Wylan Shoemaker on 6/2/2025.
//

#ifndef SOURCE_CONTEXT_H
#define SOURCE_CONTEXT_H

#pragma once

#include <string>

class SourceContext {
public:
    SourceContext();

    explicit SourceContext(std::string filename);

    void set_file(const std::string &filename);

    void advance(char c);

    void advance_tab(int tab_width = 4); // Optional: treat tab spacing
    void reset();

    [[nodiscard]] int line() const;

    [[nodiscard]] int column() const;

    [[nodiscard]] const std::string &file() const;

private:
    std::string current_file;
    int current_line = 1;
    int current_column = 1;
};


#endif //SOURCE_CONTEXT_H
