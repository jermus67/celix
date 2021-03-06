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

#include "celix/rsa/Endpoint.h"
#include <ConfiguredEndpointProperties.h>

#include <optional>
#include <string>

#include <rapidjson/document.h>

namespace celix::rsa {

/**
 * This subclass of Endpoint contains logic to parse (rapid) JSON values into endpoint celix properties.
 */
class ConfiguredEndpoint : public Endpoint {
public:

    ConfiguredEndpoint() = delete;

    explicit ConfiguredEndpoint(const rapidjson::Value& endpointJson);

    const ConfiguredEndpointProperties& getConfiguredProperties() const;

    std::string ToString() const {
        return "[ConfiguredEndpoint (" + _configuredProperties->ToString() + ")]";
    }

private:

    std::optional<ConfiguredEndpointProperties> _configuredProperties;
};

} // end namespace celix::rsa.
