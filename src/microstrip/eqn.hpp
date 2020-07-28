/***************************************************************************
                               eqn.hpp
                             ------------------
    begin                : Thu Oct 25 2018
    copyright            : (C) 2018 by Thomas Lepoix
    email                : thomas.lepoix@protonmail.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef EQN_HPP
#define EQN_HPP

#include "element.hpp"

class Eqn final : public Element {
private :
	std::string const m_descriptor="equation";
public :
	Eqn(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r);
	~Eqn();
	std::string getDescriptor(void) override;
};

#endif // EQN_HPP
