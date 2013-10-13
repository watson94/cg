
#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>
#include <iostream>
#include <cg/primitives/contour.h>
#include <misc/random_utils.h>

#include "random_utils.h"

#include <cg/io/point.h>
#include <cg/io/segment.h>
#include <cg/operations/visibility_graph.h>

using namespace util;

TEST(VISIBILITY, sample)
{
    using cg::point_2;
    cg::point_2 start(0, 0);
    cg::point_2 finish(10, 0);
    std::vector<point_2> pts = boost::assign::list_of(point_2(1, 3))
                                                     (point_2(1, -3))
                                                     (point_2(5, -3))
                                                     (point_2(5, 4));

    cg::contour_2 c1(pts);
    std::vector<cg::segment_2> ans;

    std::vector<cg::contour_2> obstacles;
    obstacles.push_back(c1);

    cg::get_visibility(start, finish, obstacles, std::back_inserter(ans));
    for (cg::segment_2 & seg : ans) {
        std::cout << seg << std::endl;
    }

    EXPECT_TRUE(1 == 1);

}


TEST(VISIBILITY, sample2)
{
    using cg::point_2;
    std::cout << "/////////////////TEST2" << std::endl;
    cg::point_2 start(0, 0);
    cg::point_2 finish(10, 0);
    std::vector<point_2> pts1 = boost::assign::list_of(point_2(1, 0))
                                                     (point_2(2, -1))
                                                     (point_2(3, 0))
                                                     (point_2(2, 1));

    std::vector<point_2> pts2 = boost::assign::list_of(point_2(4, 0))
                                                     (point_2(5, -100))
                                                     (point_2(5, 0));                                                     ;

    cg::contour_2 c1(pts1);
    cg::contour_2 c2(pts2);
    std::vector<cg::segment_2> ans;

    std::vector<cg::contour_2> obstacles;
    obstacles.push_back(c1);
    obstacles.push_back(c2);

    cg::get_visibility(start, finish, obstacles, std::back_inserter(ans));
    for (cg::segment_2 & seg : ans) {
        std::cout << seg << std::endl;
    }

    EXPECT_TRUE(1 == 1);

}


TEST(VISIBILITY, bag1)
{
    using cg::point_2;
    std::cout << "/////////////////TEST2" << std::endl;
    cg::point_2 start(0, 0);
    cg::point_2 finish(100, 0);
    std::vector<point_2> pts1 = boost::assign::list_of(point_2(10, 5))
                                                     (point_2(30, -30))
                                                     (point_2(60, 5))
                                                     (point_2(30, 30));
                                                    ;

    cg::contour_2 c1(pts1);
    std::vector<cg::segment_2> ans;

    std::vector<cg::contour_2> obstacles;
    obstacles.push_back(c1);

    cg::get_visibility(start, finish, obstacles, std::back_inserter(ans));
    for (cg::segment_2 & seg : ans) {
        std::cout << seg << std::endl;
    }

    EXPECT_TRUE(1 == 1);

}
