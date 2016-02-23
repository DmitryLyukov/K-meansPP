#include "kmeanspp.hpp"


double my_sqr_distance(const std::vector<double> &A,
        const std::vector<double> &B) {

    const size_t dim = A.size();
    double sum_sqr = 0;
    for (size_t i = 0; i < dim; ++i) {
        sum_sqr += pow(A[i] - B[i], 2);
    }
    return sum_sqr;
}


double my_distance(const std::vector<double> &A,
        const std::vector<double> &B) {

    return sqrt(my_sqr_distance(A, B));
}


void center_of_mass(const std::vector<std::vector<double> > &points,
        const std::set<size_t> &cluster, std::vector<double> &center) {
            
    const size_t N = cluster.size();
    if (N == 0) {
        return;
    }
    const size_t dim = points[0].size();
    center = std::vector<double>(dim);
    
    for (size_t i = 0; i < dim; ++i) {
        double sum = 0.0;
        for (size_t point: cluster) {
            sum += points[point][i];
        }
        center[i] = sum / N;
    }
}


void k_means_pp(const size_t num_of_clusters,
        const std::vector<std::vector<double> > &points,
        std::vector<std::vector<double> > &centers) {
    
    const size_t N = points.size();
    if ((N == 0) || (num_of_clusters == 0) || (num_of_clusters > N)) {
        return;
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    
    centers.push_back(points.at(generator() % num_of_clusters));
    
    std::vector<double> sqr_dist_from_near_center;
    for (size_t pnt = 0; pnt < N; ++pnt) {
        double sqr_dist = my_sqr_distance(points.at(pnt), centers.back());
        sqr_dist_from_near_center.push_back(sqr_dist);
    }
        
    for (size_t i = 1; i < num_of_clusters; ++i) {
        
        double sum_sqr_dist = 0.0;
        
        for (size_t pnt = 0; pnt < N; ++pnt) {
            double sqr_dist = my_sqr_distance(points[pnt], centers.back());
            double min_dist = std::min(sqr_dist_from_near_center.at(pnt), sqr_dist);
            sqr_dist_from_near_center.at(pnt) = min_dist;
            sum_sqr_dist += min_dist;
            }
        
        const double rnd = static_cast<double>(generator()) / generator.max();
        const double rnd_sum = sum_sqr_dist * rnd;
        
        sum_sqr_dist = 0.0;
        size_t point = -1;
        while (sum_sqr_dist < rnd_sum) {
            sum_sqr_dist += sqr_dist_from_near_center.at(++point);
        }
        
        centers.push_back(points.at(point));
    }
}


int k_means(const size_t num_of_clusters,
        const std::vector<std::vector<double> > &points,
        std::vector<std::set<size_t> > &clusters) {
    
    const size_t N = points.size();
    if (N == 0) {
        return 0;
    }
    std::vector<std::vector<double> > centers;
 
    k_means_pp(num_of_clusters, points, centers);

    const double eps = 0.001;
    double sum_shift_centers;
    int iter = 0;
    
    do {
        clusters = std::vector<std::set<size_t> >(num_of_clusters, std::set<size_t>());
        for (size_t point = 0; point < N; ++point) {
            double min_dist = my_distance(points[point], centers[0]);
            size_t near_cntr = 0;
            
            for (size_t cntr = 1; cntr < num_of_clusters; ++cntr) {
                double dist = my_distance(points[point], centers[cntr]);
                if (dist < min_dist) {
                    min_dist = dist;
                    near_cntr = cntr;
                }
            }
            
            clusters[near_cntr].insert(point);
        }
        
        sum_shift_centers = 0;
        for (size_t cntr = 0; cntr < num_of_clusters; ++cntr) {
            std::vector<double> new_centr;
            center_of_mass(points, clusters[cntr], new_centr);
            sum_shift_centers += my_distance(new_centr, centers[cntr]);
            centers[cntr] = new_centr;
        }
        ++iter;
        
    }
    while (sum_shift_centers > eps);
    
    return iter;
}