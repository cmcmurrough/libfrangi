/*******************************************************************************************************************/ /**
 * @file cv_frangi.cpp
 * @brief C++ example for detecting vesselness with "Multiscale vessel enhancement filtering"
 * 
 * based on library: https://ntnu-bioopt.github.io/software/libfrangi.html
 * 
 * @author Christopher D. McMurrough
 **********************************************************************************************************************/

#include <opencv2/opencv.hpp>
#include "libfrangi.h"

/*******************************************************************************************************************/ /**
 * @brief program entry point
 * @param[in] argc number of command line arguments
 * @param[in] argv string array of command line arguments
 * @return return code (0 for normal termination)
 * @author Christoper D. McMurrough
 **********************************************************************************************************************/
int main(int argc, char *argv[])
{
    // store execution parameters
    std::string imageFilename;

    // define the command line arguments
    const std::string keys =
        "{help h        |                                   | show execution options}"
        "{image i       | <none>                            | input image file name}";

    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("USAGE: cv_holistically_nested_edges <model_filename>, <image_filename>");

    // validate and parse the command line arguments
    if (parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }

    // validate and parse the command line arguments
    imageFilename = parser.get<std::string>("image");
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    // open the input image
    cv::Mat imageIn = cv::imread(imageFilename, cv::IMREAD_GRAYSCALE);
    cv::imshow("imageIn", imageIn);

    // perform the filtering
    cv::Mat imageInFloat;
    imageIn.convertTo(imageInFloat, CV_32FC1);
    cv::Mat vesselness, scale, angles;
    frangi2d(imageInFloat, vesselness, scale, angles);

    // display the result
    cv::imshow("vesselness", vesselness * 255);
    cv::waitKey();

    return 0;
}