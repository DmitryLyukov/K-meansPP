#include "kmeanspp.hpp"

int main(int argc, char* argv[]) {
    size_t N, dim;
    std::cin >> N >> dim;
    std::vector<std::vector<double> > points;
    read_points(std::cin, N, dim, points);
    
    size_t num_of_clusters = 1;
    if (argc > 1) {
        num_of_clusters = atol(argv[1]);
    }
    
    std::vector<std::set<size_t> > clusters;
        
    k_means(num_of_clusters, points, clusters);
    
    print_clusters(std::cout, points, clusters);
    return 0;
}
