# Image Intensity Analyzer

The Image Intensity Analyzer is a C++ program that analyzes the intensity values of grayscale and color images. It calculates various statistical properties such as probability distribution, mean, variance, and central moments of the intensity values.

## Features

- Supports grayscale and color images.
- Reads images from a specified directory and its subdirectories.
- Analyzes intensity values of grayscale images:
  - Calculates the probability distribution of intensity values.
  - Checks the validity of the probability distribution.
  - Computes the mean and variance of intensity values.
  - Calculates central moments of intensity values.
- Analyzes intensity values of color images:
  - Separates the intensity values into red, green, and blue channels.
  - Calculates the probability distribution of each channel's intensity values.
  - Checks the validity of the probability distributions.
  - Computes the mean and variance of each channel's intensity values.
  - Calculates central moments of each channel's intensity values.
- Provides informative output for each analyzed image, including:
  - Image type (grayscale or color).
  - Probability distribution and sum of probability distribution.
  - Mean and variance of intensity values.
  - Central moments for a user-defined value of n.
- Supports customization of the value of n for calculating central moments.
- Displays the analyzed images for visual reference.

## Dependencies

- OpenCV (version 2 or higher)

## Note

- The program assumes that the intensity values of grayscale images range from 0 to 255.
- The program assumes that color images are stored in the RGB color space.

## Contributors

- [Andrew Edwards](https://www.github.com/andwards)
