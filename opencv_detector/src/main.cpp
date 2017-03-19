#include "lib/frame_grabber/web_camera.h"
#include "lib/filter/filter_chain.h"
#include "lib/filter/frame_grab.h"
#include "lib/filter/gaussian_blur.h"
#include "lib/filter/display.h"
#include "lib/filter/background_extractor.h"
#include "lib/filter/binary_threshold.h"
#include "lib/filter/dilate.h"
#include "lib/filter/erode.h"
#include "lib/filter/blur.h"
#include "lib/count_reporter.h"
#include "lib/frame_grabber/pi_camera.h"
#include <ctime>

#ifdef USE_RASPBERRY_PI
  #pragma message ("Creating Raspberry PI application")
#else
  #pragma message ("Creating non-Rasberry PI application")
#endif

const std::string DEVICE_IDENTIFIER("demo");

using namespace TooManyPeeps;
using namespace TooManyPeeps::Mqtt;

int main()
{
#ifdef USE_RASPBERRY_PI
  PiCamera camera;
#else
  WebCamera camera;
#endif

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

	CountReporter countReporter(DEVICE_IDENTIFIER);
  countReporter.in(5);
  countReporter.out(16);

  do {
    double time_=cv::getTickCount();
    blobDetect.execute();
    double secondsElapsed= double ( cv::getTickCount()-time_ ) /double ( cv::getTickFrequency() );
    std::cout << "FPS = " << (1.0 /secondsElapsed ) << std::endl;
  } while (true);

  return 0;
}
