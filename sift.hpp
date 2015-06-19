#ifndef SIFT_HPP
#define SIFT_HPP

#include <cmath>
#include <vigra/multi_array.hxx>

#include "types.hpp"
#include "matrix.hpp"

using img_epochs = std::vector<std::vector<vigra::MultiArray<2, f32_t>>>;
using interest_point_epochs = std::vector<std::vector<Matrix<f32_t>>>; 

class Sift {
public:
    /*
    * Processes the whole Sift calculation
    * @param the given image
    * @param with standard value 1.6
    * @param with standard value square root of 2
    * @param How many DOGs should be created per epoch
    */
    void calculate(vigra::MultiArray<2, f32_t>&, u16_t epochs = 4, f32_t sigma = 1.6, 
            f32_t k = std::sqrt(2),  u16_t dogPerEpoch = 3) const;

private:
    /*
    * Keypoint Location uses Taylor expansion to filter the weak interest points.
    * @param the vector with epochs and the keypoints as tuples inside the epochs, which will be
    * filtered
    */
    void _eliminateEdgeResponses(interest_point_epochs&, const img_epochs&) const;

    /*
    * Finds the Scale space extrema.
    * @param a vector of vectors of DOGs
    */
    const interest_point_epochs _findScaleSpaceExtrema(const img_epochs& dogs) const;

    /*
    * Creates the Laplacians of Gaussians for the count of epochs.
    * @param the given img
    * @param sigma for gaussian
    * @param k the constant which will be calculated on sigma
    * @param How many DOGs should be created per epoch
    * @return a vector with the epochs, which contains DOGs
    */
    const img_epochs _createDOGs(vigra::MultiArray<2, f32_t>&, u16_t, f32_t, f32_t, u16_t) const;

    /*
    * Resamples an image by 0.5
    * @param in the input image
    * @return the output image
    */
    const vigra::MultiArray<2, f32_t> _reduceToNextLevel(const vigra::MultiArray<2, f32_t>&, 
            f32_t) const;

    /**
    * Convolves a given image with gaussian with a given sigma
    * @param input the input image which will be convolved
    * @sigma the standard deviation for the gaussian
    * @return blured image
    */
    const vigra::MultiArray<2, f32_t> _convolveWithGauss(const vigra::MultiArray<2, f32_t>&, 
            f32_t) const;

    /**
    * Calculates the Laplacian of Gaussian, which is the differnce between 2
    * images which were convolved with gaussian under usage of a constant K
    * @param lower the image which lies lower in an octave
    * @param higher the image which lies higher in an octave
    * @return the laplacian of gaussian image, which contains our interest points
    */
    const vigra::MultiArray<2, f32_t> _DOG(const vigra::MultiArray<2, f32_t>&, 
            const vigra::MultiArray<2, f32_t>&) const;
};

#endif //SIFT_HPP
