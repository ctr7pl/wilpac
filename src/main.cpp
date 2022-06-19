// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <unistd.h>
#include <vector>

#include "Buckets.h"
#include "Commands.h"
#include "PackageMan.h"
#include "Runtime.h"

// help menu / usage function
void usage() {
    std::cout << REG GRE <<
    "()Usage: `wilpac <OPTIONS> <modifiers> <args>\n" <<
    "\t()OPTIONS:\n" <<
    "\t-I, --install <package>; install package\n" <<
    "\t-F, --fetch; fetch buckets\n" <<
    "\t-h, --help; display help and exit\n";
}

int main(int argc, char *argv[]) {
    // check to see if user is admin, if not operations won't work so exit
    if (geteuid() != 0) {
        std::cerr << BLD RED "()Please run as root" RS << std::endl;
        return 1;
    }

    // check to see if args have been provided, if not exit with error
    if (argc <= 1) {
        std::cerr << BLD RED "()Not enough arguments provided (-h or --help for help)" RS << std::endl;
        return 2;
    }

    // runtime functions/tasks can be completed
    Runtime();

    // create Commands object
    Commands commands;

    // create list of operations to be performed and new arglist (args without '-' or '--')
    std::vector<cmds> operations;
    std::vector<std::string> args;

    // create operations list
    for (int i = 0; i < argc; i ++) {
        // if the option starts with '--' then parse it accordingly, if it's just '-' parse accordingly,
        // otherwise add it as a program argument (helps with organization to have separate args variable)
        if (argv[i][0] == '-' && argv[i][1] == '-') {
            operations.push_back(commands.getLongOption(argv[i]));
            commands.getLongModifier(argv[i]);
        } if (argv[i][0] == '-') {
            for (int j = 1; j < std::string(argv[i]).length(); j++) {
                operations.push_back(commands.getShortOption(argv[i][j]));
                commands.getShortModifier(argv[i][j]);
            }
        } else { args.push_back(argv[i]); }
    }

    // execute operations
    for (int i = 0; i < operations.size(); i++) {
        if (operations[i] == cmds::help) { usage(); }
        if (operations[i] == cmds::fetch) {
            fetchBuckets();
            getBuckets();
        }
        if (operations[i] == cmds::install) {
            if (args.size() <= 1) { std::cerr << BLD RED "()Not enough arguments provided for install (-h or --help for help)" RS "\n"; }
            else if (pkgExists(std::string(args[1] + ".json")).compare("0") == 0) {
                std::cerr << BLD RED "()Package not found, is the package's bucket installed?" RS << "\n";
                return 3;
            } else {
                std::cout << REG GRE "()Package located, running install script..." RS "\n";
                installPkg(std::string(args[1] + ".json"));
            }
        }
    }

    return 0;
}