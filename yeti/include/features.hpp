#pragma once
#include <vector>
#include <opencv2/core.hpp>
#include "radar_utils.hpp"

/*!
   \brief Extract CFAR features from the polar radar data, one azimuth at a time (1D)
   \param fft_data Polar radar power readings
   \param window_size Length of window used to estimate local clutter power
   \param scale local clutter power is multiplied by scale
   \param guard_cells How many cells on the left and right side of the test cell are ignored before estimation
   \param min_range We ignore the range bins less than this
   \param targets [out] Matrix of feature locations (azimuth_bin, range_bin, 1) x N
*/
void cfar1d(cv::Mat fft_data, int window_size, float scale, int guard_cells, int min_range, Eigen::MatrixXf &targets);

/*!
   \brief Extract features from polar radar data using the method described in cen_icra18
   \param fft_data Polar radar power readings
   \param zq If y(i, j) > zq * sigma_q then it is considered a potential target point
   \param sigma_gauss std dev of the gaussian filter uesd to smooth the radar signal
   \param min_range We ignore the range bins less than this
   \param targets [out] Matrix of feature locations (azimuth_bin, range_bin, 1) x N
*/
void cen2018features(cv::Mat fft_data, float zq, int sigma_gauss, int min_range, Eigen::MatrixXf &targets);

/*!
   \brief Extract features from polar radar data using the method described in cen_icra19
   \param fft_data Polar radar power readings
   \param max_points Maximum number of targets points to be extracted from the radar image
   \param min_range We ignore the range bins less than this
   \param targets [out] Matrix of feature locations (azimuth_bin, range_bin, 1) x N
*/
void cen2019features(cv::Mat fft_data, int max_points, int min_range, Eigen::MatrixXf &targets);