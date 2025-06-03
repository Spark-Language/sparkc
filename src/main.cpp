#include <cstdio>
#include "../include/tokens/TokenCategory.h"

int main() {

    auto token = TokenType::APOSTROPHE;
    auto type = token_type_to_string(token);
    auto category = category_to_string(get_token_category(token));

    printf("%s -> %s\n", type.data(), category.data());

    return 0;
}
