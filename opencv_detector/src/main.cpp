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
  bool paused = false;
  bool step = false;

#if defined(USE_RASPBERRY_PI)
  PiCamera frame_grabber;
  // frame_grabber.set_width(320);
  // frame_grabber.set_height(240);
#elif defined(USE_VIDEO_FILE)
  std::string filename = "./video_samples/sample-02.mp4";
  if (argc >= 2) {
    filename = std::string(argv[1]);
  }
  VideoFile frame_grabber(filename);
  paused = true;
  std::cout << "Watch it. Video is currently paused. Press p to pause/unpause, s to step and esc to quit" << std::endl;

#elif defined(USE_IP_CAMERA)
  std::string streamAddress = "http://toomanypeeps:demo@10.182.34.103/mjpeg.cgi?user=toomanypeeps&password=demo&channel=0&.mjpg";

  if (argc >= 2) {
    streamAddress = std::string(argv[1]);
  }
  IPCamera frame_grabber(streamAddress);
#else
  WebCamera frame_grabber;
#endif

  init(&frame_grabber);
  do {
    if (!paused || step) {
      // double time_=cv::getTickCount();
      // double secondsElapsed= double ( cv::getTickCount()-time_ ) /double ( cv::getTickFrequency() );
      // std::cout << "FPS = " << (1.0 /secondsElapsed ) << std::endl;
      step = false;
      loop();
    }

    char key = cv::waitKey(10);
    if(key == 'p') {
      paused = !paused;
    } else if (key == 's') {
      step = true;
    } else if (key == 27) {
      break;
    }

  } while (true);

  return 0;
}
