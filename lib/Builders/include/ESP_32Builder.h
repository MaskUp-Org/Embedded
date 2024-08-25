/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */


#pragma once

#include "ESP_32.h"
#include "IBuilder.h"
#include "needed.hpp"

#include <memory>


namespace MaskUP
{
namespace Build
{

class ESP_32Builder : public IBuilder <::MaskUP::Component::ESP_32>
{
public:

    ESP_32Builder();

    /* @brief First function to be called when building an object. It must returns raw pointer to the builder itself
    *
    * @return ESP_32Builder *
    */
    virtual ESP_32Builder *reset () override ;

    ESP_32Builder *buildDeviceName (const std::string &inDeviceName);
    //ESP_32Builder *buildLeftVibrator ();
    //ESP_32Builder *buildRightVibrator();
    //ESP_32Builder *buildLeftBCHeadPhone();
    //ESP_32Builder *buildRightBCHeadPhone();
    //ESP_32Builder *buildEmergencyButton();
    //ESP_32Builder *buildServomotor();
    /**
     * @brief Last function called when building an object. It must returns the object created.
     *
     * @return std::unique_ptr<ESP_32>
     */
    virtual std::unique_ptr <::MaskUP::Component::ESP_32> build () override;

private:
    bool m_isReset = false;

    std::unique_ptr <::MaskUP::Component::ESP_32> m_pEsp32;
};

}
}