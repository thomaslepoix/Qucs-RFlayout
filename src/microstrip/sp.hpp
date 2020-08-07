/***************************************************************************
                               sp.hpp
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

#ifndef SP_HPP
#define SP_HPP

#include "element.hpp"

class Sp final : public Element {
private :
	std::string const m_descriptor="s_parameter_simulation";
	std::string m_simtype;
	long double m_fstart;
	long double m_fstop;
	unsigned long m_n;
public :
	Sp(std::string _label,
			std::string _type,
			bool _mirrorx,
			short _r,
			std::string _simtype,
			long double _fstart,
			long double _fstop,
			unsigned long _n);
	~Sp(void)=default;
	std::string getDescriptor(void) override;
	long double getFstart(void) override;
	long double getFstop(void) override;
	std::string getSimtype(void) override;
	unsigned long getN(void) override;
};

#endif // SP_HPP
