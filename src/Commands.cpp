// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "Commands.h"


cmds Commands::getLongOption(std::string input) {
    if (input.compare("--help") == 0) { return cmds::help; }
    if (input.compare("--fetch") == 0) { return cmds::fetch; }
    if (input.compare("--install") == 0) { return cmds::install; }
    else { return cmds::invalid; }
}

cmds Commands::getShortOption(char input) {
    if (input == 'h') { return cmds::help; }
    if (input == 'F') { return cmds::fetch; }
    if (input == 'I') { return cmds::install; }
    else { return cmds::invalid; }
}

void Commands::getLongModifier(std::string input) {
    if (input.compare("--all") == 0) { all = true; }
    else { return; }
}

void Commands::getShortModifier(char input) {
    if (input == 'a') { all = true; }
    else { return; }
}