#pragma once

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

namespace cg
{
    template <class BidIter>
    BidIter recursive_quick (BidIter p, BidIter q) {
        BidIter st = std::min_element(p, q) ;
        BidIter en = std::max_element(p, q) ;
        std::iter_swap(st, p++);
        std::iter_swap(en, p);
        en =p++;

        BidIter max = std::max_element(st, en, [&st, &en] (point_2 const & a, point_2 const & b) {
                                       if (orientation(b, a, a + (*en - *st)) == CG_COLLINEAR) {
                                           return a < b;
                                       }
                                       return (orientation(b, a, a + (*en - *st)) == CG_LEFT);
        }
        );
        std::iter_swap(p, max);
        max = p;
        BidIter part = std::partition(st, en, [&max, &en] (point_2 const &a) {
                return orientation(*en, *max, a) == CG_RIGHT;
        }
        );
        std::rotate(max, max + 1, part);

        return st;
    }
    template <class BidIter>
    BidIter quick_hull(BidIter p, BidIter q) {
        return q;
        if (p == q) {
            return p;
        }
        BidIter st = p;
        BidIter en = q;
        std::iter_swap(std::min_element(p, q), p++);
        std::iter_swap(std::max_element(p, q), p++);
        BidIter part = std::partition(st, en, [&p] (point_2 const & a) {
                       return orientation(a, *p, *(p + 1)) == CG_LEFT;
        });
        std::rotate(st, st + 1, part);
        recursive_quick(st, part);
        recursive_quick(part, en);
    }
}
