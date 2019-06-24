/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:22:49 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/20 15:34:40 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"
#include "Operand.hpp"

creator_function_t OperandFactory::sCreateFunctions[] = {
    &OperandFactory::createInt8,
    &OperandFactory::createInt16,
    &OperandFactory::createInt32,
    &OperandFactory::createFloat,
    &OperandFactory::createDouble,
};

OperandFactory::OperandFactory()
{
}

OperandFactory::~OperandFactory()
{

}

OperandFactory::OperandFactory(OperandFactory const &rhs)
{
    *this = rhs;
}

OperandFactory &OperandFactory::operator=(OperandFactory const & rhs)
{
    if (this != &rhs)
    {
        *this = rhs;
    }
    return *this;
}


IOperand const * OperandFactory::createOperand( EOperandType type, std::string const & value ) const
{
    if (type == EOperandType::MAX)
        throw std::exception();
    creator_function_t fun = sCreateFunctions[static_cast<int>(type)];
    return ((*this).*(fun))(value);
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
    return new Operand<int8_t>(value);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
    return new Operand<int16_t>(value);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
    return new Operand<int32_t>(value);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
    return new Operand<float>(value);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
    return new Operand<double>(value);
}
