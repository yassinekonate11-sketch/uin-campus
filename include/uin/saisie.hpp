#pragma once

#include <string>
#include <string_view>

namespace uin {

double lireNote(std::string_view invite);
int lireEntier(std::string_view invite, int min, int max);

} // namespace uin