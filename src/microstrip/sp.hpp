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

//******************************************************************************
class Sp final : public Element {
private :
	static std::string const m_descriptor;
	std::string const m_simtype;
	long double const m_fstart;
	long double const m_fstop;
	unsigned long const m_n;
public :
	Sp(std::string const _label,
			std::string const _type,
			bool const _mirrorx,
			short const _r,
			std::string const _simtype,
			long double const _fstart,
			long double const _fstop,
			unsigned long const _n);
	~Sp(void)=default;
	std::string getDescriptor(void) const override;
	long double getFstart(void) const override;
	long double getFstop(void) const override;
	std::string getSimtype(void) const override;
	unsigned long getN(void) const override;
};

#endif // SP_HPP
