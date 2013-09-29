#pragma once

#include <algorithm>
#include <iostream>

#include <cg/operations/orientation.h>
#include <cg/operations/distance.h>


namespace cg {
    template <class BidIter, class OutIter>
    OutIter simplify(BidIter start, BidIter finish, double eps, OutIter out, bool is_start) {

        if ( std::distance(start, finish) <= 2) {
            *out++ = *start;
            return out;
        }
        BidIter first = start;
        BidIter last = finish - 1;
        point_2 p = *(first);
        point_2 q = *(last);
//        std::cout << "/////" << std::endl;
//        std::cout << p << std::endl << q << std::endl;

        BidIter ind = std::max_element(start + 1, last, [&p, &q] (point_2 const & a, point_2 const & b)
            {
                return (distance(p, q, a) < distance(p, q, b));
            }
        );

        point_2 t = *(ind);
        if (distance(p, q , t) < eps) {
//            std::cout << "Ok " << t << " " << distance(p, q, t) << std::endl;
            *out++ = *first;
        } else {
//            std::cout << "Splitting " << t << " " << distance(p, q, t) << std::endl;
            out = simplify(start, ind + 1, eps, out, false);
            out = simplify(ind, finish, eps, out, false);
        }
        if (is_start) {
            *out++=*last;
        }
        return out;
    }
}



