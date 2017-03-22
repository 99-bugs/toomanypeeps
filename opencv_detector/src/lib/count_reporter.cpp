#include "count_reporter.h"

#include <iostream>
#include <sstream>

namespace TooManyPeeps {

	const std::string CountReporter::ADDRESS("tcp://broker.mqttdashboard.com");
	const std::string CountReporter::BASE_TOPIC("toomanypeeps");
	const std::string CountReporter::IN_TOPIC_PART("in");
	const std::string CountReporter::OUT_TOPIC_PART("out");

	CountReporter::CountReporter(std::string deviceIdentifier) {
		this->deviceIdentifier = deviceIdentifier;
		clientId = "__MAC_ADDRESS__";

		mqttPublisher = new Mqtt::SimpleMqttPublisher(ADDRESS, clientId);

		inTopic = BASE_TOPIC + "/" + deviceIdentifier + "/" + IN_TOPIC_PART;
		outTopic = BASE_TOPIC + "/" + deviceIdentifier + "/" + OUT_TOPIC_PART;
  }

	CountReporter::~CountReporter(void) {
		delete mqttPublisher;
  }

	void CountReporter::in(int numberOfPeople) {
		mqttPublisher->publish(create_json_count(numberOfPeople), inTopic);
  }


	void CountReporter::out(int numberOfPeople) {
		mqttPublisher->publish(create_json_count(numberOfPeople), outTopic);
  }

	std::string CountReporter::create_json_count(int numberOfPeople) {
		std::stringstream ss;
		ss << "{\"count\":" << numberOfPeople << "}";
		return ss.str();
	}

};
