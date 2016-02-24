#ifndef IOPOINTS
#define IOPOINTS

#include <iostream>
#include <vector>
#include <set>
#include <sstream>

void read_points(std::istream &inp,
        std::vector<std::vector<double> > &points);

void print_clusters(std::ostream &outp,
        const std::vector<std::vector<double> > &points,
        const std::vector<std::set<size_t> > &clusters);

#endif  // IOPOINTS
