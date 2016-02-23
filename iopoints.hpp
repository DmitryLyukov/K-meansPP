#ifndef IOPOINTS
#define IOPOINTS

#include <iostream>
#include <vector>
#include <set>

void read_points(std::istream &inp, const size_t N, const size_t dim,
        std::vector<std::vector<double> > &points);

void print_clusters(std::ostream &outp,
        const std::vector<std::vector<double> > &points,
        const std::vector<std::set<size_t> > &clusters);

#endif  // IOPOINTS
