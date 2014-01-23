#include <QColor>
#include <QApplication>

#include <boost/optional.hpp>

#include <cg/visualization/viewer_adapter.h>
#include <cg/visualization/draw_util.h>

#include <cg/io/point.h>

#include <cg/primitives/point.h>
#include <cg/Douglas-Peucher/Douglas-Peucher.h>

using cg::point_2f;
using cg::point_2;

struct douglas_peucher_viewer : cg::visualization::viewer_adapter
{
   douglas_peucher_viewer() :
       pts_(std::vector<point_2>( {point_2(0, 0), point_2(20, 20), point_2(30, -30) } )),
       ch_size_(2)
   {}

   void draw(cg::visualization::drawer_type & drawer) const
   {
      drawer.set_color(Qt::white);
      for (point_2 const & p : pts_)
         drawer.draw_point(p);

      std::vector <point_2> res;
      cg::simplify(pts_.begin(), pts_.end(), eps, std::back_inserter(res), true);
      //ch_size_ = std::distance(res.begin(), res.end());
      drawer.set_color(Qt::green);
      for (int i = 0; i < res.size() - 1; i++) {
         {
            drawer.draw_point(res[i], 3);
            drawer.draw_line(res[i], res[i + 1]);
         }
      }
   }

   void print(cg::visualization::printer_type & p) const
   {
      p.corner_stream() << "algorithm: Douglas-Peucher" << cg::visualization::endl;
      p.corner_stream() << "press mouse rbutton to add point" << cg::visualization::endl
                        << "points: " << pts_.size() << cg::visualization::endl
                        << "press Up/Down Key to change eps" << cg::visualization::endl
                        << "Eps = " <<  eps ;

   }

   bool on_press(const point_2f & p)
   {
       pts_.push_back(p);
       return true;
   }

   bool on_key(int key)
   {
      switch (key)
      {
        case Qt::Key_Up : eps += 10; break;
        case Qt::Key_Down : eps -=10; break;
        default : return false;
      }
      return true;
   }

private:
   std::vector<point_2> pts_;
   size_t ch_size_;
   double eps = 10;
};

int main(int argc, char ** argv)
{
   QApplication app(argc, argv);
   douglas_peucher_viewer viewer;
   cg::visualization::run_viewer(&viewer, "Douglas-Peucher");
}
