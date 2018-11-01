/**
 *Licensed to the Apache Software Foundation (ASF) under one
 *or more contributor license agreements.  See the NOTICE file
 *distributed with this work for additional information
 *regarding copyright ownership.  The ASF licenses this file
 *to you under the Apache License, Version 2.0 (the
 *"License"); you may not use this file except in compliance
 *with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *Unless required by applicable law or agreed to in writing,
 *software distributed under the License is distributed on an
 *"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 *specific language governing permissions and limitations
 *under the License.
 */

#ifndef CELIX_PUBSUB_ZMQ_ADMIN_H
#define CELIX_PUBSUB_ZMQ_ADMIN_H

#include <pubsub_admin.h>
#include "celix_api.h"
#include "log_helper.h"
#include "pubsub_nanomsg_topic_receiver.h"
#include "../../../shell/shell/include/command.h"

#define PUBSUB_NANOMSG_ADMIN_TYPE       "zmq"
#define PUBSUB_NANOMSG_URL_KEY          "zmq.url"

#define PUBSUB_NANOMSG_VERBOSE_KEY      "PSA_ZMQ_VERBOSE"
#define PUBSUB_NANOMSG_VERBOSE_DEFAULT  true

#define PUBSUB_NANOMSG_PSA_IP_KEY       "PSA_IP"
#define PUBSUB_NANOMSG_PSA_ITF_KEY		"PSA_INTERFACE"

#define PUBSUB_NANOMSG_DEFAULT_IP       "127.0.0.1"

//typedef struct pubsub_nanomsg_admin pubsub_nanomsg_admin_t;
class pubsub_nanomsg_admin {
public:
    pubsub_nanomsg_admin(celix_bundle_context_t *ctx, log_helper_t *logHelper);
    pubsub_nanomsg_admin(const pubsub_nanomsg_admin&) = delete;
    pubsub_nanomsg_admin& operator=(const pubsub_nanomsg_admin&) = delete;
    ~pubsub_nanomsg_admin();
    void start();
    void stop();

private:
    void addSerializerSvc(void *svc, const celix_properties_t *props);
    void removeSerializerSvc(void */*svc*/, const celix_properties_t *props);
    celix_status_t matchPublisher(long svcRequesterBndId, const celix_filter_t *svcFilter,
                                                      double *score, long *serializerSvcId);
    celix_status_t matchSubscriber(long svcProviderBndId,
                                                       const celix_properties_t *svcProperties, double *score,
                                                       long *serializerSvcId);
    celix_status_t matchEndpoint(const celix_properties_t *endpoint, bool *match);

    celix_status_t setupTopicSender(const char *scope, const char *topic,
                                                        long serializerSvcId, celix_properties_t **publisherEndpoint);
    celix_status_t teardownTopicSender(const char *scope, const char *topic);

    celix_status_t setupTopicReceiver(const char *scope, const char *topic,
                                                          long serializerSvcId, celix_properties_t **subscriberEndpoint);
    celix_status_t teardownTopicReceiver(const char *scope, const char *topic);

    celix_status_t addEndpoint(const celix_properties_t *endpoint);
    celix_status_t removeEndpoint(const celix_properties_t *endpoint);

    celix_status_t executeCommand(char *commandLine __attribute__((unused)), FILE *out,
                                                        FILE *errStream __attribute__((unused)));

    celix_status_t connectEndpointToReceiver(pubsub_nanomsg_topic_receiver_t *receiver,
                                                                   const celix_properties_t *endpoint);

    celix_status_t disconnectEndpointFromReceiver(pubsub_nanomsg_topic_receiver_t *receiver,
                                                                        const celix_properties_t *endpoint);
    celix_bundle_context_t *ctx;
    log_helper_t *log;
    pubsub_admin_service_t adminService{};
    long adminSvcId = -1L;
    long cmdSvcId = -1L;
    command_service_t cmdSvc{};
    long serializersTrackerId = -1L;

    const char *fwUUID{};

    char* ipAddress{};

    unsigned int basePort{};
    unsigned int maxPort{};

    double qosSampleScore{};
    double qosControlScore{};
    double defaultScore{};

    bool verbose{};

    struct {
        celix_thread_mutex_t mutex;
        hash_map_t *map; //key = svcId, value = psa_nanomsg_serializer_entry_t*
    } serializers{};

    struct {
        celix_thread_mutex_t mutex;
        hash_map_t *map; //key = scope:topic key, value = pubsub_nanomsg_topic_sender_t*
    } topicSenders{};

    struct {
        celix_thread_mutex_t mutex;
        hash_map_t *map; //key = scope:topic key, value = pubsub_nanomsg_topic_sender_t*
    } topicReceivers{};

    struct {
        celix_thread_mutex_t mutex;
        hash_map_t *map; //key = endpoint uuid, value = celix_properties_t* (endpoint)
    } discoveredEndpoints{};

};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

celix_status_t pubsub_nanoMsgAdmin_executeCommand(void *handle, char *commandLine, FILE *outStream, FILE *errStream);

#endif //CELIX_PUBSUB_ZMQ_ADMIN_H
