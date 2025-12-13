#pragma once

namespace nn
{
enum class Activation
{
    Relu,
    Logistic
};

enum class Loss
{
    LogLoss,
    MSE
};

constexpr double epsilon = 1e-9;
}
