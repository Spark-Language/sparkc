//
// Created by Wylan Shoemaker on 6/9/2025.
//

#include "../../include/visibility/Visibility.h"

#include <algorithm>

Visibility scopeFromString(const std::string& keyword) {
    std::string lower = keyword;
    std::ranges::transform(lower, lower.begin(),
                           [](const unsigned char c){ return std::tolower(c); });

    if (lower == "public")   return Visibility::Public;
    if (lower == "internal") return Visibility::Internal;
    return Visibility::Private;
}