/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef CELIX_EVENT_H
#define CELIX_EVENT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <celix_properties.h>
#include <celix_cleanup.h>

typedef struct celix_event celix_event_t;


celix_event_t* celix_event_create(const char* topic, const celix_properties_t* properties);

void celix_event_release(celix_event_t* event);

CELIX_DEFINE_AUTOPTR_CLEANUP_FUNC(celix_event_t, celix_event_release);

const char* celix_event_getTopic(const celix_event_t* event);

const celix_properties_t* celix_event_getProperties(const celix_event_t* event);

celix_event_t* celix_event_retain(celix_event_t* event);


#ifdef __cplusplus
}
#endif

#endif //CELIX_EVENT_H
