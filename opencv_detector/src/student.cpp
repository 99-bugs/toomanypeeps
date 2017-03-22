#include "student.h"

// Hier maken we een lijst van filters aan
FilterChain filters;

// Dit zijn de tussenliggende beelden
cv::Mat original;
cv::Mat processed;

// Hier maken we een MQTT publisher aan
// SimpleMqttPublisher	mqttPublisher("tcp://broker.mqttdashboard.com", "vives_demo");

// De init methode wordt enkel bij het opstarten uitgevoerd
void init(FrameGrabber * frameGrabber) {
  filters.add(new FrameGrab(original, frameGrabber));
  filters.add(new GaussianBlur(original, processed));
  filters.add(new BackgroundExtractor(processed));

  // Kunnen we hier eigenlijk niet beter een redelijke erode doen en pas dan dilate?
  // Dit zou twee licht aan elkaar hangende blobs kunnen van elkaar halen

  // Weghalen van de schaduwen die door de BackgroundExtractor worden toegevoegd
  filters.add(new BinaryThreshold(processed, 200)); // Remove shadows
  filters.add(new Blur(processed));
  filters.add(new Dilate(processed));
  filters.add(new Erode(processed));
  filters.add(new Dilate(processed));

  // Dit gaat volgens mij kleine gaten opvullen samen met de opvolgende THreshold
  filters.add(new GaussianBlur(processed));

  // Leave this
  filters.add(new BinaryThreshold(processed, 50));
  filters.add(new Erode(processed));

  FindContours * finder = new FindContours(processed, original);
  filters.add(finder);

  // Zeg tegen de tracker dat het zijn bevindingen moet bezorgen aan onze update functie
  TrackObjects * tracker = new TrackObjects(processed, original, finder, update);
  filters.add(tracker);

  filters.add(new Display(original, "Contours & Tracker"));
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

  cout << "MQTT: " << json << endl;

  // mqttPublisher.publish(json, "toomanypeeps/nico/counter");
    // retain ??
}
