#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../gui/gui_spec.hpp"

enum eDirection {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
