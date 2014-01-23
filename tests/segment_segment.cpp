#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>

#include <cg/primitives/contour.h>
#include <cg/primitives/segment.h>
#include <cg/operations/orientation.h>
#include <cg/convex_hull/graham.h>
#include <cg/operations/intersection/segment_segment.h>
#include <cg/operations/intersection/segment_segment.h>
#include <misc/random_utils.h>

#include "random_utils.h"

using namespace util;

TEST(orientation, uniform_line)
{

   uniform_random_real<double, std::mt19937> distr(-(1LL << 53), (1LL << 53));
   auto it = cg::intersection(cg::segment_2(cg::point_2(1.0, 1.0), cg::point_2(2.0, 3.0)), cg::segment_2(cg::point_2(2.0, 2.0), cg::point_2(3.0, 3.0)));

}


