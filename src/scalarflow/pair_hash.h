/* @file pair_hash.h
 * Basic utility for unordered hashmap
 */

#pragma once

#include <string>
#include <limits.h>

using std::string;

typedef std::pair<string, string> Vertex;

/**
* provide hash function for pair<string, string>,
* in this way, pair<string, string> or Vertex could be 
* used as key of unordered_map
*/
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};