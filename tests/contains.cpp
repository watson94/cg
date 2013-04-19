#include <gtest/gtest.h>

#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/contains/contour_point.h>

TEST(contains, triangle_point)
{
   using cg::point_2;

   cg::triangle_2 t(point_2(0, 0), point_2(1, 1), point_2(2, 0));

   for (size_t l = 0; l != 3; ++l)
      EXPECT_TRUE(cg::contains(t, t[l]));

   EXPECT_TRUE(cg::contains(t, point_2(1, 0.5)));

   EXPECT_TRUE(cg::contains(t, point_2(1, 0)));
   EXPECT_TRUE(cg::contains(t, point_2(0.5, 0.5)));
   EXPECT_TRUE(cg::contains(t, point_2(1.5, 0.5)));

   EXPECT_FALSE(cg::contains(t, point_2(0, 1)));
   EXPECT_FALSE(cg::contains(t, point_2(2, 1)));
   EXPECT_FALSE(cg::contains(t, point_2(1, -1)));
}

TEST(contains, segment_point)
{
   using cg::point_2;

   cg::segment_2 s(point_2(0, 0), point_2(2, 2));
   for (size_t l = 0; l != 2; ++l)
      EXPECT_TRUE(cg::contains(s, s[l]));

   EXPECT_TRUE(cg::contains(s, point_2(1, 1)));

   EXPECT_FALSE(cg::contains(s, point_2(-1, -1)));
   EXPECT_FALSE(cg::contains(s, point_2(4, 4)));

   EXPECT_FALSE(cg::contains(s, point_2(1, 0)));
   EXPECT_FALSE(cg::contains(s, point_2(0, 1)));
}

TEST(contains, convex_contour_point)
{
    using cg::point_2;
    using cg::contour_2;
    std::vector<point_2 > vec;
    vec.push_back(point_2(0, 0));
    vec.push_back(point_2(2, 1));
    vec.push_back(point_2(3, 2));
    vec.push_back(point_2(1, 5));
    vec.push_back(point_2(-1, 5));
    vec.push_back(point_2(-2, 3));
    contour_2 pol(vec);
    EXPECT_TRUE(cg::convex_contains(pol, point_2(1, 1)));
    EXPECT_TRUE(cg::convex_contains(pol, point_2(2, 1)));
    EXPECT_FALSE(cg::convex_contains(pol, point_2(5, 1)));
    EXPECT_TRUE(cg::convex_contains(pol, point_2(1, 0.5)));
    EXPECT_FALSE(cg::convex_contains(pol, point_2(3, 1.5)));
    EXPECT_TRUE(cg::convex_contains(pol, point_2(-1, 1.5)));
    EXPECT_FALSE(cg::convex_contains(pol, point_2(-3, 4.5)));
    EXPECT_TRUE(cg::convex_contains(pol, point_2(-2, 3)));
    EXPECT_FALSE(cg::convex_contains(pol, point_2(2, 10)));
    EXPECT_TRUE(cg::convex_contains(pol, point_2(0.5, 2.5)));
}
