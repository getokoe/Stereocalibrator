# StereoCalibrator
Purpose of this software is to simplify the calibration process with chessboard patterns for stereo cameras and provide as good as possible calibration data. It heavily relies on the stereocamcalib library.
During the calibration process the provided images are sorted by their quality and only the best are used for calibration. These images will also be checked for the distribution/rotation of the chessboard pattern over the image.
The calibration data is saved as .csv and .npy files along with the undistorted images used for calibration.

Dependencies: Qt5 and stereocamcalib

Install:

1. Download StereoCalibrator (for example via wget)
2. cd ./stereocalibrator
2. mkdir build
3. cd ./build
4. qmake ..
5. make .

To start the software simply run ./Stereocalibrator.

