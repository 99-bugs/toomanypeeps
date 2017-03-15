#include "lib/camera/web_camera.h"
#include "lib/filter/filter_chain.h"
#include "lib/filter/frame_grab.h"
#include "lib/filter/gaussian_blur.h"
#include "lib/filter/display.h"

using namespace TooManyPeeps;

int main()
{
  WebCamera camera;

  cv::Mat original;
  cv::Mat blurred;
  cv::Mat evenMoreBlurred;

  FilterChain blobDetect;

  blobDetect.add(new FrameGrab(original, &camera));
  blobDetect.add(new Display(original, "Original"));
  blobDetect.add(new GaussianBlur(original, blurred, 50));
  blobDetect.add(new GaussianBlur(blurred, evenMoreBlurred, 1000));
  blobDetect.add(new Display(evenMoreBlurred, "Even more Blurred"));

  do {
    blobDetect.execute();
  } while (true);

  return 0;
}
