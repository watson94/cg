#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>
#include <cg/operations/search_maximums.h>

using cg::point_2f;
using cg::point_2;

struct search_maximums_viewer : cg::visualization::viewer_adapter
{
   search_maximums_viewer() :
       pts_(std::vector<point_2>( {point_2(0, 0), point_2(20, 20), point_2(30, -30) } ))
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (point_2 const & p : pts_)
         drawer.draw_point(p, 3);
      std::vector<point_2> ans;
      std::vector<point_2> tmp;
      for (point_2 const & p : pts_)
          tmp.push_back(point_2(p.x, p.y));
        cg::search_maximums(tmp.begin(), tmp.end(), std::back_inserter(ans));
      drawer.set_color(Qt::red);
      for (point_2 const & p : ans)
         drawer.draw_point(p, 3);

   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "algorithm: Diametr of Polygonr" << cg::visualization::endl;
      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "points: " << pts_.size() << cg::visualization::endl;

   }

   bool on_press(const point_2f & p)
   {
       pts_.push_back(cg::point_2(p.x, p.y) );

       return true;
   }

public:
   std::vector<point_2> pts_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   search_maximums_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Maximum of set of points");
}


