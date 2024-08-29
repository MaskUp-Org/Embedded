/*
 * Created on Sat Feb 25 2024
 * By SEGHAIER Mohamed-Ali
 *
 * Copyright MaskUP (c) 2024
 */

#pragma once

#include <memory>

namespace MaskUP
{
namespace Build
{

template <typename T>
class IBuilder
{

public:
    /**
     * @brief First function to be called when building an object. It must returns raw pointer to the builder itself
     *
     * @return IBuilder * : The builder itself.
     */
    virtual IBuilder *reset () = 0 ;

    /**
     * @brief Last function called when building an object. It must returns the object created.
     *
     * @return std::unique_ptr<T> Object created
     */
    virtual std::unique_ptr<T> build() = 0;
};

}
}