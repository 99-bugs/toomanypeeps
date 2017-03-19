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
#include "lib/frame_grabber/video_file.h"
#include <ctime>

#ifdef USE_RASPBERRY_PI
  #pragma message ("Creating Raspberry PI application")
#else
  #pragma message ("Creating non-Rasberry PI application")
#endif

const std::string DEVICE_IDENTIFIER("demo");

using namespace TooManyPeeps;
using namespace TooManyPeeps::Mqtt;

int main(int argc, const char * argv[])
{
#if defined(USE_RASPBERRY_PI)
  PiCamera frame_grabber;
  frame_grabber.set_width(320);
  frame_grabber.set_height(240);
#elif defined(USE_VIDEO_FILE)
  std::string filename = "./video_samples/demo.avi";
  if (argc >= 2) {
    filename = std::string(argv[1]);
  }
  VideoFile frame_grabber(filename);
#else
  WebCamera frame_grabber;
#endif

  cv::Mat original;
  cv::Mat preProcess;
  cv::Mat mog2Processed;
  cv::Mat postProcess;

  FilterChain blobDetect;

  blobDetect.add(new FrameGrab(original, &frame_grabber));
  blobDetect.add(new Display(original, "Original"));
  blobDetect.add(new GaussianBlur(original, preProcess, 5));
  blobDetect.add(new BackgroundExtractor(preProcess, mog2Processed, 100, 16));

  blobDetect.add(new BinaryThreshold(mog2Processed, postProcess, 200));
  blobDetect.add(new Blur(postProcess, postProcess, 5));
  blobDetect.add(new Dilate(postProcess, postProcess, 5));
  blobDetect.add(new Erode(postProcess, postProcess, 3));
  blobDetect.add(new Dilate(postProcess, postProcess, 5));
  blobDetect.add(new GaussianBlur(postProcess, postProcess, 10));

  // Leave this
  blobDetect.add(new BinaryThreshold(postProcess, postProcess, 50));
  blobDetect.add(new Erode(postProcess, postProcess, 2));
  blobDetect.add(new Display(postProcess, "Post-Processed"));

	// CountReporter countReporter(DEVICE_IDENTIFIER);
  // countReporter.in(5);
  // countReporter.out(16);

  do {
    double time_=cv::getTickCount();
    blobDetect.execute();
    double secondsElapsed= double ( cv::getTickCount()-time_ ) /double ( cv::getTickFrequency() );
    std::cout << "FPS = " << (1.0 /secondsElapsed ) << std::endl;
  } while (true);

  return 0;
}
