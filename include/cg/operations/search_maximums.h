#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/segment.h>
#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/visibility_graph.h>
#include "orientation.h"
#include <algorithm>

#include <map>
#include <cg/io/segment.h>

using namespace std;
namespace cg {
    template <class BidIter, class OutIter>
    void search_maximums(BidIter begin, BidIter end, OutIter out) {

        std::sort(begin, end, [] (point_2 const & a, point_2 const & b)
                     {
                        return ((a.y > b.y) || ((a.y == b.y) && (a.x < b.x)));
                     });
        for (BidIter i = begin; i != end; i++) {
            std::cout << *i << " ";
        }
        double maxX = 0;
        for (BidIter i = begin; i != end; i++) {
            if (i->x < maxX) {
                maxX = i->x;
            }
        }
        maxX-- ;

        for (BidIter i = begin; i != end; i++) {
            if (i->x >= maxX) {
                 *(out++) = *i;
                maxX = i->x;
            }
        }
    }
}
