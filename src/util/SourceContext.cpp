//
// Created by Wylan Shoemaker on 6/2/2025.
//

#include <utility>

#include "../../include/util/SourceContext.h"

SourceContext::SourceContext() = default;

SourceContext::SourceContext(std::string filename)
    : current_file(std::move(filename)) {
}

void SourceContext::set_file(const std::string &filename) {
    current_file = filename;
    current_line = 1;
    current_column = 1;
}

void SourceContext::advance(char c) {
    if (c == '\n') {
        ++current_line;
        current_column = 1;
    } else {
        ++current_column;
    }
}

void SourceContext::advance_tab(int tab_width) {
    current_column += tab_width;
}

void SourceContext::reset() {
    current_line = 1;
    current_column = 1;
}

int SourceContext::line() const {
    return current_line;
}

int SourceContext::column() const {
    return current_column;
}

const std::string &SourceContext::file() const {
    return current_file;
}
