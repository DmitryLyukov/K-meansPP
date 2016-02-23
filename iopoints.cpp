#include "iopoints.hpp"


void read_points(std::istream &inp, const size_t N, const size_t dim,
        std::vector<std::vector<double> > &points) {

    points = std::vector<std::vector<double> >(N, std::vector<double>(dim));
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < dim; ++j) {
            inp >> points[i][j];
        }
    }
}


void print_clusters(std::ostream &outp,
        const std::vector<std::vector<double> > &points,
        const std::vector<std::set<size_t> > &clusters) {
    
    const size_t num_of_clusters = clusters.size();
    for (size_t i = 0; i < num_of_clusters; ++i) {
        for (size_t point: clusters[i]) {
            outp << i << ' ';
            for (double crd: points[point]) {
                outp << crd << ' ';
            }
            outp << std::endl;
        }
    }
}