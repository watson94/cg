#pragma once

#include <vector>

#include "point.h"
#include "cg/common/range.h"

namespace cg
{
   template <class Scalar>
   struct contour_2t;

   typedef contour_2t<float> contour_2f;
   typedef contour_2t<double> contour_2;
   typedef contour_2t<int>   contour_2i;

   template <class Scalar>
   struct contour_2t
   {
      contour_2t()
      {}
      contour_2t(std::vector<point_2t<Scalar> > const& pts) : pts_(pts)
      {}

      typedef typename std::vector<point_2t<Scalar> >::const_iterator const_iterator;
      typedef typename common::range_circulator<contour_2t<Scalar> > circulator_t;

      const_iterator begin() const
      {
         return pts_.begin();
      }
      const_iterator end() const
      {
         return pts_.end();
      }

      circulator_t circulator() const
      {
         return common::range_circulator<contour_2t<Scalar> >(*this);
      }

      circulator_t circulator(const_iterator itr) const
      {
         return common::range_circulator<contour_2t<Scalar> >(*this, itr);
      }

      size_t vertices_num() const
      {
         return pts_.size();
      }

      size_t size() const
      {
         return vertices_num();
      }

      void add_point(point_2t<Scalar> const& point)
      {
         pts_.push_back(point);
      }

      void delete_last_point() {
        pts_.erase(pts_.end() - 1);
      }

      point_2t<Scalar> const& operator [] (size_t idx) const
      {
         return pts_[idx];
      }

      point_2t<Scalar> & operator [] (size_t idx)
      {
         return pts_[idx];
      }

   private:
      friend struct contour_builder_type;

      std::vector<point_2t<Scalar> > pts_;
   };

   template <class Scalar>
   bool operator == (contour_2t<Scalar> const & a, contour_2t<Scalar> const & b)
   {
       for (auto pos = a.begin(); pos != a.end(); pos++) {
           auto it1 = pos;
           bool is_ok = true;
           for (auto it2 = b.begin(); it2 != b.end(); it2++) {
               if ((*it2) != (*it1)) {
                    is_ok = false;
               }
               it1 = (((it1 + 1) == a.end()) ? a.begin() : (it1 + 1));
           }
           if (is_ok) {
               return true;
           }
       }
       return false;
   }

   typedef common::range_circulator<contour_2f> contour_circulator;
}
