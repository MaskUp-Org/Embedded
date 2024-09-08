/*
 * Created on Sat Aug 17 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include "ServoMotor.h"
#include "IBuilder.h"
#include "needed.hpp"
#include "Position.hpp"

#include <memory>

namespace MaskUP
{
namespace Build
{
class ServoMotorBuilder : public IBuilder <::MaskUP::Component::ServoMotor>
{
public:
    virtual ServoMotorBuilder* reset() override;
    ServoMotorBuilder* assignDefaultPosition(const ::MaskUP::Enum::Position inPosition);

    virtual std::unique_ptr <::MaskUP::Component::ServoMotor> build() override;

private:

    std::unique_ptr <::MaskUP::Component::ServoMotor> m_pServoMotor;
    bool m_isReset;

};
}
}