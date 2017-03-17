#include "lib/camera/web_camera.h"
#include "lib/filter/filter_chain.h"
#include "lib/filter/frame_grab.h"
#include "lib/filter/gaussian_blur.h"
#include "lib/filter/display.h"
#include "lib/filter/background_extractor.h"
#include "lib/filter/binary_threshold.h"
#include "lib/filter/dilate.h"
#include "lib/filter/erode.h"
#include "lib/filter/blur.h"

using namespace TooManyPeeps;

int main()
{
  WebCamera camera;

  cv::Mat original;
  cv::Mat blurred;
  cv::Mat mog2Processed;
  cv::Mat detection;
  cv::Mat otherBlur;

  FilterChain blobDetect;

  blobDetect.add(new FrameGrab(original, &camera));
  blobDetect.add(new Display(original, "Original"));
  blobDetect.add(new GaussianBlur(original, blurred, 5));
  blobDetect.add(new BackgroundExtractor(blurred, mog2Processed, 100, 16));
  blobDetect.add(new Dilate(mog2Processed, detection, 10));
  blobDetect.add(new Erode(detection, detection, 5));
  blobDetect.add(new Display(detection, "Final Result"));
  blobDetect.add(new Blur(original, otherBlur, 5));
  blobDetect.add(new Display(otherBlur, "Other Blur Result"));

  do {
    blobDetect.execute();
  } while (true);

  return 0;
}
