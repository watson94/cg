#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>
#include <cg/operations/polygon_diameter.h>

using cg::point_2f;
using cg::point_2;

struct douglas_peucher_viewer : cg::visualization::viewer_adapter
{
   douglas_peucher_viewer() :
       pts_(std::vector<point_2>( {point_2(0, 0), point_2(20, 20), point_2(30, -30) } ))
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (point_2 const & p : pts_)
         drawer.draw_point(p);
      std::vector<point_2> tmp(pts_.begin(), pts_.end());
      auto res = cg::polygon_diameter(tmp.begin(), tmp.end());
      drawer.set_color(Qt::green);
      std::cout <<"In drawer:"<< *(res.first) << *(res.second) << std::endl;
      drawer.draw_line(*(res.first), *(res.second));

   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "algorithm: Diametr of Polygonr" << cg::visualization::endl;
      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "points: " << pts_.size() << cg::visualization::endl;

   }

   bool on_press(const point_2f & p)
   {
       pts_.push_back(p);
       return true;
   }

private:
   std::vector<point_2> pts_;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   douglas_peucher_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Diameter of set of points");
}

