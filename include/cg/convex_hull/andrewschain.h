#pragma once

#include <boost/range/algorithm/sort.hpp>

#include <cg/operations/orientation.h>

namespace cg {
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


       BidIter endhull = st;

       ///up
       for (; p != en; ) {
           while ((endhull > st) && (orientation(*p, *(endhull - 1), *endhull)) != CG_RIGHT) {
                endhull--;
           }
           endhull++;
           std::iter_swap(endhull, p);
           if (p != en) p++; else break;
       }
       for (BidIter o = st; o <= endhull; o++) {
           std::cout << *o;
       }
       std::cout << std::endl;
       BidIter enduppart = endhull;
       endhull++;
       if (endhull == q) {
            return q;
       }
       std::sort(endhull, q);
       std::reverse(endhull, q);
       p = endhull;
       for (; p != en; ) {
           std::cout << *p;

           while ((endhull > enduppart) && (orientation(*p, *(endhull - 1), *endhull)) != CG_RIGHT) {
                endhull--;
           }
           endhull++;
           std::iter_swap(endhull, p);
           if (p != en)
               p++;
           else
                break;
       }
       while ((endhull - 1 != st) && (orientation(*(endhull - 1), *st, *endhull) !=  CG_LEFT)) {
            endhull--;
       }


       return ++endhull;
   }
}

