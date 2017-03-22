#pragma once

#include "mqtt/simple_mqtt_publisher.h"
#include <string>

namespace TooManyPeeps {

  class CountReporter
  {
    private:
      static const std::string ADDRESS;
      static const std::string BASE_TOPIC;
      static const std::string IN_TOPIC_PART;
      static const std::string OUT_TOPIC_PART;

    private:
      std::string clientId;
      std::string deviceIdentifier;
      Mqtt::SimpleMqttPublisher * mqttPublisher;

      std::string inTopic;
      std::string outTopic;

    public:
      CountReporter(std::string deviceIdentifier);
      ~CountReporter(void);

    public:
      void in(int numberOfPeople);
      void out(int numberOfPeople);

    private:
      std::string create_json_count(int numberOfPeople);
  };

};
