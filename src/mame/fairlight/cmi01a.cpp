// license:BSD-3-Clause
// copyright-holders:Phil Bennett
/***************************************************************************

    Fairlight CMI-01A Channel Controller Card

***************************************************************************/

#include "emu.h"
#include "cmi01a.h"

#define VERBOSE     (0)
#include "logmacro.h"

const uint8_t cmi01a_device::s_7497_rate_table[64][64] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
	{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
	{1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1},
	{1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1},
	{1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1},
	{1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1},
	{1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1},
	{1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1},
	{1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1},
	{1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
	{0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1},
	{0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1},
	{0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1},
	{0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1},
	{0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1},
	{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
	{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}
};

DEFINE_DEVICE_TYPE(CMI01A_CHANNEL_CARD, cmi01a_device, "cmi_01a", "Fairlight CMI-01A Channel Card")

cmi01a_device::cmi01a_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, CMI01A_CHANNEL_CARD, tag, owner, clock)
	, device_sound_interface(mconfig, *this)
	, m_irq_merger(*this, "cmi01a_irq")
	, m_pia(*this, "cmi01a_pia_%u", 0U)
	, m_ptm(*this, "cmi01a_ptm")
	, m_stream(nullptr)
	, m_sample_timer(nullptr)
	, m_irq_cb(*this)
	, m_current_sample(0), sample16(0), m_mosc(0.0), m_pitch(0), m_octave(0), m_zx_ff_clk(false), m_zx_ff(false), m_zx(false), m_gzx(false)
	, m_run(false), m_not_rstb(true), m_not_load(false), m_not_wpe(true), m_new_addr(false)
	, m_tri(false), m_permit_eload(false), m_not_eload(true), m_bcas_q1_enabled(true)
	, m_env_dir(ENV_DIR_UP), m_env(0), m_env_divider(0), m_ediv_out(false), m_eclk(false), m_env_clk(false)
	, m_wave_addr_lsb(0), m_wave_addr_msb(0), m_upper_wave_addr_load(false), m_wave_addr_msb_clock(true), m_run_load_xor(true), m_delayed_inverted_run_load(false)
	, m_ptm_c1(false), m_ptm_o1(false), m_ptm_o2(false), m_ptm_o3(false)
	, m_vol_latch(0), m_flt_latch(0), m_rp(0), m_ws(0), m_dir(ENV_DIR_UP)
{
}

void cmi01a_device::device_add_mconfig(machine_config &config)
{
	PIA6821(config, m_pia[0], 0); // 6821 C6/7/8/9
	m_pia[0]->readcb1_handler().set(FUNC(cmi01a_device::tri_r));
	m_pia[0]->readpa_handler().set(FUNC(cmi01a_device::ws_dir_r));
	m_pia[0]->writepa_handler().set(FUNC(cmi01a_device::ws_dir_w));
	m_pia[0]->readpb_handler().set(FUNC(cmi01a_device::rp_r));
	m_pia[0]->writepb_handler().set(FUNC(cmi01a_device::rp_w));
	m_pia[0]->ca2_handler().set(FUNC(cmi01a_device::notload_w));
	m_pia[0]->cb2_handler().set(FUNC(cmi01a_device::run_w));
	m_pia[0]->irqa_handler().set(m_irq_merger, FUNC(input_merger_device::in_w<0>));
	m_pia[0]->irqb_handler().set(m_irq_merger, FUNC(input_merger_device::in_w<1>));

	PIA6821(config, m_pia[1], 0); // 6821 D6/7/8/9
	m_pia[1]->readca1_handler().set(FUNC(cmi01a_device::zx_r));
	m_pia[1]->readcb1_handler().set(FUNC(cmi01a_device::eosi_r));
	m_pia[1]->readpa_handler().set(FUNC(cmi01a_device::pitch_octave_r));
	m_pia[1]->writepa_handler().set(FUNC(cmi01a_device::pitch_octave_w));
	m_pia[1]->readpb_handler().set(FUNC(cmi01a_device::pitch_lsb_r));
	m_pia[1]->writepb_handler().set(FUNC(cmi01a_device::pitch_lsb_w));
	m_pia[1]->ca2_handler().set(FUNC(cmi01a_device::permit_eload_w));
	m_pia[1]->cb2_handler().set(FUNC(cmi01a_device::not_wpe_w));
	m_pia[1]->irqa_handler().set(m_irq_merger, FUNC(input_merger_device::in_w<2>));
	m_pia[1]->irqb_handler().set(m_irq_merger, FUNC(input_merger_device::in_w<3>));

	PTM6840(config, m_ptm, DERIVED_CLOCK(1, 1));
	m_ptm->o1_callback().set(FUNC(cmi01a_device::ptm_o1));
	m_ptm->o2_callback().set(FUNC(cmi01a_device::ptm_o2));
	m_ptm->o3_callback().set(FUNC(cmi01a_device::ptm_o3));
	m_ptm->irq_callback().set(m_irq_merger, FUNC(input_merger_device::in_w<4>));

	INPUT_MERGER_ANY_HIGH(config, m_irq_merger).output_handler().set(FUNC(cmi01a_device::cmi01a_irq));
}

void cmi01a_device::device_start()
{
	m_wave_ram = std::make_unique<u8[]>(0x4000);

	m_sample_timer = timer_alloc(FUNC(cmi01a_device::update_sample), this);

	m_stream = stream_alloc(0, 1, 48000);

	m_ptm->set_external_clocks(0, 0, 0);

	save_pointer(NAME(m_wave_ram), 0x4000);
	save_item(NAME(m_current_sample));
	save_item(NAME(sample16));

	save_item(NAME(m_mosc));
	save_item(NAME(m_pitch));
	save_item(NAME(m_octave));

	save_item(NAME(m_zx_ff_clk));
	save_item(NAME(m_zx_ff));
	save_item(NAME(m_zx));
	save_item(NAME(m_gzx));

	save_item(NAME(m_run));
	save_item(NAME(m_not_rstb));
	save_item(NAME(m_not_load));
	save_item(NAME(m_not_wpe));
	save_item(NAME(m_new_addr));

	save_item(NAME(m_tri));
	save_item(NAME(m_permit_eload));
	save_item(NAME(m_not_eload));

	save_item(NAME(m_bcas_q1_enabled));

	save_item(NAME(m_env_dir));
	save_item(NAME(m_env));
	save_item(NAME(m_env_divider));
	save_item(NAME(m_ediv_out));
	save_item(NAME(m_envdiv_toggles));
	save_item(NAME(m_eclk));
	save_item(NAME(m_env_clk));

	save_item(NAME(m_wave_addr_lsb));
	save_item(NAME(m_wave_addr_msb));
	save_item(NAME(m_upper_wave_addr_load));
	save_item(NAME(m_wave_addr_msb_clock));
	save_item(NAME(m_run_load_xor));
	save_item(NAME(m_delayed_inverted_run_load));

	save_item(NAME(m_ptm_c1));
	save_item(NAME(m_ptm_o1));
	save_item(NAME(m_ptm_o2));
	save_item(NAME(m_ptm_o3));

	save_item(NAME(m_vol_latch));
	save_item(NAME(m_flt_latch));
	save_item(NAME(m_rp));
	save_item(NAME(m_ws));
	save_item(NAME(m_dir));
}

void cmi01a_device::device_reset()
{
	m_ptm->set_g1(1);
	m_ptm->set_g2(1);
	m_ptm->set_g3(1);

	m_current_sample = 0x80;

	m_new_addr = false;
	m_vol_latch = 0;
	m_flt_latch = 0;
	m_rp = 0;
	m_ws = 0;
	m_dir = 0;
	m_env = 0;
	m_bcas_q1_enabled = true;
	m_not_rstb = true;

	m_ptm_o1 = 0;
	m_ptm_o2 = 0;
	m_ptm_o3 = 0;

	m_run = false;
	m_gzx = true;
	m_not_wpe = false;
	m_tri = false;
	m_permit_eload = false;

	m_eclk = false;
	m_env_clk = false;
	m_ediv_out = true;
	m_ediv_count = 0;
	m_env_divider = 3;
	std::fill(std::begin(m_envdiv_toggles), std::end(m_envdiv_toggles), false);

	m_pitch = 0;
	m_octave = 0;

	sample16 = (s16)(u16)((((s32)(s8)(m_current_sample ^ 0x80)) * ((s32)m_env) * ((s32)m_vol_latch)) >> 8);

	m_sample_timer->adjust(attotime::never);
}

void cmi01a_device::device_resolve_objects()
{
	m_irq_cb.resolve_safe();
}

void cmi01a_device::sound_stream_update(sound_stream &stream, std::vector<read_stream_view> const &inputs, std::vector<write_stream_view> &outputs)
{
	if (m_run)
	{
		auto &buf = outputs[0];
		//u32 samples = buf.samples();
		//if(samples > 1)
		//	logerror("QUI samples: %d\n", samples);

		for (int sampindex = 0; sampindex < buf.samples(); sampindex++)
		{
			//const s32 sample = (s32)(s8)(m_current_sample ^ 0x80);
			//const s32 env32 = (s32)m_env;
			//const s32 vol32 = (s32)m_vol_latch;
			//const s16 sample16 = (s16)(u16)((sample * env32 * vol32) >> 8);
			//buf.put_int(sampindex, sample16, 32768);
			//sample16 = (s16)(u16)((((s32)(s8)(m_current_sample ^ 0x80)) * ((s32)m_env) * ((s32)m_vol_latch)) >> 8);
			buf.put_int(sampindex, sample16, 32768);
		}
	}
	else
	{
		outputs[0].fill(0);
	}
}

/*TIMER_CALLBACK_MEMBER(cmi01a_device::update_sample)
{
	m_stream->update();
	m_current_sample = m_wave_ram[((m_wave_addr_msb << 7) | m_wave_addr_lsb) & 0x3fff];
	sample16 = (s16)(u16)((((s32)(s8)(m_current_sample ^ 0x80)) * ((s32)m_env) * ((s32)m_vol_latch)) >> 8);
	set_wave_addr_lsb((m_wave_addr_lsb + 1) & 0x7f);
	//logerror("QUI %d %d\n", m_channel, m_current_sample);
}*/

TIMER_CALLBACK_MEMBER(cmi01a_device::update_sample)
{
	m_stream->update();
	m_current_sample = m_wave_ram[((m_wave_addr_msb << 7) | m_wave_addr_lsb) & 0x3fff];

	const u8 wave_addr_lsb = (m_wave_addr_lsb + 1) & 0x7f;
	if (wave_addr_lsb != m_wave_addr_lsb) {

		m_wave_addr_lsb = wave_addr_lsb;
	
		const bool zx = BIT(m_wave_addr_lsb, 6);
		if (zx != m_zx) {
			m_zx = zx;

			const bool wave_addr_msb_clock = !(!m_not_load && m_zx);
			if (wave_addr_msb_clock != m_wave_addr_msb_clock) {
				m_wave_addr_msb_clock = wave_addr_msb_clock;
				if (m_wave_addr_msb_clock) {
					const u8 wave_addr_msb = m_wave_addr_msb + 1;
					if (wave_addr_msb != m_wave_addr_msb) {
						m_wave_addr_msb = wave_addr_msb;
						m_pia[1]->cb1_w(BIT(m_wave_addr_msb, 7));
					}
				}
			}

			m_pia[1]->ca1_w(m_zx);

			const bool zx_ff_clk = !m_zx;
			if (zx_ff_clk != m_zx_ff_clk) {
				m_zx_ff_clk = zx_ff_clk;
				if (m_zx_ff_clk && m_run) {
					if (m_ptm_o1 != m_zx_ff) {
						m_zx_ff = m_ptm_o1;

						if (!m_bcas_q1_enabled) {
							m_bcas_q1_enabled = true;
							if (m_not_load)
								m_ptm->set_ext_clock(0, clock() / 8.0);
							else
								m_ptm->set_ext_clock(0, 0.0);
							m_ptm->set_ext_clock(1, clock() / 4.0);
							m_ptm->set_ext_clock(2, clock() / 4.0);
						}

						// pulse /ZCINT low
						m_pia[0]->ca1_w(1);
						if (!m_gzx) {
							m_gzx = true;
							update_upper_wave_addr_load();
							update_not_eload();
							set_envelope_dir(m_dir);
						}

						// return /ZCINT high
						m_pia[0]->ca1_w(0);
						if (m_gzx) {
							m_gzx = false;
							update_upper_wave_addr_load();
							update_not_eload();
						}

					}
				}
			}
			
			const bool old_ptm_c1 = m_ptm_c1;
			m_ptm_c1 = !m_not_load && zx_ff_clk;
			if (old_ptm_c1 != m_ptm_c1)
				m_ptm->set_c1(m_ptm_c1);

		}

	}

	sample16 = (s16)(u16)((((s32)(s8)(m_current_sample ^ 0x80)) * ((s32)m_env) * ((s32)m_vol_latch)) >> 8);

	//logerror("QUI %d %d\n", m_channel, m_current_sample);
}



int cmi01a_device::notload_r()
{
	return m_not_load;
}

void cmi01a_device::notload_w(int state)
{
	set_not_load(state);
}

void cmi01a_device::pitch_octave_w(u8 data)
{
	//m_pitch &= 0x0ff;
	//m_pitch |= (data & 3) << 8;
	m_pitch = (m_pitch & 0x0ff) | ((data & 3) << 8);
	m_octave = (data >> 2) & 0x0f;
}

u8 cmi01a_device::pitch_octave_r()
{
	return ((m_pitch >> 8) & 3) | (m_octave << 2);
}

void cmi01a_device::pitch_lsb_w(u8 data)
{
	//m_pitch &= 0xf00;
	//m_pitch |= data;
	m_pitch = (m_pitch & 0xf00) | data;
}

u8 cmi01a_device::pitch_lsb_r()
{
	return (u8)m_pitch;
}

void cmi01a_device::rp_w(u8 data)
{
	m_rp = data;
	//m_env_divider = ((m_rp >> 2) & 0x3c) | 0x03;
}

u8 cmi01a_device::rp_r()
{
	return m_rp;
}

void cmi01a_device::ws_dir_w(u8 data)
{
	m_ws = data & 0x7f;
	m_dir = (data >> 7) & 1;
	try_load_upper_wave_addr();
}

u8 cmi01a_device::ws_dir_r()
{
	return m_ws | (m_dir << 7);
}

int cmi01a_device::tri_r()
{
	return m_tri;
}

void cmi01a_device::cmi01a_irq(int state)
{
	m_irq_cb(state ? ASSERT_LINE : CLEAR_LINE);
}

void cmi01a_device::permit_eload_w(int state)
{
	m_permit_eload = state;
	update_not_eload();
}

void cmi01a_device::run_voice()
{
	//double cfreq = ((0x800 | (m_pitch << 1)) * m_mosc) / 4096.0;

	/* Octave register enabled? */
	//if (!BIT(m_octave, 3))
	//	cfreq /= (double)(2 << ((7 ^ m_octave) & 7));

	//cfreq /= 16.0;

	attotime cfreq = attotime::from_hz(
		!BIT(m_octave, 3) ?
			((((0x800 | (m_pitch << 1)) * m_mosc) / 4096.0) / (double)(2 << ((7 ^ m_octave) & 7))) / 16.0 :
			((((0x800 | (m_pitch << 1)) * m_mosc) / 4096.0) / 16.0)
	);
	m_sample_timer->adjust(cfreq, 0, cfreq);
	
	
	
	//logerror("QUI %d %s %f\n", m_channel, cfreq.to_string(), m_mosc);
	//LOG("QUI %d\n", m_channel);
}

void cmi01a_device::run_w(int state)
{
	bool old_run = m_run;
	m_run = state;

	if (old_run != m_run)
		update_rstb_pulser();

	m_stream->update();

	/* RUN */
	if (!old_run && m_run)
	{
		run_voice();

		m_ptm->set_g1(0);
		m_ptm->set_g2(0);
		m_ptm->set_g3(0);
	}

	if (old_run && !m_run)
	{
		m_sample_timer->adjust(attotime::never);
		m_current_sample = 0x80;
		sample16 = (s16)(u16)((((s32)(s8)(m_current_sample ^ 0x80)) * ((s32)m_env) * ((s32)m_vol_latch)) >> 8);

		m_ptm->set_g1(1);
		m_ptm->set_g2(1);
		m_ptm->set_g3(1);

		set_zx_flipflop_state(false);
	}
}

inline void cmi01a_device::update_rstb_pulser()
{
	set_run_load_xor(m_run != !m_not_load);
}

void cmi01a_device::set_run_load_xor(const bool run_load_xor)
{
	if (run_load_xor == m_run_load_xor)
		return;

	m_run_load_xor = run_load_xor;
	m_new_addr = true;

	// pulse /RSTB low
	m_not_rstb = false;
	set_gzx(true);
	set_wave_addr_lsb(0);
	set_wave_addr_msb(0x80 | m_ws);

	// return /RSTB high
	m_not_rstb = true;
	set_gzx(false);
}

void cmi01a_device::update_bcas_q1_enable()
{
	const bool old_enable = m_bcas_q1_enabled;
	m_bcas_q1_enabled = (m_zx_ff == m_ptm_o1);

	if (!old_enable && m_bcas_q1_enabled)
	{
		if (m_not_load)
			m_ptm->set_ext_clock(0, clock() / 8.0);
		else
			m_ptm->set_ext_clock(0, 0.0);
		m_ptm->set_ext_clock(1, clock() / 4.0);
		m_ptm->set_ext_clock(2, clock() / 4.0);
	}
	else if (old_enable && !m_bcas_q1_enabled)
	{
		m_ptm->set_ext_clock(0, 0.0);
		m_ptm->set_ext_clock(1, 0.0);
		m_ptm->set_ext_clock(2, 0.0);
	}
}

void cmi01a_device::set_zx_flipflop_clock(const bool zx_ff_clk)
{
	if (zx_ff_clk == m_zx_ff_clk)
		return;

	m_zx_ff_clk = zx_ff_clk;

	if (m_zx_ff_clk && m_run)
		set_zx_flipflop_state(m_ptm_o1);
}

void cmi01a_device::set_zx_flipflop_state(const bool zx_ff)
{
	if (zx_ff == m_zx_ff)
		return;

	m_zx_ff = zx_ff;

	update_bcas_q1_enable();
	pulse_zcint();
}

inline void cmi01a_device::pulse_zcint()
{
	// pulse /ZCINT low
	m_pia[0]->ca1_w(1);
	set_gzx(true);

	// return /ZCINT high
	m_pia[0]->ca1_w(0);
	set_gzx(false);
}

void cmi01a_device::set_not_load(const bool not_load)
{
	if (not_load == m_not_load)
		return;

	m_not_load = not_load;
	update_rstb_pulser();
	update_ptm_c1();
}

void cmi01a_device::set_gzx(const bool gzx)
{
	if (gzx == m_gzx)
		return;

	m_gzx = gzx;
	update_upper_wave_addr_load();
	update_not_eload();
	if (m_gzx)
		set_envelope_dir(m_dir);
}

inline void cmi01a_device::update_not_eload()
{
	set_not_eload(!(m_permit_eload && m_gzx));
}

void cmi01a_device::set_not_eload(const bool not_eload)
{
	if (not_eload == m_not_eload)
		return;

	m_not_eload = not_eload;
	try_load_envelope();
}

inline void cmi01a_device::try_load_envelope()
{
	if (m_not_eload)
		return;

	set_envelope(m_rp);
}

void cmi01a_device::set_envelope(const u8 env)
{
	if (env == m_env)
		return;

	m_env = env;
	update_envelope_divider();
	update_envelope_tri();
}

void cmi01a_device::update_envelope_divider()
{
	if (m_env_dir == ENV_DIR_UP)
		m_env_divider = (~m_env >> 2) & 0x3c;
	else
		m_env_divider = (m_env >> 2) & 0x3c;
	m_env_divider |= 0x03;
}

void cmi01a_device::set_envelope_dir(const int env_dir)
{
	if (env_dir == m_env_dir)
		return;

	m_env_dir = env_dir;
	update_envelope_divider();
	update_envelope_tri();
}

void cmi01a_device::update_envelope_clock()
{
	const bool old_eclk = m_eclk;
	m_eclk = (m_ptm_o2 && m_zx_ff) || (m_ptm_o3 && !m_zx_ff);

	if (old_eclk == m_eclk)
		return;

	tick_ediv();

	const bool old_env_clk = m_env_clk;
	m_env_clk = ((m_not_load && m_eclk) || (!m_not_load && m_ediv_out));

	if (!old_env_clk && m_env_clk)
		clock_envelope();
}

void cmi01a_device::clock_envelope()
{
	if (m_tri)
		return;

	m_stream->update();
	if (m_env_dir == ENV_DIR_DOWN)
		m_env--;
	else
		m_env++;
	update_envelope_divider();
	update_envelope_tri();
}

void cmi01a_device::tick_ediv()
{
	//if (m_channel == 5) logerror("CH%d ticking ediv, rate: %02x\n", m_channel, m_ediv_rate);
	m_ediv_out = s_7497_rate_table[m_env_divider][m_ediv_count];
	m_ediv_count = (m_ediv_count + 1) & 0x3f;
}


/*void cmi01a_device::tick_ediv()
{
	const bool envdiv_enable_a = m_eclk;
	const bool envdiv_enable_b = envdiv_enable_a && m_envdiv_toggles[0];
	const bool envdiv_enable_c = envdiv_enable_b && m_envdiv_toggles[1];
	const bool envdiv_enable_d = envdiv_enable_c && m_envdiv_toggles[2];
	const bool envdiv_enable_e = envdiv_enable_d && m_envdiv_toggles[3];
	const bool envdiv_enable_f = envdiv_enable_e && m_envdiv_toggles[4];

	if (envdiv_enable_f)
		m_envdiv_toggles[5] = !m_envdiv_toggles[5];
	if (envdiv_enable_e)
		m_envdiv_toggles[4] = !m_envdiv_toggles[4];
	if (envdiv_enable_d)
		m_envdiv_toggles[3] = !m_envdiv_toggles[3];
	if (envdiv_enable_c)
		m_envdiv_toggles[2] = !m_envdiv_toggles[2];
	if (envdiv_enable_b)
		m_envdiv_toggles[1] = !m_envdiv_toggles[1];
	if (envdiv_enable_a)
		m_envdiv_toggles[0] = !m_envdiv_toggles[0];

	const bool envdiv_out_f = m_eclk && BIT(m_env_divider, 5) && !m_envdiv_toggles[0];
	const bool envdiv_out_e = m_eclk && BIT(m_env_divider, 4) && m_envdiv_toggles[0] && !m_envdiv_toggles[1];
	const bool envdiv_out_d = m_eclk && BIT(m_env_divider, 3) && m_envdiv_toggles[0] && m_envdiv_toggles[1] && !m_envdiv_toggles[2];
	const bool envdiv_out_c = m_eclk && BIT(m_env_divider, 2) && m_envdiv_toggles[0] && m_envdiv_toggles[1] && m_envdiv_toggles[2] && !m_envdiv_toggles[3];
	const bool envdiv_out_b = m_eclk && BIT(m_env_divider, 1) && m_envdiv_toggles[0] && m_envdiv_toggles[1] && m_envdiv_toggles[2] && m_envdiv_toggles[3] && !m_envdiv_toggles[4];
	const bool envdiv_out_a = m_eclk && BIT(m_env_divider, 0) && m_envdiv_toggles[0] && m_envdiv_toggles[1] && m_envdiv_toggles[2] && m_envdiv_toggles[3] && m_envdiv_toggles[4] && !m_envdiv_toggles[5];

	m_ediv_out = !(envdiv_out_f || envdiv_out_e || envdiv_out_d || envdiv_out_c || envdiv_out_b || envdiv_out_a);
}*/

void cmi01a_device::update_envelope_tri()
{
	if (m_env_dir == ENV_DIR_DOWN)
		m_tri = (m_env == 0x00);
	else
		m_tri = (m_env == 0xff);

	m_pia[0]->cb1_w(m_tri);
}

void cmi01a_device::not_wpe_w(int state)
{
	if (state == m_not_wpe)
		return;

	m_not_wpe = state;
	update_upper_wave_addr_load();
}

inline void cmi01a_device::update_upper_wave_addr_load()
{
	const bool c10_and_out = (!m_not_wpe && m_gzx);
	set_upper_wave_addr_load(c10_and_out || !m_not_rstb);
}

inline void cmi01a_device::set_upper_wave_addr_load(const bool upper_wave_addr_load)
{
	if (upper_wave_addr_load == m_upper_wave_addr_load)
		return;

	m_upper_wave_addr_load = upper_wave_addr_load;
	try_load_upper_wave_addr();
}

inline void cmi01a_device::try_load_upper_wave_addr()
{
	if (!m_upper_wave_addr_load)
		return;

	set_wave_addr_msb(0x80 | m_ws);
}

void cmi01a_device::set_wave_addr_lsb(const u8 wave_addr_lsb)
{
	if (wave_addr_lsb == m_wave_addr_lsb)
		return;

	m_wave_addr_lsb = wave_addr_lsb;
	set_zx(BIT(m_wave_addr_lsb, 6));
}

void cmi01a_device::set_wave_addr_msb(const u8 wave_addr_msb)
{
	if (wave_addr_msb == m_wave_addr_msb)
		return;

	m_wave_addr_msb = wave_addr_msb;
	m_pia[1]->cb1_w(BIT(m_wave_addr_msb, 7));
}

void cmi01a_device::set_wave_addr_msb_clock(const bool wave_addr_msb_clock)
{
	if (wave_addr_msb_clock == m_wave_addr_msb_clock)
		return;

	m_wave_addr_msb_clock = wave_addr_msb_clock;
	if (m_wave_addr_msb_clock)
		set_wave_addr_msb(m_wave_addr_msb + 1);
}

void cmi01a_device::set_zx(const bool zx)
{
	if (zx == m_zx)
		return;

	m_zx = zx;
	set_wave_addr_msb_clock(!(!m_not_load && m_zx));
	m_pia[1]->ca1_w(m_zx);
	set_zx_flipflop_clock(!m_zx);
	update_ptm_c1();
}

void cmi01a_device::update_ptm_c1()
{
	const bool old_ptm_c1 = m_ptm_c1;
	m_ptm_c1 = !m_not_load && !m_zx;
	if (old_ptm_c1 != m_ptm_c1)
		m_ptm->set_c1(m_ptm_c1);
}

void cmi01a_device::ptm_o1(int state)
{
	m_ptm_o1 = state;
	update_bcas_q1_enable();
}

void cmi01a_device::ptm_o2(int state)
{
	m_ptm_o2 = state;
	update_envelope_clock();
}

void cmi01a_device::ptm_o3(int state)
{
	m_ptm_o3 = state;
	update_envelope_clock();
}

int cmi01a_device::eosi_r()
{
	return BIT(m_wave_addr_msb, 7);
}

int cmi01a_device::zx_r()
{
	return BIT(m_wave_addr_lsb, 6);
}

void cmi01a_device::write(offs_t offset, u8 data)
{
	switch (offset)
	{
		case 0x0:
			if (m_new_addr)
				m_new_addr = false;

			m_wave_ram[((m_wave_addr_msb << 7) | m_wave_addr_lsb) & 0x3fff] = data;
			set_wave_addr_lsb((m_wave_addr_lsb + 1) & 0x7f);
			break;

		case 0x3:
			set_envelope_dir(ENV_DIR_DOWN);
			break;

		case 0x4:
			set_envelope_dir(ENV_DIR_UP);
			break;

		case 0x5:
			m_vol_latch = data;
			break;

		case 0x6:
			m_flt_latch = data;
			break;

		case 0x8: case 0x9: case 0xa: case 0xb:
			m_pia[0]->write(offset & 3, data);
			break;

		case 0xc: case 0xd: case 0xe: case 0xf:
			m_pia[1]->write((BIT(offset, 0) << 1) | BIT(offset, 1), data);
			break;

		case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
		{
			/* PTM addressing is a little funky */
			int a0 = offset & 1;
			int a1 = (m_ptm_o1 && BIT(offset, 3)) || (!BIT(offset, 3) && BIT(offset, 2));
			int a2 = BIT(offset, 1);

			m_ptm->write((a2 << 2) | (a1 << 1) | a0, data);
			break;
		}

		default:
			LOG("%s: Unknown channel card write to E0%02X = %02X\n", machine().describe_context(), offset, data);
			break;
	}
}

u8 cmi01a_device::read(offs_t offset)
{
	if (machine().side_effects_disabled())
		return 0;

	u8 data = 0;

	switch (offset)
	{
		case 0x0:
			data = m_wave_ram[((m_wave_addr_msb << 7) | m_wave_addr_lsb) & 0x3fff];
			if (!m_new_addr)
			{
				set_wave_addr_lsb((m_wave_addr_lsb + 1) & 0x7f);
			}
			m_new_addr = false;
			break;

		case 0x3:
			set_envelope_dir(ENV_DIR_DOWN);
			break;

		case 0x4:
			set_envelope_dir(ENV_DIR_UP);
			break;

		case 0x5:
			data = 0xff;
			break;

		case 0x8: case 0x9: case 0xa: case 0xb:
			data = m_pia[0]->read(offset & 3);
			break;

		case 0xc: case 0xd: case 0xe: case 0xf:
			data = m_pia[1]->read((BIT(offset, 0) << 1) | BIT(offset, 1));
			break;

		case 0x10: case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16: case 0x17:
		{
			int a0 = offset & 1;
			int a1 = (m_ptm_o1 && BIT(offset, 3)) || (!BIT(offset, 3) && BIT(offset, 2));
			int a2 = BIT(offset, 1);

			data = m_ptm->read((a2 << 2) | (a1 << 1) | a0);

			break;
		}

		default:
			LOG("%s: Unknown channel card %d read from E0%02X\n", machine().describe_context(), m_channel, offset);
			break;
	}

	return data;
}
