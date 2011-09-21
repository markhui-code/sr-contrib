
#include <boost/smart_ptr.hpp>

#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>

#include <gtest/gtest.h>
#include <ros/ros.h>

template <class T>
class A
{
public:
  A(T p)
    : a(p)
  {
    std::cout << " new A: " << p<<std::endl;
  };

  A<T>(const A<T>& o)
    : a(o.a)
  {
    std::cout << " copying A: " << a<<std::endl;
  }

  ~A() {};

  T a;
};

template <class T>
struct greater
{
  bool operator() (const A<T>& x, const A<T>& y) const
  {
    return x.a > y.a;
  }
};

TEST(GeneticAlgorithm, sort)
{
  boost::shared_ptr<std::vector<A<double> > > test = boost::shared_ptr<std::vector<A<double> > >( new std::vector<A<double> >() );

  boost::mt19937 gen;
  boost::uniform_real<> dist(1.0, 6.0);

  std::cout << " testing uniform int: " << dist(gen) << " " << dist(gen) << " " << dist(gen) << " " << dist(gen) << " " << dist(gen) << std::endl;

  boost::mt19937 gen2;
  boost::uniform_real<> dist2(1.0, 6.0);

  std::cout << " testing uniform int2: " << dist2(gen2) << " " << dist2(gen2) << " " << dist2(gen2) << " " << dist2(gen2) << " " << dist2(gen2) << std::endl;


  boost::mt19937 drand;
  for(unsigned int i=0; i < 10; ++i)
    test->push_back(drand());

  std::cout << "before sorting: " << std::endl;
  for(unsigned int i=0; i < test->size(); ++i)
    std::cout << test->at(i).a << " ";
  std::cout << std::endl;

  std::sort( test->begin(), test->end(), greater<double>() );
  std::cout << "after sorting: " << std::endl;
  for(unsigned int i=0; i < test->size(); ++i)
    std::cout << test->at(i).a << " ";
  std::cout << std::endl;

}
/////////////////////
//     MAIN       //
///////////////////

int main(int argc, char **argv)
{
  ros::init(argc, argv, "test_sort");

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/* For the emacs weenies in the crowd.
   Local Variables:
   c-basic-offset: 2
   End:
*/