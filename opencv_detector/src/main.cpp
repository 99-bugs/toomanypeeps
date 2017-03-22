#include "lib/frame_grabber/web_camera.h"
#include "lib/frame_grabber/pi_camera.h"
#include "lib/frame_grabber/video_file.h"
#include "lib/frame_grabber/ip_camera.h"
#include <ctime>

using namespace TooManyPeeps;

#ifdef USE_RASPBERRY_PI
  #pragma message ("Creating Raspberry PI application")
#else
  #pragma message ("Creating non-Rasberry PI application")
#endif

void init(FrameGrabber * frameGrabber);
void loop(void);

int main(int argc, const char * argv[])
{
#if defined(USE_RASPBERRY_PI)
  PiCamera frame_grabber;
  frame_grabber.set_width(320);
  frame_grabber.set_height(240);
#elif defined(USE_VIDEO_FILE)
  std::string filename = "./video_samples/lab_demo.mp4";
  if (argc >= 2) {
    filename = std::string(argv[1]);
  }
  VideoFile frame_grabber(filename);
#elif defined(USE_IP_CAMERA)
  std::string streamAddress = "http://toomanypeeps:demo@10.182.33.103/mjpeg.cgi?user=toomanypeeps&password=demo&channel=0&.mjpg";
  if (argc >= 2) {
    streamAddress = std::string(argv[1]);
  }
  IPCamera frame_grabber(streamAddress);
#else
  WebCamera frame_grabber;
#endif

  bool paused = false;
  bool step = false;

  init(&frame_grabber);

  do {
    if (!paused || step) {
      // double time_=cv::getTickCount();
      // double secondsElapsed= double ( cv::getTickCount()-time_ ) /double ( cv::getTickFrequency() );
      // std::cout << "FPS = " << (1.0 /secondsElapsed ) << std::endl;
      step = false;
      loop();
    }

    char key = cv::waitKey(100);
    if(key == 'p') {
      paused = !paused;
    } else if (key == 's') {
      step = true;
    }

  } while (true);

  return 0;
}
