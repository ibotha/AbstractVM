/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:04:50 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/21 14:08:30 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "EOperandType.hpp"

class IOperand {
public:
    virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
    virtual EOperandType getType( void ) const = 0; // Type of the instance
    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
    virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
    virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
    virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    virtual bool operator==( IOperand const & rhs ) const = 0; // equality
    virtual std::string toString( void ) const = 0; // String representation of the instance
    virtual ~IOperand( void ) {}
};