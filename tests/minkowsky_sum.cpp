
#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>
#include <iostream>
#include <cg/primitives/contour.h>
#include <misc/random_utils.h>

#include "random_utils.h"

#include <cg/io/point.h>
#include <cg/io/segment.h>
#include <cg/operations/minkowsky_sum.h>

using namespace util;

TEST(MINKOWSKY, sample)
{
    using cg::point_2;
    std::vector<point_2> pts1 = boost::assign::list_of(point_2(-10, 0))
                                                     (point_2(10, 0));

    std::vector<point_2> pts2 = boost::assign::list_of(point_2(0, 10))
                                                     (point_2(0, -10));
    std::vector<point_2> pts3 = boost::assign::list_of(point_2(-10, -10))
                                                     (point_2(10, -10))
                                                     (point_2(10, 10))
                                                     (point_2(-10, 10));

    cg::contour_2 c1(pts1);
    cg::contour_2 c2(pts2);
    cg::contour_2 c3(pts3);


    cg::contour_2 ans = cg::minkowsky_sum(c1, c2);
    std::cout << "Ans" << std::endl;
    for (const cg::point_2 & p : ans) {
        std::cout << p << std::endl;
    }

    EXPECT_TRUE(c3 == ans);

}


TEST(MINKOWSKY, sample2)
{
    using cg::point_2;
    std::vector<point_2> pts1 = boost::assign::list_of(point_2(-10, 0))
                                                     (point_2(10, 0))
                                                     (point_2(0, 10) );

    std::vector<point_2> pts2 = boost::assign::list_of(point_2(0, 10))
                                                     (point_2(0, -10));
    std::vector<point_2> pts3 = boost::assign::list_of(point_2(-10, -10))
                                                      (point_2(10, -10))
                                                      (point_2(10, 10))
                                                      (point_2(0, 20))
                                                      (point_2(-10, 10));

    cg::contour_2 c1(pts1);
    cg::contour_2 c2(pts2);
    cg::contour_2 c3(pts3);


    cg::contour_2 ans = cg::minkowsky_sum(c1, c2);
    std::cout << "Ans" << std::endl;
    for (const cg::point_2 & p : ans) {
        std::cout << p << std::endl;
    }

    EXPECT_TRUE(c3 == ans);

}
