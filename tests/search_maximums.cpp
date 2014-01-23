#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>

#include <cg/primitives/contour.h>
#include <cg/primitives/segment.h>
#include <cg/operations/orientation.h>
#include <cg/convex_hull/graham.h>
#include <cg/operations/search_maximums.h>

#include <misc/random_utils.h>

#include "random_utils.h"

using namespace util;




TEST(search_maximums, simple1)
{
    using cg::point_2;
    std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                     (point_2(1, 0))
                                                     (point_2(0, 1))
                                                     (point_2(2, 0))
                                                     (point_2(0, 2))
                                                     (point_2(3, 0))
                                                     (point_2(2, 2));

    std::vector<point_2> ans;
    cg::search_maximums(pts.begin(), pts.end(), std::back_inserter(ans));
    EXPECT_TRUE(ans.size() == 4 && ans[0] == cg::point_2(0, 2) && ans[1] == cg::point_2(2, 2) && ans[2] == cg::point_2(2, 0) && ans[3] == cg::point_2(3, 0) );

}

TEST(search_maximums, one_vertical_line)
{
    using cg::point_2;
    std::vector<point_2> pts = boost::assign::list_of(point_2(0, 0))
                                                     (point_2(0, 1))
                                                     (point_2(0, 2))
                                                     (point_2(0, 3))
                                                     ;

    std::vector<point_2> ans;
    cg::search_maximums(pts.begin(), pts.end(), std::back_inserter(ans));
    EXPECT_TRUE(ans.size() == 4 && ans[0] == cg::point_2(0, 3) && ans[1] == cg::point_2(0, 2) && ans[2] == cg::point_2(0, 1) && ans[3] == cg::point_2(0, 0));
}

