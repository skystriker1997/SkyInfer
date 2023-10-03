#include "layer/concrete/flatten.hpp"

namespace sky_infer {
    LayerFlatten::LayerFlatten(std::string name, std::shared_ptr<Batchf> input, std::shared_ptr<Batchf> output, int start_dim, int end_dim): type_(LayerType::Flatten), name_(std::move(name)), input_(std::move(input)), output_(std::move(output)), start_dim_(start_dim), end_dim_(end_dim) {};

    void LayerFlatten::Forward() {
        check_(input_->size() == output_->size())
                << "failed to execute flatten layer; input and output should have same batch sizes";

        int start = start_dim_ < 0 ? 4 + start_dim_ : start_dim_;
        int end = end_dim_ < 0 ? 4 + end_dim_ : end_dim_;

        check_(start < end) << "failed to execute flatten layer; the start dimension must be less than end dimension";
        check_(start >= 1 && end <= 3)
                << "failed to execute flatten layer; the start dimension cannot be less than 1 and the end dimension cannot be greater than 3";

        if (start == 1 && end == 3) {
            for (int i = 0; i < input_->size(); i++) {
                Tensor<float>& in = input_->at(i);
                Tensor<float>& out = output_->at(i);
                int new_channel = 1;
                int new_row = 1;
                int new_col = in.Channels() * in.Rows() * in.Cols();
                check_(out.Channels() == new_channel && out.Rows() == new_row &&
                       out.Cols() == new_col)
                        << "failed to execute flatten layer; the shape of output tensor is not as expected";
                out = in.Reshape({new_channel, new_row, new_col});
            }
        } else if (start == 2 && end == 3) {
            for (int i = 0; i < input_->size(); i++) {
                Tensor<float>& in = input_->at(i);
                Tensor<float>& out = output_->at(i);
                int new_channel = 1;
                int new_row = in.Channels();
                int new_col = in.Rows() * in.Cols();
                check_(out.Channels() == new_channel && out.Rows() == new_row &&
                       out.Cols() == new_col)
                        << "failed to execute flatten layer; the shape of output tensor is not as expected";
                out = in.Reshape({new_channel, new_row, new_col});
            }
        } else {
            for (int i = 0; i < input_->size(); i++) {
                Tensor<float>& in = input_->at(i);
                Tensor<float>& out = output_->at(i);
                int new_channel = 1;
                int new_row = in.Channels() * in.Rows();
                int new_col = in.Cols();
                check_(out.Channels() == new_channel && out.Rows() == new_row &&
                       out.Cols() == new_col)
                        << "failed to execute flatten layer; the shape of output tensor is not as expected";
                out = in.Reshape({new_channel, new_row, new_col});
            }
        }
    }
}