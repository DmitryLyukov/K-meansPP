#ifndef K_MEANS_PP_HPP
#define K_MEANS_PP_HPP

#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>

double my_sqr_distance(const std::vector<double> &A,
        const std::vector<double> &B);

double my_distance(const std::vector<double> &A,
        const std::vector<double> &B);

void center_of_mass(const std::vector<std::vector<double> > &points,
        const std::set<size_t> &cluster, std::vector<double> &center);

void k_means_pp(const size_t num_of_clusters,
        const std::vector<std::vector<double> > &points,
        std::vector<std::vector<double> > &centers);

int k_means(const size_t num_of_clusters,
        const std::vector<std::vector<double> > &points,
        std::vector<std::set<size_t> > &clusters);

#endif  // K_MEANS_PP_HPP
