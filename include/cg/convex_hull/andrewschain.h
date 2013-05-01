#pragma once

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

namespace cg {
   template <class BidIter>
   BidIter make_chain(BidIter st, BidIter en) {
       BidIter endhull = st;
       BidIter p = st + 1;
       for (; p != en; ) {
           while ((endhull > st) && (orientation(*p, *(endhull - 1), *endhull)) != CG_RIGHT) {
                endhull--;
           }
           endhull++;
           std::iter_swap(endhull, p);
           if (p != en) p++; else break;
       }
       return endhull;
   }

   template <class BidIter>
   BidIter andrews_hull(BidIter p, BidIter q) {
       if (p == q) {
           return p;
       }
       std::sort(p, q);
       BidIter st = p++;

       if (p == q) {
           return p;
       }

       if ((p + 1) == q) {
           return q;
       }

       BidIter en = q;

       BidIter endhull = make_chain(st, en);
       endhull++;

       if (endhull == q) {
            return q;
       }
       std::sort(endhull, q);
       std::reverse(endhull, q);
       p = endhull;

       endhull = make_chain(endhull - 1, en);

       while ((endhull - 1 != st) && (orientation(*(endhull - 1), *st, *endhull) !=  CG_LEFT)) {
            endhull--;
       }

       return ++endhull;

   }
}

