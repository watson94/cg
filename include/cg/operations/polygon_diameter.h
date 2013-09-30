#pragma once

#include <algorithm>
#include <iostream>

#include<cg/io/point.h>


#include <cg/operations/orientation.h>
#include <cg/operations/distance.h>
//#include <cg/convex_hull/quickhull.h>
#include <cg/primitives/segment.h>
#include <cg/convex_hull/andrew.h>

namespace cg {

    double max_distance2_point_to_segment(point_2 const & p, segment_2 const & seg) {
        return std::max(distance2(p, seg[0]), distance2(p, seg[1]));
    }

    template <class BidIter>
    std::pair<BidIter, BidIter> polygon_diameter(BidIter  begin, BidIter end) {
        //std::cout << *begin << std::endl << *end << std::endl;
        //typedef typename BidIter::value_type::value_type Scalar;
        //std::vector<point_2> pts(begin, end);
        std::cout << "All points:" << std::endl;
        for (BidIter i = begin; i != end; i++) {
            std::cout << *i << " ";
        }
        std::cout << std::endl;


        end = andrew_hull(begin , end);

        std::cout << "Convex hull:" << std::endl;
        for (BidIter i = begin; i != end; i++) {
            std::cout << *i << " ";
        }
        std::cout << std::endl;

        if ( std::distance(begin, end) <= 1) {
            std::pair<BidIter, BidIter> ans(begin, begin);
            return ans;
        }
        if ( std::distance(begin, end) == 2) {
          std::pair<BidIter, BidIter> ans(begin, end - 1);
          return ans;
        }

        segment_2 seg(*begin, *(begin + 1));

        BidIter t = std::max_element(begin + 2, end, [&seg](point_2 const & p, point_2 const & q) {
            return exactly_closer_to_segment(p, q, seg);
        });

        std::cout << "t: " << *t << std::endl;

        std::pair<BidIter, BidIter> ans(begin, t);
        //double max_dist = -1;

        for (BidIter i = begin + 1; i != end; i++) {
            //std::cout << "Max dist:"  << max_dist << std::endl;
            std::cout << "Answer"  << *(ans.first) << *(ans.second) << std::endl;
            BidIter to = (i + 1 == end) ? begin : i + 1;

            seg = segment_2(*i, *(to));
            while (exactly_closer_to_segment(*t, ((t + 1) == end) ? *(begin) : *(t + 1), seg)) {
                std::cout << "Distance to seg"  << max_distance2_point_to_segment(*t, seg) << std::endl;
                t++;
                if (t == end) {
                    t = begin;
                }
            }
            std::cout << "Distance to itog seg"  << max_distance2_point_to_segment(*t, seg) << std::endl;

            if (exactly_smaller_distance(*(ans.first), *(ans.second), *t, seg[0])) {
                ans.first = t;
                ans.second = i;
            }
            if (exactly_smaller_distance(*(ans.first), *(ans.second), *t, seg[1])) {
                ans.first = t;
                ans.second = to;
            }
        }
        std::cout << "Exit answer"  << *(ans.first) << *(ans.second) << std::endl;
        return ans;
    }





    template <class BidIter>
    std::pair<BidIter, BidIter> polygon_diameter2(BidIter begin, BidIter end) {
        std::cout << *begin << std::endl << *end << std::endl;
        if ( std::distance(begin, end) <= 1) {
            std::pair<BidIter, BidIter> ans(begin, begin);
            return ans;
        }
        if ( std::distance(begin, end) == 2) {
            std::pair<BidIter, BidIter> ans(begin, end - 1);
            return ans;
        }
        std::pair<BidIter, BidIter> ans;
        double max = 0;
        for (BidIter i = begin; i != end; i++) {
            for (BidIter j = i + 1; j != end; j++) {
                if (distance(*i, *j) > max) {
                    ans.first = i;
                    ans.second = j;
                    max = distance(*i, *j);
                }
                std::cout << distance(*i, *j) << std::endl;
            }
        }
        return ans;
    }
}



