/*
 * Created on Aug Tue 05 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "VibratorBuilder.h"
#include <iostream>
#include <Arduino.h>
#include "FileReader.h"


namespace MaskUP
{
namespace Build
{

VibratorBuilder* VibratorBuilder::reset()
{
    m_pVibrator = ::MaskUP::Tools::make_unique <::MaskUP::Component::Vibrator>();
    m_isReset = true;

    return this;
}

VibratorBuilder* VibratorBuilder::setup(const int inPin)
{
    m_pVibrator->setup(inPin, OUTPUT);

    return this;
}

VibratorBuilder* VibratorBuilder::assignSide(const ::MaskUP::Enum::Side inSide)
{
    m_pVibrator->setSide(inSide);

    return this;
}

std::unique_ptr <::MaskUP::Component::Vibrator> VibratorBuilder::build()
{
    if (m_isReset == true)
    {
        m_isReset = false;
        return std::move(m_pVibrator);
    }
    else
    {
        std::cout << "VibratorBuilder error : Cannot build Vibrator.\n";
        return nullptr;
    }
}

}
}
