// Copyright 2021 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef GRPC_CORE_LIB_RESOURCE_QUOTA_API_H
#define GRPC_CORE_LIB_RESOURCE_QUOTA_API_H

#include <grpc/support/port_platform.h>

#include "src/core/lib/channel/channel_args.h"
#include "src/core/lib/resource_quota/resource_quota.h"

typedef struct grpc_resource_quota grpc_resource_quota;

namespace grpc_core {

// TODO(ctiller): This is a hack. We need to do real accounting instead of
// hard coding.
constexpr size_t kResourceQuotaCallSize = 15 * 1024;
constexpr size_t kResourceQuotaChannelSize = 50 * 1024;

// Retrieve the resource quota from the channel args.
// UB if not set.
ResourceQuotaRefPtr ResourceQuotaFromChannelArgs(const grpc_channel_args* args);

// Take some channel args:
// If there is a resource quota set, copy args and return that.
// If there is no resource quota set, set a default, and return new
// channel args. Call grpc_channel_args_destroy on the input args.
grpc_channel_args* EnsureResourceQuotaInChannelArgs(
    const grpc_channel_args* args);

// Create channel args with just the passed in resource quota
grpc_channel_args* ChannelArgsWrappingResourceQuota(ResourceQuotaRefPtr);

inline ResourceQuota* ResourceQuotaFromC(grpc_resource_quota* quota) {
  return reinterpret_cast<ResourceQuota*>(quota);
}

}  // namespace grpc_core

#endif  // GRPC_CORE_LIB_RESOURCE_QUOTA_API_H
