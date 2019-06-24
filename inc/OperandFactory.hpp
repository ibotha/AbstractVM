/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibotha <ibotha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 15:17:02 by ibotha            #+#    #+#             */
/*   Updated: 2019/06/20 16:36:52 by ibotha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IOperand.hpp"
#include "functional"

class OperandFactory;
typedef IOperand const * (OperandFactory::* creator_function_t)(std::string const &) const;

class OperandFactory {
    private:
        static creator_function_t sCreateFunctions[];

        IOperand const * createInt8( std::string const & value ) const;
        IOperand const * createInt16( std::string const & value ) const;
        IOperand const * createInt32( std::string const & value ) const;
        IOperand const * createFloat( std::string const & value ) const;
        IOperand const * createDouble( std::string const & value ) const;
        
    public:
        OperandFactory();
        ~OperandFactory();
        OperandFactory(OperandFactory const &rhs);
        OperandFactory &operator=(OperandFactory const & rhs);
        
        IOperand const * createOperand(EOperandType type, std::string const & value ) const;
};
