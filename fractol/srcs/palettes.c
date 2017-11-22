

#include "fractol.h"

void	init_greyscale_palette(int *palette)
{
	int		i;
	int		x;

	i = 0;
	while (i < PALETTE_LEN)
	{
		x = (256 / (PALETTE_LEN - 1)) * i;
		palette[i] = (x * 256 * 256) + (x * 256) + x;
		i++;
	}
}

void	init_bluescale_palette(int *palette)
{
	int		i;
	int		b;

	i = 0;
	while (i < PALETTE_LEN)
	{
		b = (200 / (PALETTE_LEN - 1)) * i + 41;
		palette[i] = 0x0c0000 + 0x000600 + b;
		i++;
	}
}

void	init_colorful_palette(int *palette)
{
	int		i;

	i = 0;
	while (i < PALETTE_LEN)
	{
		if (i % 5 == 0)
			palette[i] = 0x0f6677;
		if (i % 5 == 1)
			palette[i] = 0xefe7c9;
		if (i % 5 == 2)
			palette[i] = 0xf27f04;
		if (i % 5 == 3)
			palette[i] = 0xd61908;
		if (i % 5 == 4)
			palette[i] = 0x6d061c;
		i++;
	}
}

void	init_purple_palette(int *palette)
{
	int		i;

	i = 0;
	while (i < PALETTE_LEN)
	{
		if (i % 5 == 0)
			palette[i] = 0x2C0735;
		if (i % 5 == 1)
			palette[i] = 0x4E148C;
		if (i % 5 == 2)
			palette[i] = 0x613DC1;
		if (i % 5 == 3)
			palette[i] = 0x858AE3;
		if (i % 5 == 4)
			palette[i] = 0x97DFFC;
		i++;
	}
}

void	init_greenscale_palette(int *palette)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (i < PALETTE_LEN)
	{
		r = 4;
		g = (200 / (PALETTE_LEN - 1)) * i + 20;
		b = (40 / (PALETTE_LEN - 1)) * i + 12;
		palette[i] = (r * 256 * 256) + (g * 256) + b;
		i++;
	}
}

void	init_gold_palette(int *palette)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	while (i < PALETTE_LEN)
	{
		r = (195 / (PALETTE_LEN - 1)) * i + 40;
		g = (200 / (PALETTE_LEN - 1)) * i + 30;
		b = (100 / (PALETTE_LEN - 1)) * i + 0;
		palette[i] = (r * 256 * 256) + (g * 256) + b;
		i++;
	}
}

void	init_palettes(int palettes[NB_PALETTES][PALETTE_LEN])
{
	init_greyscale_palette(palettes[0]);
	init_bluescale_palette(palettes[1]);
	init_colorful_palette(palettes[2]);
	init_purple_palette(palettes[3]);
	init_greenscale_palette(palettes[4]);
	init_gold_palette(palettes[5]);
}