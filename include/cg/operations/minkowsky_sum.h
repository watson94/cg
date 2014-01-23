#pragma once

#include <cg/primitives/contour.h>
#include <cg/primitives/segment.h>
#include <cg/operations/has_intersection/segment_segment.h>
#include <cg/operations/orientation.h>
#include "orientation.h"

namespace cg
{

   template <class Scalar>
   cg::contour_2t<Scalar> minkowsky_sum(cg::contour_2t<Scalar> const & c1, cg::contour_2t<Scalar> const & c2) {
       std::cout << "sizes:" << c1.size() << " " << c2.size() << std::endl;
       std::cout << "C1" <<std::endl;
       for (auto p : c1) {
            std::cout << p << std::endl;
       }
       std::cout << "C2" <<std::endl;
       for (auto p : c2) {
            std::cout << p << std::endl;
       }
       std::cout << "Im recounting" << std::endl;
       cg::contour_2t<Scalar> ans;
       auto it1 = std::min_element(c1.begin(), c1.end());
       auto it1_n = (((it1 + 1) != c1.end()) ? (it1) + 1 : c1.begin());
       auto it2 = std::min_element(c2.begin(), c2.end());
       auto it2_n = (((it2 + 1) != c2.end()) ? (it2) + 1 : c2.begin());
       int count =  0;
       while (count < c1.size() + c2.size()) {
           std::cout << it2->x << " " << it2->y << std::endl;
           if ((ans.size() > 1) && (cg::orientation(ans[ans.size() - 2], ans[ans.size() - 1], *(it1) + vector_2t<Scalar>(it2->x, it2->y)) == CG_COLLINEAR))  {
               ans[ans.size() - 1] = *(it1) + vector_2t<Scalar>(it2->x, it2->y);
           } else {
                ans.add_point(*(it1) + vector_2t<Scalar>(it2->x, it2->y));
           }
           count++;
           vector_2t<Scalar> v1 = *(it1_n) - *(it1);
           vector_2t<Scalar> v2 = *(it2_n) - *(it2);
           point_2t<Scalar> p0(0, 0);
           point_2t<Scalar> p1 = p0 + v1;
           point_2t<Scalar> p2 = p0 + v2;
           if (cg::orientation(p0, p1, p2) == CG_LEFT) {
               it1 = it1_n;
               it1_n = (((it1_n + 1) != c1.end()) ? (it1_n) + 1 : c1.begin());
           } else {
               it2 = it2_n;
               it2_n = (((it2_n + 1) != c2.end()) ? (it2_n) + 1 : c2.begin());
           }
       }

       if (ans.size() > 2) {
           if (cg::orientation(ans[ans.size() - 2],  ans[ans.size() - 1], ans[0]) == CG_COLLINEAR) {
                ans.delete_last_point();
           }
       }

       return ans;
   }

}

