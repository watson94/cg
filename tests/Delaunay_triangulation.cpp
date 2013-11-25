

#include <gtest/gtest.h>

#include <boost/assign/list_of.hpp>
#include <iostream>
#include <cg/primitives/contour.h>
#include <misc/random_utils.h>

#include "random_utils.h"

#include <cg/io/point.h>
#include <cg/io/segment.h>
#include <cg/triangulation/Delaunay_triangulation.h>
#include <cg/io/triangle.h>

using namespace util;

using cg::triangle_2;
using cg::point_2;

TEST(Triangulation, sample)
{
    using cg::point_2;
    std::vector<point_2> pts = boost::assign::list_of(point_2(63, -72))
                                                     (point_2(-151, 85))
                                                     (point_2(-105, -16))
                                                     (point_2(-10, -69));

    cg::cell<double> cell;
    for (int i = 0; i < pts.size(); i++) {
        auto ans = cell.get_triangulation();

        for (const cg::triangle_2 & tr : ans) {
            std::cout << tr[0] << tr[1] << tr[2] << std::endl;
        }
        cell.add_point(pts[i]);
    }
    std::cout << "Ans" << std::endl;
    auto ans = cell.get_triangulation();

    for (const cg::triangle_2 & tr : ans) {
        std::cout << tr[0] << tr[1] << tr[2] << std::endl;
    }
    EXPECT_TRUE(true == true);
}




bool is_delaunay_triang(const std::vector<triangle_2> & faces, const std::vector<point_2> & pts)
{
   for(triangle_2 t : faces)
      for(point_2 s : pts)
         if(t[0] != s && t[1] != s && t[2] != s && cg::check_inside_circumcircle(t[0], t[1], t[2], s))
         {
            std::cout << t << " contains " << s << std::endl;
            return false;
         }
   return true;
}


TEST(delaunay, uniform)
{
   for(size_t i = 0; i < 10; ++i)
   {
      std::vector<point_2> pts = uniform_points(100);
      cg::cell<double> cell;
      for(auto pt : pts)
      {
         cell.add_point(pt);
      }
      std::vector<triangle_2> faces = cell.get_triangulation();
      EXPECT_TRUE(is_delaunay_triang(faces, pts));
   }
}
