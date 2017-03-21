#include "student.h"
// This is the C++ file for the students

// Hier maken we een lijst van filters aan
FilterChain filters;

// Dit zijn de tussenliggende beelden
cv::Mat originalImage;
cv::Mat preProcess;
cv::Mat mog2Processed;
cv::Mat postProcess;

// Hier maken we een MQTT publisher aan
SimpleMqttPublisher	mqttPublisher("tcp://broker.mqttdashboard.com", "vives_demo");

// De init methode wordt enkel bij het opstarten uitgevoerd
void init(FrameGrabber * frameGrabber) {
  filters.add(new FrameGrab(originalImage, frameGrabber));
  filters.add(new GaussianBlur(originalImage, preProcess, 5));

  filters.add(new BackgroundExtractor(preProcess, mog2Processed, 100, 16));

  // Kunnen we hier eigenlijk niet beter een redelijke erode doen en pas dan dilate?
  // Dit zou twee licht aan elkaar hangende blobs kunnen van elkaar halen

  // Weghalen van de schaduwen die door de BackgroundExtractor worden toegevoegd
  filters.add(new BinaryThreshold(mog2Processed, postProcess, 200)); // Remove shadows
  filters.add(new Blur(postProcess, postProcess, 5));
  filters.add(new Dilate(postProcess, postProcess, 5));
  filters.add(new Erode(postProcess, postProcess, 3));
  filters.add(new Dilate(postProcess, postProcess, 5));

  // Dit gaat volgens mij kleine gaten opvullen samen met de opvolgende THreshold
  filters.add(new GaussianBlur(postProcess, postProcess, 10));

  // Leave this
  filters.add(new BinaryThreshold(postProcess, postProcess, 50));
  filters.add(new Erode(postProcess, postProcess, 2));
  // filters.add(new Display(postProcess, "Post-Processed"));

  FindContours * finder = new FindContours(postProcess, originalImage, 5000, 11000);
  filters.add(finder);

  TrackObjects * tracker = new TrackObjects(postProcess, originalImage, finder);
  filters.add(tracker);

  filters.add(new Display(originalImage, "Contours & Tracker"));
}

// De loop methode wordt per beeld 1x uitgevoerd
void loop(void) {
  filters.execute();
}

// update wordt uitgevoerd wanneer een nieuw telresultaat wordt bekomen
void update(int numberOfPeopleInside) {
  stringstream ss;
  ss << "{\"value\": " << numberOfPeopleInside << "}";
  string json = ss.str();

  mqttPublisher.publish(json, "toomanypeeps/nico/counter");
    // retain ??
}
