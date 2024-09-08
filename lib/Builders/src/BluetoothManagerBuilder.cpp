/*
 * Created on Aug Tue 05 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#include "BluetoothManagerBuilder.h"
#include "FileReader.h"

#include <iostream>
#include <Arduino.h>

namespace MaskUP
{
namespace Build
{

BluetoothManagerBuilder* BluetoothManagerBuilder::reset()
{
    m_pBluetoothManager = ::MaskUP::Tools::make_unique <::MaskUP::Communication::BluetoothManager>();
    m_isReset = true;

    return this;
}

BluetoothManagerBuilder* BluetoothManagerBuilder::setup(const uint32_t inSerial)
{
    String deviceName = ::MaskUP::Tools::getDeviceInformation("DeviceName");
    m_pBluetoothManager->setup(inSerial, deviceName);
    return this;
}

std::unique_ptr <::MaskUP::Communication::BluetoothManager> BluetoothManagerBuilder::build()
{
    if (m_isReset == true)
    {
        m_isReset = false;
        return std::move(m_pBluetoothManager);
    }
    else
    {
        std::cout << "BluetoothManagerBuilder error : Cannot build BluetoothManager.\n";
        return nullptr;
    }
    return nullptr;
}

}
}
