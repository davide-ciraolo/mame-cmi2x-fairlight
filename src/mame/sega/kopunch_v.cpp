// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria
/*************************************************************************

  Sega KO Punch

  Functions to emulate the video hardware of the machine.

*************************************************************************/

#include "emu.h"
#include "kopunch.h"


void kopunch_state::kopunch_palette(palette_device &palette) const
{
	const uint8_t *color_prom = memregion("proms")->base();

	color_prom += 24; // first 24 colors are black

	for (int i = 0; i < palette.entries(); i++)
	{
		int bit0, bit1, bit2;

		// red component
		bit0 = BIT(*color_prom, 0);
		bit1 = BIT(*color_prom, 1);
		bit2 = BIT(*color_prom, 2);
		int const r = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
		// green component
		bit0 = BIT(*color_prom, 3);
		bit1 = BIT(*color_prom, 4);
		bit2 = BIT(*color_prom, 5);
		int const g = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;
		// blue component
		bit0 = 0;
		bit1 = BIT(*color_prom, 6);
		bit2 = BIT(*color_prom, 7);
		int const b = 0x21 * bit0 + 0x47 * bit1 + 0x97 * bit2;

		palette.set_pen_color(i, rgb_t(r, g, b));
		color_prom++;
	}
}

void kopunch_state::vram_fg_w(offs_t offset, uint8_t data)
{
	m_vram_fg[offset] = data;
	m_fg_tilemap->mark_tile_dirty(offset);
}

void kopunch_state::vram_bg_w(offs_t offset, uint8_t data)
{
	m_vram_bg[offset] = data;
	m_bg_tilemap->mark_tile_dirty(offset);
}

void kopunch_state::scroll_x_w(uint8_t data)
{
	m_scrollx = data;
	m_bg_tilemap->set_scrollx(0, data);
}

void kopunch_state::scroll_y_w(uint8_t data)
{
	m_bg_tilemap->set_scrolly(0, data);
}

void kopunch_state::gfxbank_w(uint8_t data)
{
	// d0-d2: bg gfx bank
	if (m_gfxbank != (data & 0x07))
	{
		m_gfxbank = data & 0x07;
		m_bg_tilemap->mark_all_dirty();
	}

	// d3: flip y, other bits: N/C
	m_bg_tilemap->set_flip((data & 0x08) ? TILEMAP_FLIPY : 0);
}

TILE_GET_INFO_MEMBER(kopunch_state::get_fg_tile_info)
{
	int code = m_vram_fg[tile_index];

	tileinfo.set(0, code, 0, 0);
}

TILE_GET_INFO_MEMBER(kopunch_state::get_bg_tile_info)
{
	// note: highest bit is unused
	int code = (m_vram_bg[tile_index] & 0x7f) | m_gfxbank << 7;

	tileinfo.set(1, code, 0, 0);
}

void kopunch_state::video_start()
{
	m_fg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(kopunch_state::get_fg_tile_info)), TILEMAP_SCAN_ROWS,  8,  8, 32, 32);
	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(kopunch_state::get_bg_tile_info)), TILEMAP_SCAN_ROWS, 16, 16, 16, 16);

	m_fg_tilemap->set_transparent_pen(0);
}

uint32_t kopunch_state::screen_update_kopunch(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	bitmap.fill(0, cliprect);

	// background does not wrap around horizontally
	rectangle bg_clip = cliprect;
	bg_clip.max_x = m_scrollx ^ 0xff;

	m_bg_tilemap->draw(screen, bitmap, bg_clip, 0, 0);
	m_fg_tilemap->draw(screen, bitmap, cliprect, 0, 0);

	return 0;
}
