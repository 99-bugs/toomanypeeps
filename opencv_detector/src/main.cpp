#include "lib/camera/web_camera.h"
#include "lib/filter/filter_chain.h"
#include "lib/filter/frame_grab.h"
#include "lib/filter/gaussian_blur.h"
#include "lib/filter/display.h"
#include "lib/filter/background_extractor.h"

using namespace TooManyPeeps;

int main()
{
  WebCamera camera;

  cv::Mat original;
  cv::Mat blurred;
  cv::Mat mog2Processed;

  FilterChain blobDetect;

  blobDetect.add(new FrameGrab(original, &camera));
  blobDetect.add(new Display(original, "Original"));
  blobDetect.add(new GaussianBlur(original, blurred, 5));
  blobDetect.add(new BackgroundExtractor(blurred, mog2Processed, 100, 16));
  blobDetect.add(new Display(mog2Processed, "After Background Extractor"));

  do {
    blobDetect.execute();
  } while (true);

  return 0;
}
