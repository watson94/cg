#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>
#include <iostream>
#include <cg/primitives/contour.h>
#include <misc/random_utils.h>

#include "random_utils.h"

#include <cg/io/point.h>
#include <cg/operations/polygon_diameter.h>

using namespace util;

TEST(Diameter, sample)
{
    using cg::point_2;

    std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                     (point_2(2, 2))
                                                     (point_2(6, -3))
                                                     (point_2(9, -1))
                                                     (point_2(4, -7));

    auto ans = cg::polygon_diameter(pts.begin(), pts.end());
    std::cout << *(ans.first) << *(ans.second) << std::endl;
    EXPECT_TRUE((*(ans.first) == point_2(4, -7) && *(ans.second) == point_2(2, 2)) ||
                (*(ans.first) == point_2(2, 2) && *(ans.second) == point_2(4, -7)));

}

TEST(Diameter, sample1)
{
    using cg::point_2;

    std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                     (point_2(2, 2))
                                                     (point_2(6, -3))
                                                     (point_2(9, -1));

    auto ans = cg::polygon_diameter(pts.begin(), pts.end());
    std::cout << *(ans.first) << *(ans.second) << std::endl;
    EXPECT_TRUE((*(ans.first) == point_2(0, 0) && *(ans.second) == point_2(9, -1)) ||
                (*(ans.first) == point_2(9, -1) && *(ans.second) == point_2(0, 0)));

}

TEST(Diameter, onepoint)
{
    using cg::point_2;

    std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0));

    auto ans = cg::polygon_diameter(pts.begin(), pts.end());
    std::cout << *(ans.first) << *(ans.second) << std::endl;
    EXPECT_TRUE((*(ans.first) == point_2(0, 0) && *(ans.second) == point_2(0, 0)));
}


TEST(Diameter, twopoints)
{
    using cg::point_2;

    std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                     (point_2(3, 4));

    auto ans = cg::polygon_diameter(pts.begin(), pts.end());
    std::cout << *(ans.first) << *(ans.second) << std::endl;
    EXPECT_TRUE((*(ans.first) == point_2(0, 0) && *(ans.second) == point_2(3, 4)) ||
                (*(ans.first) == point_2(3, 4) && *(ans.second) == point_2(0, 0)));

}

TEST(Diameter, oneline)
{
    using cg::point_2;

    std::vector<point_2> pts = boost::assign::list_of(point_2(-3, -3))
                                                     (point_2(-1, -1))
                                                     (point_2(2, 2))
                                                     (point_2(5, 5));

    auto ans = cg::polygon_diameter(pts.begin(), pts.end());
    std::cout << *(ans.first) << *(ans.second) << std::endl;
    EXPECT_TRUE((*(ans.first) == point_2(-3, -3) && *(ans.second) == point_2(5, 5)) ||
                (*(ans.first) == point_2(5, 5) && *(ans.second) == point_2(-3, -3)));

}


TEST(Diameter, square)
{
    using cg::point_2;

    std::vector<point_2> pts = boost::assign::list_of(point_2(-3, -3))
                                                     (point_2(3, 3))
                                                     (point_2(3, -3))
                                                     (point_2(-3, 3));

    auto ans = cg::polygon_diameter(pts.begin(), pts.end());
    std::cout << *(ans.first) << *(ans.second) << std::endl;
    EXPECT_TRUE((*(ans.first) == point_2(-3, -3) && *(ans.second) == point_2(3, 3)) ||
                (*(ans.first) == point_2(3, 3) && *(ans.second) == point_2(-3, -3)) ||
                (*(ans.first) == point_2(-3, 3) && *(ans.second) == point_2(3, -3)) ||
                (*(ans.first) == point_2(3, -3) && *(ans.second) == point_2(-3, 3)));

}


