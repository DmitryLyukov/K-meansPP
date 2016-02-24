#include "iopoints.hpp"


void read_points(std::istream &inp,
        std::vector<std::vector<double> > &points) {

    while (!inp.eof()) {
        std::string str_point;
        std::getline(inp, str_point);
        
        for (auto it = str_point.begin(); it != str_point.end(); ++it) {
            if (*it == ',') {
                *it = ' ';
            }
        }
        
        std::istringstream iss(str_point);
        std::vector<double> point;
        
        while (!iss.eof()) {
            double crd;
            iss >> crd;
            point.push_back(crd);
        }
        
        points.push_back(point);
    }
}


void print_clusters(std::ostream &outp,
        const std::vector<std::vector<double> > &points,
        const std::vector<std::set<size_t> > &clusters) {
    
    const size_t num_of_clusters = clusters.size();
    for (size_t i = 0; i < num_of_clusters; ++i) {
        for (size_t point: clusters[i]) {
            outp << i;
            for (double crd: points[point]) {
                outp << ' ' << crd;
            }
            outp << std::endl;
        }
    }
}
