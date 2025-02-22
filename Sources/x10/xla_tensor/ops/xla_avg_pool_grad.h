/*
 * Copyright 2020 TensorFlow Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "tensorflow/compiler/xla/xla_client/util.h"
#include "tensorflow/compiler/tf2xla/xla_tensor/ir.h"
#include "tensorflow/compiler/xla/client/lib/pooling.h"

namespace swift_xla {
namespace ir {
namespace ops {

class XlaAvgPoolGrad : public Node {
 public:
  XlaAvgPoolGrad(const Value& out_backprop,
                 std::vector<int64_t> gradients_size,
                 std::vector<int64_t> kernel_size,
                 std::vector<int64_t> stride,
                 std::vector<std::pair<int64_t, int64_t>> spatial_padding,
                 const xla::TensorFormat& data_format,
                 const bool counts_include_padding);

  NodePtr Clone(OpList operands) const override;

  XlaOpVector Lower(LoweringContext* loctx) const override;

  std::string ToString() const override;

  const std::vector<int64_t>& gradients_size() const {
    return gradients_size_;
  }

  const std::vector<int64_t>& kernel_size() const { return kernel_size_; }

  const std::vector<int64_t>& stride() const { return stride_; }

  const std::vector<std::pair<int64_t, int64_t>>& spatial_padding()
      const {
    return spatial_padding_;
  }

  const xla::TensorFormat& data_format() const { return data_format_; }

  bool counts_include_padding() const { return counts_include_padding_; }

 private:
  // Size of input gradients.
  std::vector<int64_t> gradients_size_;
  // The parameters of the pooling.
  std::vector<int64_t> kernel_size_;
  std::vector<int64_t> stride_;
  std::vector<std::pair<int64_t, int64_t>> spatial_padding_;
  xla::TensorFormat data_format_;
  // Whether the counts used to compute the average should include the added
  // padding.
  bool counts_include_padding_;
};

}  // namespace ops
}  // namespace ir
}  // namespace swift_xla
