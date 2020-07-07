#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "radar_utils.hpp"

inline bool exists(const std::string& name) {
    struct stat buffer;
    return !(stat (name.c_str(), &buffer) == 0);
}

int main() {
    std::string datadir = "/home/keenan/Documents/data/2019-01-10-14-36-48-radar-oxford-10k-partial/radar";
    float cart_resolution = 0.25;
    int cart_pixel_width = 1000;
    bool interpolate_crossover = true;

    // Get file names of the radar images
    DIR *dirp = opendir(datadir.c_str());
    struct dirent *dp;
    std::vector<std::string> radar_files;
    while ((dp = readdir(dirp)) != NULL) {
        if (exists(dp->d_name))
            radar_files.push_back(dp->d_name);
    }
    // Sort files in ascending order of time stamp
    std::sort(radar_files.begin(), radar_files.end(), less_than_img());

    std::cout << radar_files[0] << std::endl;
    std::cout << radar_files[1] << std::endl;
    std::cout << radar_files[2] << std::endl;

    float radar_resolution = 0.0432;
    std::vector<int64_t> timestamps;
    std::vector<float> azimuths;
    std::vector<bool> valid;
    cv::Mat fft_data;

    load_radar(datadir + "/" + radar_files[100], timestamps, azimuths, valid, fft_data);

    // cv::imshow("radar", fft_data);
    // cv::waitKey(0);

    cv::Mat cart_img;
    radar_polar_to_cartesian(azimuths, fft_data, radar_resolution, cart_resolution, cart_pixel_width,
        interpolate_crossover, cart_img);

    cv::imshow("cart", cart_img);
    cv::waitKey(0);

    return 0;
}