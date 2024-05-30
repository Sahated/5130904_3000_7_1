#include "Polygon.h"
#include <iterator>
#include <algorithm>
#include "Delimetr.h"

double getTriArea(double curr, const bajkin::Point& p1, const bajkin::Point& p2, const bajkin::Point& p3)
{
  curr += 0.5 * std::abs((p3.x - p1.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p3.y - p1.y));
  return curr;
}

double bajkin::Polygon::getAreaImpl(double curr, c_it_t it, c_it_t it2) const
{
  if (it2 == points.cend())
  {
    return curr;
  }
  curr = getTriArea(curr, *it++, *it2++, points[0]);
  return getAreaImpl(curr, it, it2);
}

double bajkin::Polygon::getArea() const
{
  return getAreaImpl(0.0, points.cbegin(), ++points.cbegin());
}

std::istream& bajkin::operator>>(std::istream& in, Polygon& pol)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t countAngles = 0;
  in >> countAngles;
  const size_t minAngles = 3;
  if (countAngles < minAngles)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  temp.reserve(countAngles);
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ in }, countAngles, std::back_inserter(temp));
  if (temp.size() == countAngles)
  {
    pol.points = temp;
  }
  return in;
}

std::istream& bajkin::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point temp{ 0,0 };
  using dc = Delimiter;
  in >> dc{ '(' } >> temp.x >> dc{ ';' } >> temp.y >> dc{ ')' };
  if (in)
  {
    p = temp;
  }
  return in;
}

bool bajkin::Point::operator<(const Point& rhs) const
{
  return (x < rhs.x) && (y < rhs.y);
}
