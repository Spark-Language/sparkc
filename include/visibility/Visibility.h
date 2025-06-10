//
// Created by Wylan Shoemaker on 6/9/2025.
//

#ifndef SCOPE_H
#define SCOPE_H

#include <string>

// Accessibility levels for tokens
enum class Visibility {
    Private,
    Public,
    Internal,
    Macro,
    None
};

// Convert a Scope to its lowercase keyword form
inline std::string to_string(Visibility s) {
    switch (s) {
        case Visibility::Public: return "public";
        case Visibility::Internal: return "internal";
        case Visibility::Macro: return "macro";
        case Visibility::None: return "none";
        case Visibility::Private: // fallthrough
        default: return "private";
    }
}

// Parse a keyword into a Scope (defaults to Private)
Visibility scopeFromString(const std::string &keyword);

#endif //SCOPE_H
