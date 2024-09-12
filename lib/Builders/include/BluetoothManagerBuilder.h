/*
 * Created on Tue Sep 05 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright (c) 2024 MaskUp
 */

#pragma once

#include "BluetoothManager.h"
#include "IBuilder.h"
#include "needed.hpp"
#include "Enums.h"

#include <memory>

namespace MaskUP
{
namespace Build
{
class BluetoothManagerBuilder : public IBuilder <::MaskUP::Communication::BluetoothManager>
{
public:
    virtual BluetoothManagerBuilder* reset() override;

    BluetoothManagerBuilder* setup(const uint32_t inSerial);
    BluetoothManagerBuilder* buildStateMachine(std::shared_ptr<::MaskUP::StateMachine::StateMachine> inpStateMachine);

    virtual std::unique_ptr <::MaskUP::Communication::BluetoothManager> build() override;

private:

    std::unique_ptr <::MaskUP::Communication::BluetoothManager> m_pBluetoothManager;
    bool m_isReset;


};
}
}