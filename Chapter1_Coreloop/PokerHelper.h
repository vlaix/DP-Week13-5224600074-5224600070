#pragma once
#include <map>
#include <algorithm>
#include <vector>
#include "Hand.h"

std::map<int, int> getRankCount(const Hand& hand);
bool isFlush(const Hand& hand);
bool isStraight(const Hand& hand);
bool DuplicateChecker(const Hand& hand, int Many);