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
#pragma once

#include <string>
#include <map>

#include <celix/dm/Properties.h>

namespace celix::rsa {

    /**
     * @brief Endpoint class which represent a remote endpoint discovered by the framework.
     */
    class Endpoint {
    public:
        static constexpr const char * const IDENTIFIER = "endpoint.id";
        static constexpr const char * const IMPORTED = "service.imported";
        static constexpr const char * const IMPORT_CONFIGS = "service.imported.configs";
        static constexpr const char * const EXPORTS = "service.exported.interfaces";
        static constexpr const char * const OBJECTCLASS = "endpoint.objectClass";
        static constexpr const char * const SCOPE = "endpoint.scope";
        static constexpr const char * const TOPIC = "endpoint.topic";


        /**
         * Endpoint constructor.
         * @param properties celix properties with information about this endpoint and what its documenting.
         */
        explicit Endpoint(celix::Properties properties) : _celixProperties{std::move(properties)} {
            // TODO validate mandatory properties are set.
        }

        [[nodiscard]] const celix::dm::Properties& getProperties() const {
            return _celixProperties;
        }

        [[nodiscard]] std::string getEndpointId() const {
            return _celixProperties.get(IDENTIFIER);
        }

        [[nodiscard]] std::string getExportedInterfaces() const {
            return _celixProperties.get(EXPORTS);
        }



    protected:
        celix::dm::Properties _celixProperties;

    };
} // end namespace celix::rsa.
