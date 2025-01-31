// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    Venture Line Super Rider driver

***************************************************************************/

#include "emu.h"
#include "suprridr.h"
#include "screen.h"


/*************************************
 *
 *  Tilemap callbacks
 *
 *************************************/

TILE_GET_INFO_MEMBER(suprridr_state::get_tile_info)
{
	uint8_t code = m_bgram[tile_index];
	tileinfo.set(0, code, 0, 0);
}


TILE_GET_INFO_MEMBER(suprridr_state::get_tile_info2)
{
	uint8_t code = m_fgram[tile_index];
	tileinfo.set(1, code, 0, 0);
}



/*************************************
 *
 *  Video startup
 *
 *************************************/

void suprridr_state::video_start()
{
	m_fg_tilemap          = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(suprridr_state::get_tile_info2)), TILEMAP_SCAN_ROWS, 8,8, 32,32);
	m_bg_tilemap          = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(suprridr_state::get_tile_info)),  TILEMAP_SCAN_ROWS, 8,8, 32,32);
	m_bg_tilemap_noscroll = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(suprridr_state::get_tile_info)),  TILEMAP_SCAN_ROWS, 8,8, 32,32);

	m_fg_tilemap->set_transparent_pen(0);

	save_item(NAME(m_flipx));
	save_item(NAME(m_flipy));
}



/*************************************
 *
 *  Color PROM decoding
 *
 *************************************/

void suprridr_state::suprridr_palette(palette_device &palette) const
{
	uint8_t const *const color_prom = memregion("proms")->base();
	for (int i = 0; i < 96; i++)
	{
		int bit0, bit1, bit2;

		// red component
		bit0 = BIT(color_prom[i], 0);
		bit1 = BIT(color_prom[i], 1);
		bit2 = BIT(color_prom[i], 2);
		int const r = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		// green component
		bit0 = BIT(color_prom[i], 3);
		bit1 = BIT(color_prom[i], 4);
		bit2 = BIT(color_prom[i], 5);
		int const g = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		// blue component
		bit0 = BIT(color_prom[i], 6);
		bit1 = BIT(color_prom[i], 7);
		int const b = 0x4f * bit0 + 0xa8 * bit1;

		palette.set_pen_color(i, rgb_t(r, g, b));
	}
}



/*************************************
 *
 *  Screen flip/scroll registers
 *
 *************************************/

void suprridr_state::flipx_w(uint8_t data)
{
	m_flipx = data & 1;
	machine().tilemap().set_flip_all((m_flipx ? TILEMAP_FLIPX : 0) | (m_flipy ? TILEMAP_FLIPY : 0));
}


void suprridr_state::flipy_w(uint8_t data)
{
	m_flipy = data & 1;
	machine().tilemap().set_flip_all((m_flipx ? TILEMAP_FLIPX : 0) | (m_flipy ? TILEMAP_FLIPY : 0));
}


void suprridr_state::fgdisable_w(uint8_t data)
{
	m_fg_tilemap->enable(~data & 1);
}


void suprridr_state::fgscrolly_w(uint8_t data)
{
	m_fg_tilemap->set_scrolly(0, data);
}


void suprridr_state::bgscrolly_w(uint8_t data)
{
	m_bg_tilemap->set_scrolly(0, data);
}


int suprridr_state::is_screen_flipped()
{
	return m_flipx;  /* or is it flipy? */
}



/*************************************
 *
 *  Video RAM writes
 *
 *************************************/

void suprridr_state::bgram_w(offs_t offset, uint8_t data)
{
	m_bgram[offset] = data;
	m_bg_tilemap->mark_tile_dirty(offset);
	m_bg_tilemap_noscroll->mark_tile_dirty(offset);
}


void suprridr_state::fgram_w(offs_t offset, uint8_t data)
{
	m_fgram[offset] = data;
	m_fg_tilemap->mark_tile_dirty(offset);
}



/*************************************
 *
 *  Video refresh
 *
 *************************************/

uint32_t suprridr_state::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	rectangle subclip;
	const rectangle &visarea = screen.visible_area();

	/* render left 4 columns with no scroll */
	subclip = visarea;
	subclip.max_x = subclip.min_x + (m_flipx ? 1*8 : 4*8) - 1;
	subclip &= cliprect;
	m_bg_tilemap_noscroll->draw(screen, bitmap, subclip, 0, 0);

	/* render right 1 column with no scroll */
	subclip = visarea;
	subclip.min_x = subclip.max_x - (m_flipx ? 4*8 : 1*8) + 1;
	subclip &= cliprect;
	m_bg_tilemap_noscroll->draw(screen, bitmap, subclip, 0, 0);

	/* render the middle columns normally */
	subclip = visarea;
	subclip.min_x += m_flipx ? 1*8 : 4*8;
	subclip.max_x -= m_flipx ? 4*8 : 1*8;
	subclip &= cliprect;
	m_bg_tilemap->draw(screen, bitmap, subclip, 0, 0);

	/* render the top layer */
	m_fg_tilemap->draw(screen, bitmap, cliprect, 0, 0);

	/* draw the sprites */
	for (int i = 0; i < 48; i++)
	{
		int code = (m_spriteram[i*4+1] & 0x3f) | ((m_spriteram[i*4+2] >> 1) & 0x40);
		int color = m_spriteram[i*4+2] & 0x7f;
		int fx = m_spriteram[i*4+1] & 0x40;
		int fy = m_spriteram[i*4+1] & 0x80;
		int x = m_spriteram[i*4+3];
		int y = 240 - m_spriteram[i*4+0];

		if (m_flipx)
		{
			fx = !fx;
			x = 240 - x;
		}
		if (m_flipy)
		{
			fy = !fy;
			y = 240 - y;
		}
		m_gfxdecode->gfx(2)->transpen(bitmap,cliprect, code, color, fx, fy, x, y, 0);
	}
	return 0;
}
