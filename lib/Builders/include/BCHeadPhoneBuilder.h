/*
 * Created on Sat Aug 17 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include "BCHeadphone.h"
#include "IBuilder.h"
#include "needed.hpp"
#include "Side.hpp"
#include <memory>

namespace MaskUP
{
namespace Build
{
class BCHeadphoneBuilder : public IBuilder <::MaskUP::Component::BCHeadphone>
{
public:
    virtual BCHeadphoneBuilder* reset() override;
    BCHeadphoneBuilder* assignSide(const ::MaskUP::Enum::Side inSide);

    virtual std::unique_ptr <::MaskUP::Component::BCHeadphone> build() override;

private:
    std::unique_ptr <::MaskUP::Component::BCHeadphone> m_pBCHeadphone;
    bool m_isReset;

};
}
}