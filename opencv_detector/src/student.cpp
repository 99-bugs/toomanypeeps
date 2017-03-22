#include "student.h"

// Hier maken we een lijst van filters aan
FilterChain filters;

// Dit zijn de tussenliggende beelden
cv::Mat original;
cv::Mat processed;

// Hier maken we een MQTT publisher aan
SimpleMqttPublisher	mqttPublisher("tcp://mqtt.labict.be", "ytty546365fdyr654354fdg");

// De init methode wordt enkel bij het opstarten uitgevoerd
void init(FrameGrabber * frameGrabber) {
  // Frame ophalen
  filters.add(new FrameGrab(original, frameGrabber));

  // Ruis wegwerken maar de overgangen behouden
  filters.add(new GaussianBlur(original, processed));

  // De voorgrond uithalen
  filters.add(new BackgroundExtractor(processed));

  // Weghalen van de schaduwen die door de BackgroundExtractor worden toegevoegd
  filters.add(new BinaryThreshold(processed, 200)); // Remove shadows

  // Gaten opvullen
  filters.add(new Blur(processed));
  filters.add(new Dilate(processed));
  filters.add(new Erode(processed));

  // Beetje uitvergroten van onze blobs en omringende stukjes meenemen
  filters.add(new Dilate(processed));
  filters.add(new GaussianBlur(processed));

  // Terug overgaan naar een puur zwart-wit beeld
  filters.add(new BinaryThreshold(processed, 50));

  // Wat kleiner maken van de blobs
  filters.add(new Erode(processed));

  // Zoeken van de contouren
  FindContours * finder = new FindContours(processed, original);
  filters.add(finder);

  // Volgen van de objecten
  // Zeg tegen de tracker dat het zijn bevindingen moet bezorgen aan onze update functie
  TrackObjects * tracker = new TrackObjects(processed, original, finder, update);
  filters.add(tracker);

  // Eindresultaat teruggeven
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

  mqttPublisher.publish(json, "toomanypeeps/demo/counter");
}
