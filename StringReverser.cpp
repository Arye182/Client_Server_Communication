//
// Created by miri on 20.1.2020.
//

#include "StringReverser.h"
#include <algorithm>

using namespace std;
 string StringReverser::solve(string str) {
   reverse(str.begin(), str.end());
   return str;
}
