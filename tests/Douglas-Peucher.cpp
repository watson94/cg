#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>
#include <iostream>
#include <cg/primitives/contour.h>
#include <misc/random_utils.h>

#include "random_utils.h"

#include <cg/io/point.h>
#include <cg/Douglas-Peucher/Douglas-Peucher.h>

using namespace util;

TEST(DouglasPeucher, sample)
{
    using cg::point_2;

    std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                     (point_2(2, 2))
                                                     (point_2(6, -3))
                                                     (point_2(9, -1))
                                                     (point_2(4, -7));
    std::vector<point_2> res;
    double eps = 7;

    std::cout << "Begin point" << std::endl;
    std::cout << *(pts.begin()) << std::endl;

    cg::simplify(pts.begin(), pts.end(), eps, std::back_inserter(res), true);

    for (int i = 0; i < res.size(); i++) {
        std::cout << res[i] << std::endl;
    }

    EXPECT_EQ(1, 2);

}

