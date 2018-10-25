#ifndef PARSER4_H
#define PARSER4_H

#include <iostream>
#include <fstream>
#include <regex>

#include "eqn.h"
#include "pac.h"
#include "mcorn.h"
#include "mcross.h"
#include "mcoupled.h"
#include "mgap.h"
#include "mmbend.h"
#include "mlin.h"
#include "mopen.h"
#include "mrstub.h"
#include "mstep.h"
#include "mtee.h"
#include "mvia.h"

Element** parser4(std::ifstream& f_sch, std::ifstream& f_net, int& nelem);
long double suffix(std::string s_sci, std::string s_eng);

#endif
