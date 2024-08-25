/*
 * Created on Sat Aug 17 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include "Vibrator.h"
#include "IBuilder.h"
#include "needed.hpp"
#include "Side.hpp"

#include <memory>

namespace MaskUP
{
namespace Build
{
class VibratorBuilder : public IBuilder <::MaskUP::Component::Vibrator>
{
public:
    virtual VibratorBuilder *reset () override ;
    VibratorBuilder *assignSide (const ::MaskUP::Enum::Side inSide) ;

    virtual std::unique_ptr <::MaskUP::Component::Vibrator> build () override;

private:

    std::unique_ptr <::MaskUP::Component::Vibrator> m_pVibrator;

};
}
}