/*
 * Created on Aug Tue 05 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "BCHeadPhoneBuilder.h"
#include <iostream>
#include <Arduino.h>


namespace MaskUP
{
namespace Build
{

BCHeadphoneBuilder* BCHeadphoneBuilder::reset()
{
    m_pBCHeadphone = ::MaskUP::Tools::make_unique <::MaskUP::Component::BCHeadphone>();
    m_isReset = true;

    return this;
}

BCHeadphoneBuilder* BCHeadphoneBuilder::assignSide(const ::MaskUP::Enum::Side inSide)
{
    m_pBCHeadphone->setSide(inSide);

    return this;
}

std::unique_ptr <::MaskUP::Component::BCHeadphone> BCHeadphoneBuilder::build()
{
    if (m_isReset == true)
    {
        m_isReset = false;
        return std::move(m_pBCHeadphone);
    }
    else
    {
        std::cout << "BCHeadphoneBuilder error : Cannot build Vibrator.\n";
        return nullptr;
    }
}

}
}
