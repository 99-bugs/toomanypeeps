#include "lib/camera/web_camera.h"
#include "lib/filter/filter_chain.h"
#include "lib/filter/frame_grab.h"
#include "lib/filter/gaussian_blur.h"

using namespace TooManyPeeps;

int main()
{
  WebCamera camera;

  cv::Mat original;
  cv::Mat blurred;
  cv::Mat evenMoreBlurred;

  FilterChain blobDetect;

  blobDetect.add(new FrameGrab(original, &camera));
  blobDetect.add(new GaussianBlur(original, blurred, 50));
  blobDetect.add(new GaussianBlur(blurred, evenMoreBlurred, 1000));

  do {
    blobDetect.execute();

    // [TODO] This can be filter too
    cv::imshow("this is you, smile! :)", blurred);
    if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC

    cv::imshow("BLURRED", evenMoreBlurred);
    if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC

  } while (true);

  return 0;
}
