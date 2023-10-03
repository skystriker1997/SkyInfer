#ifndef SKY_INFER_LAYER_SIGMOID
#define SKY_INFER_LAYER_SIGMOID


#include "layer/layer.hpp"

namespace sky_infer {
    class LayerSigmoid: public Layer {
    private:

        std::string name_;
        LayerType type_;
        Check check_;
        std::vector<std::string> input_name_;
        std::vector<std::string> output_name_;

        std::shared_ptr<Batchf> input_;
        std::shared_ptr<Batchf> output_;


    public:

        LayerSigmoid(std::string name, std::shared_ptr<Batchf> input, std::shared_ptr<Batchf> output);

        void Forward() override;

        ~LayerSigmoid() override = default;
    };
}




#endif