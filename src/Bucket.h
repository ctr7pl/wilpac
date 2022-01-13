// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BUCKET_H
#define BUCKET_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Colors.h"

class Bucket {
public:
    Bucket();

    // gets the buckets the user has in their bucketlist file
    static void getBuckets();

    // pulls the latest bucket repositories
    static void fetchBuckets();

    ~Bucket();
};

#endif