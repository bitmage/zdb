/*
 * ZDB Copyright 2017 Regents of the University of Michigan
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy
 * of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef ZDB_SRC_KAFKA_TOPIC_H
#define ZDB_SRC_KAFKA_TOPIC_H

#include <string>

#include <librdkafka/rdkafkacpp.h>

#include "transport/connection.h"

namespace zdb {

class KafkaConnection : public Connection {
 public:
  KafkaConnection();
  ~KafkaConnection();

  bool connect(const std::string& brokers,
               const std::string& topic,
               const std::string& client_id);

 protected:
  RdKafka::Conf* m_conf = nullptr;
  RdKafka::Conf* m_tconf = nullptr;
  void delete_conf_objects();
};

class KafkaConsumerConnection : public KafkaConnection {
 public:
  KafkaConsumerConnection();
  ~KafkaConsumerConnection();

  ClientType client_type() const override {
    return ClientType::KAFKA_CONSUMER;
  }

  Message consume();

 private:
  virtual bool connect_impl(const std::string& brokers,
                            const std::string& topic,
                            const std::string& client_id) override;

  RdKafka::KafkaConsumer* m_consumer = nullptr;
  RdKafka::Topic* m_topic = nullptr;

  KafkaConsumerConnection(const KafkaConsumerConnection&) = delete;
};

class KafkaProducerConnection : public KafkaConnection {
 public:
  KafkaProducerConnection();
  ~KafkaProducerConnection();

  ClientType client_type() const override {
    return ClientType::KAFKA_PRODUCER;
  }

  Message produce(const std::string& msg);
  Message produce_blocking(const std::string& msg, size_t max_attempts);

 private:
  virtual bool connect_impl(const std::string& brokers,
                            const std::string& topic,
                            const std::string& client_id) override;

  RdKafka::Conf* m_conf = nullptr;
  RdKafka::Conf* m_tconf = nullptr;
  RdKafka::Producer* m_producer = nullptr;
  RdKafka::Topic* m_topic = nullptr;
};

}  // namespace zdb

#endif /* ZDB_SRC_KAFKA_TOPIC_H */
