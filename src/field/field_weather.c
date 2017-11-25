#include "global.h"
#include "blend_palette.h"
#include "field_map_obj.h"
#include "field_weather.h"
#include "palette.h"
#include "rng.h"
#include "script.h"
#include "songs.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "trig.h"
#include "ewram.h"

#define MACRO1(a) ((((a) >> 1) & 0xF) | (((a) >> 2) & 0xF0) | (((a) >> 3) & 0xF00))

struct RGBColor
{
    u16 r:5;
    u16 g:5;
    u16 b:5;
};

struct WeatherPaletteData
{
    u16 data[0][0x1000];  // unknown length
};

struct WeatherCallbacks
{
    void (*func0)(void);
    void (*func1)(void);
    void (*func2)(void);
    u8 (*func3)(void);
};

extern struct Weather gWeather;
extern u8 gUnknown_0202FF38[];
extern u16 gUnknown_0202FF58;
IWRAM_DATA const u8 *gUnknown_030006DC;

const u8 DroughtPaletteData_0[] = INCBIN_U8("graphics/weather/drought0.bin.lz");
const u8 DroughtPaletteData_1[] = INCBIN_U8("graphics/weather/drought1.bin.lz");
const u8 DroughtPaletteData_2[] = INCBIN_U8("graphics/weather/drought2.bin.lz");
const u8 DroughtPaletteData_3[] = INCBIN_U8("graphics/weather/drought3.bin.lz");
const u8 DroughtPaletteData_4[] = INCBIN_U8("graphics/weather/drought4.bin.lz");
const u8 DroughtPaletteData_5[] = INCBIN_U8("graphics/weather/drought5.bin.lz");
extern u8 (*gUnknown_0202FC48)[32];
extern u8 gUnknown_0202F9E8[32];

const u8 *const gUnknown_08396FA8[] =
{
    DroughtPaletteData_0,
    DroughtPaletteData_1,
    DroughtPaletteData_2,
    DroughtPaletteData_3,
    DroughtPaletteData_4,
    DroughtPaletteData_5,
    gSharedMem,
};

// This is a pointer to gWeather. All code in this file accesses gWeather directly,
// while code in other field weather files accesses gWeather through this pointer.
// This is likely the result of compiler optimization, since using the pointer in
// this file produces the same result as accessing gWeather directly.
struct Weather *const gWeatherPtr = &gWeather;

void sub_807CAE8(void);
void nullsub_38(void);
u8 sub_807CB0C(void);
void sub_807DE78(void);
void sub_807DEF4(void);
void sub_807DEC4(void);
u8 sub_807DF54(void);
void sub_807DF9C(void);
void nullsub_55(void);
void sub_807DFC0(void);
u8 sub_807DFD0(void);
void LightRain_InitVars(void);
void sub_807E400(void);
void sub_807E3D0(void);
u8 sub_807E460(void);
void Snow_InitVars(void);
void snowflakes_progress2(void);
void sub_807EA18(void);
u8 sub_807EAC0(void);
void sub_807EE80(void);
void sub_807EFC0(void);
void sub_807EEF4(void);
u8 sub_807F34C(void);
void sub_807F49C(void);
void sub_807F52C(void);
void sub_807F4FC(void);
u8 sub_807F5EC(void);
void sub_807F7F8(void);
void sub_807F888(void);
void sub_807F858(void);
u8 sub_807F934(void);
void sub_807FE9C(void);
void sub_807FF4C(void);
void sub_807FF1C(void);
u8 sub_807FFC8(void);
void sub_807FB24(void);
void sub_807FBD8(void);
void sub_807FBA8(void);
u8 sub_807FC3C(void);
void sub_807F49C(void);
void sub_807F52C(void);
void sub_807F4FC(void);
u8 sub_807F5EC(void);
void sub_8080430(void);
void nullsub_56(void);
void sub_8080460(void);
u8 sub_8080470(void);
void sub_807E110(void);
void sub_807E174(void);
void sub_807E144(void);
u8 sub_807E258(void);
void sub_807EF24(void);
void sub_807EFC0(void);
void sub_807EF90(void);
u8 sub_807F34C(void);
void sub_8080474(void);
void sub_80804F8(void);
void sub_80804C8(void);
u8 sub_808056C(void);

const struct WeatherCallbacks gUnknown_08396FC8[] =
{
    {sub_807CAE8, nullsub_38, sub_807CAE8, sub_807CB0C},
    {sub_807DE78, sub_807DEF4, sub_807DEC4, sub_807DF54},
    {sub_807DF9C, nullsub_55, sub_807DFC0, sub_807DFD0},
    {LightRain_InitVars, sub_807E400, sub_807E3D0, sub_807E460},           // light rain
    {Snow_InitVars, snowflakes_progress2, sub_807EA18, sub_807EAC0},  // snow
    {sub_807EE80, sub_807EFC0, sub_807EEF4, sub_807F34C},
    {sub_807F49C, sub_807F52C, sub_807F4FC, sub_807F5EC},
    {sub_807F7F8, sub_807F888, sub_807F858, sub_807F934},
    {sub_807FE9C, sub_807FF4C, sub_807FF1C, sub_807FFC8},
    {sub_807FB24, sub_807FBD8, sub_807FBA8, sub_807FC3C},
    {sub_807F49C, sub_807F52C, sub_807F4FC, sub_807F5EC},
    {sub_8080430, nullsub_56, sub_8080460, sub_8080470},
    {sub_807E110, sub_807E174, sub_807E144, sub_807E258},
    {sub_807EF24, sub_807EFC0, sub_807EF90, sub_807F34C},
    {sub_8080474, sub_80804F8, sub_80804C8, sub_808056C},
};

void (*const gUnknown_083970B8[])(void) =
{
    sub_807CC24,
    sub_807CCAC,
    nullsub_39,
    nullsub_39,
};

const u8 gUnknown_083970C8[] =
{
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    0,
    0,
    2,
    1,
    2,
    2,
    2,
    2,
    1,
    1,
    1,
    1,
    2,
    1,
    1,
    1,
    1,
    1,
};

const u16 gUnknown_083970E8[] = INCBIN_U16("graphics/weather/0.gbapal");

void sub_807C828(void)
{
    u8 index;
    if (!FuncIsActiveTask(sub_807CA34))
    {
        index = AllocSpritePalette(0x1200);
        CpuCopy32(gUnknown_083970E8, &gPlttBufferUnfaded[0x100 + index * 16], 32);
        sub_807CB10();
        gWeatherPtr->unknown_6D5 = index;
        gWeatherPtr->unknown_6D4 = AllocSpritePalette(0x1201);
        gWeatherPtr->unknown_6DA = 0;
        gWeatherPtr->unknown_6D8 = 0;
        gWeatherPtr->unknown_6DE = 0;
        gWeatherPtr->unknown_6E4 = 0;
        gWeatherPtr->unknown_700 = 0;
        gWeatherPtr->unknown_6FB = 0;
        gWeatherPtr->unknown_724 = 0;
        gWeatherPtr->unknown_716 = 0;
        gWeatherPtr->unknown_717 = 0;
        gWeatherPtr->unknown_72E = 0;
        gWeatherPtr->unknown_6FA = 0;
        sub_807DB64(16, 0);
        gWeatherPtr->currWeather = 0;
        gWeatherPtr->unknown_6C6 = 3;
        gWeatherPtr->unknown_6C8 = 0;
        gWeatherPtr->unknown_6D3 = 1;
        gWeatherPtr->unknown_6C9 = CreateTask(sub_807C9E4, 80);
    }
}

void DoWeatherEffect(u8 effect)
{
    if (effect != WEATHER_RAIN_LIGHT && effect != WEATHER_RAIN_MED && effect != WEATHER_RAIN_HEAVY)
    {
        PlayRainSoundEffect();
    }
    if (gWeatherPtr->unknown_6D1 != effect && gWeatherPtr->currWeather == effect)
    {
        gUnknown_08396FC8[effect].func0();
    }
    gWeatherPtr->unknown_6D3 = 0;
    gWeatherPtr->unknown_6D1 = effect;
    gWeatherPtr->unknown_6CE = 0;
}

void sub_807C988(u8 effect)
{
    PlayRainSoundEffect();
    gWeatherPtr->currWeather = effect;
    gWeatherPtr->unknown_6D1 = effect;
}

void sub_807C9B4(u8 effect)
{
    PlayRainSoundEffect();
    gWeatherPtr->currWeather = effect;
    gWeatherPtr->unknown_6D1 = effect;
    gWeatherPtr->unknown_6C8 = 1;
}

void sub_807C9E4(u8 taskId)
{
    if (gWeatherPtr->unknown_6C8)
    {
        gUnknown_08396FC8[gWeatherPtr->currWeather].func2();
        gTasks[taskId].func = sub_807CA34;
    }
}

void sub_807CA34(u8 task)
{
    u8 v1;
    if (gWeatherPtr->currWeather != gWeatherPtr->unknown_6D1)
    {
        v1 = gUnknown_08396FC8[gWeatherPtr->currWeather].func3();
        if (!v1)
        {
            gUnknown_08396FC8[gWeatherPtr->unknown_6D1].func0();
            gWeatherPtr->unknown_6C3 = 0; // compiler reuses v1
            gWeatherPtr->unknown_6C6 = 0; // compiler reuses v1
            gWeatherPtr->currWeather = gWeatherPtr->unknown_6D1;
            gWeatherPtr->unknown_6D3 = 1;
        }
    }
    else
    {
        gUnknown_08396FC8[gWeatherPtr->currWeather].func1();
    }
    gUnknown_083970B8[gWeatherPtr->unknown_6C6]();
}

void sub_807CAE8(void)
{
    gWeatherPtr->unknown_6C1 = 0;
    gWeatherPtr->unknown_6C2 = 0;
}

void nullsub_38(void)
{
}

u8 sub_807CB0C(void)
{
    return 0;
}

void sub_807CB10(void)
{
    u16 v0;
    u8 (*v1)[32];
    u16 v2;
    u16 v4;
    u16 v5;
    u16 v6;
    u16 v9;
    u32 v10;
    u16 v11;
    s16 dunno;

    gUnknown_030006DC = gUnknown_083970C8;
    for (v0 = 0; v0 <= 1; v0++)
    {
        if (v0 == 0)
            v1 = gWeatherPtr->unknown_200;
        else
            v1 = gWeatherPtr->unk460;

        for (v2 = 0; (u16)v2 <= 0x1f; v2++)
        {
            v4 = v2 << 8;
            if (v0 == 0)
                v5 = (v2 << 8) / 16;
            else
                v5 = 0;
            for (v6 = 0; v6 <= 2; v6++)
            {
                v4 = (v4 - v5);
                v1[v6][v2] = v4 >> 8;
            }
            v9 = v4;
            v10 = 0x1f00 - v4;
            if ((0x1f00 - v4) < 0)
            {
                v10 += 0xf;
            }
            v11 = v10 >> 4;
            if (v2 <= 0xb)
            {
                for (; v6 <= 0x12; v6++)
                {
                    v4 += v11;
                    dunno = v4 - v9;
                    if (dunno > 0)
                    {
                        v4 -= (dunno + ((u16)dunno >> 15)) >> 1;
                    }
                    v1[v6][v2] = v4 >> 8;
                    if (v1[v6][v2] > 0x1f)
                    {
                        v1[v6][v2] = 0x1f;
                    }
                }
            }
            else
            {
                for (; v6 <= 0x12; v6++)
                {
                    v4 += v11;
                    v1[v6][v2] = v4 >> 8;
                    if (v1[v6][v2] > 0x1f)
                    {
                        v1[v6][v2] = 0x1f;
                    }
                }
            }
        }
    }
}

void sub_807CC24(void)
{
    if (gWeatherPtr->unknown_6C0 == gWeatherPtr->unknown_6C1)
    {
        gWeatherPtr->unknown_6C6 = 3;
    }
    else
    {
        if (++gWeatherPtr->unknown_6C3 >= gWeatherPtr->unknown_6C2)
        {
            gWeatherPtr->unknown_6C3 = 0;
            if (gWeatherPtr->unknown_6C0 < gWeatherPtr->unknown_6C1)
                gWeatherPtr->unknown_6C0++;
            else
                gWeatherPtr->unknown_6C0--;
            sub_807CEBC(0, 0x20, gWeatherPtr->unknown_6C0);
        }
    }
}

void sub_807CCAC(void)
{
    if (++gWeatherPtr->unknown_6CB > 1)
        gWeatherPtr->unknown_6CA = 0;
    switch (gWeatherPtr->currWeather)
    {
    case WEATHER_RAIN_LIGHT:
    case WEATHER_RAIN_MED:
    case WEATHER_RAIN_HEAVY:
    case WEATHER_SNOW:
    case 11:
        if (sub_807CDC4() == 0)
        {
            gWeatherPtr->unknown_6C0 = 3;
            gWeatherPtr->unknown_6C6 = 3;
        }
        break;
    case 12:
        if (sub_807CE24() == 0)
        {
            gWeatherPtr->unknown_6C0 = -6;
            gWeatherPtr->unknown_6C6 = 3;
        }
        break;
    case 6:
        if (sub_807CE7C() == 0)
        {
            gWeatherPtr->unknown_6C0 = 0;
            gWeatherPtr->unknown_6C6 = 3;
        }
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    default:
        if (!gPaletteFade.active)
        {
            gWeatherPtr->unknown_6C0 = gWeatherPtr->unknown_6C1;
            gWeatherPtr->unknown_6C6 = 3;
        }
        break;
    }
}

u8 sub_807CDC4(void)
{
    if (gWeatherPtr->unknown_6C7 == 0x10)
        return 0;
    if (++gWeatherPtr->unknown_6C7 >= 0x10)
    {
        sub_807CEBC(0, 0x20, 3);
        gWeatherPtr->unknown_6C7 = 0x10;
        return 0;
    }
    sub_807D1BC(0, 0x20, 3, 0x10 - gWeatherPtr->unknown_6C7, gWeatherPtr->unknown_6C4);
    return 1;
}

u8 sub_807CE24(void)
{
    if (gWeatherPtr->unknown_6C7 == 0x10)
        return 0;
    if (++gWeatherPtr->unknown_6C7 >= 0x10)
    {
        sub_807CEBC(0, 0x20, -6);
        gWeatherPtr->unknown_6C7 = 0x10;
        return 0;
    }
    sub_807D304(-6, 0x10 - gWeatherPtr->unknown_6C7, gWeatherPtr->unknown_6C4);
    return 1;
}

u8 sub_807CE7C(void)
{
    if (gWeatherPtr->unknown_6C7 == 0x10)
        return 0;
    ++gWeatherPtr->unknown_6C7;
    sub_807D424(0x10 - gWeatherPtr->unknown_6C7, gWeatherPtr->unknown_6C4);
    return 1;
}

void nullsub_39(void)
{
}

void sub_807CEBC(u8 a, u8 b, s8 c)
{
    u16 r4;
    u16 palOffset;
    u8 *r6;
    u16 i;

    if (c > 0)
    {
        c = c - 1;
        palOffset = a * 16;
        b += a;
        r4 = a;
        while (r4 < b)
        {
            if (gUnknown_030006DC[r4] == 0)
            {
                CpuFastCopy(gPlttBufferUnfaded + palOffset, gPlttBufferFaded + palOffset, 16 * sizeof(u16));
                palOffset += 16;
            }
            else
            {
                u8 r, g, b;

                if (gUnknown_030006DC[r4] == 2 || r4 - 16 == gWeatherPtr->unknown_6D5)
                    r6 = gWeatherPtr->unk460[c];
                else
                    r6 = gWeatherPtr->unknown_200[c];
                if (r4 == 16 || r4 > 0x1B)
                {
                    for (i = 0; i < 16; i++)
                    {
                        if (gPlttBufferUnfaded[palOffset] == 0x2D9F)
                        {
                            palOffset++;
                        }
                        else
                        {
                            struct RGBColor color = *(struct RGBColor *)&gPlttBufferUnfaded[palOffset];

                            r = r6[color.r];
                            g = r6[color.g];
                            b = r6[color.b];
                            gPlttBufferFaded[palOffset++] = (b << 10) | (g << 5) | r;
                        }
                    }
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        struct RGBColor color = *(struct RGBColor *)&gPlttBufferUnfaded[palOffset];

                        r = r6[color.r];
                        g = r6[color.g];
                        b = r6[color.b];
                        gPlttBufferFaded[palOffset++] = (b << 10) | (g << 5) | r;
                    }
                }
            }
            r4++;
        }
    }
    else if (c < 0)
    {
        c = -c - 1;
        palOffset = a * 16;
        b += a;
        r4 = a;
        while (r4 < b)
        {
            if (gUnknown_030006DC[r4] == 0)
            {
                CpuFastCopy(gPlttBufferUnfaded + palOffset, gPlttBufferFaded + palOffset, 16 * sizeof(u16));
                palOffset += 16;
            }
            else
            {
                if (r4 == 16 || r4 > 0x1B)
                {
                    for (i = 0; i < 16; i++)
                    {
                        if (gPlttBufferUnfaded[palOffset] != 0x2D9F)
                            gPlttBufferFaded[palOffset] = eWeatherPaletteData.data[c][MACRO1(gPlttBufferUnfaded[palOffset])];
                        palOffset++;
                    }
                }
                else
                {
                    for (i = 0; i < 16; i++)
                    {
                        gPlttBufferFaded[palOffset] = eWeatherPaletteData.data[c][MACRO1(gPlttBufferUnfaded[palOffset])];
                        palOffset++;
                    }
                }
            }
            r4++;
        }
    }
    else
    {
        CpuFastCopy(gPlttBufferUnfaded + a * 16, gPlttBufferFaded + a * 16, b * 16 * sizeof(u16));
    }
}

void sub_807D1BC(u8 a1, u8 a2, s8 c, u8 d, u16 e)
{
    u16 palOffset;
    u16 r4;
    u16 i;
    struct RGBColor color = *(struct RGBColor *)&e;
    u8 r_ = color.r;
    u8 g_ = color.g;
    u8 b_ = color.b;

    palOffset = a1 * 16;
    a2 += a1;
    c = c - 1;
    r4 = a1;
    while (r4 < a2)
    {
        if (gUnknown_030006DC[r4] == 0)
        {
            BlendPalette(palOffset, 16, d, e);
            palOffset += 16;
        }
        else
        {
            u8 *r5;

            if (gUnknown_030006DC[r4] == 1)
                r5 = gWeatherPtr->unknown_200[c];
            else
                r5 = gWeatherPtr->unk460[c];

            for (i = 0; i < 16; i++)
            {
                struct RGBColor color = *(struct RGBColor *)&gPlttBufferUnfaded[palOffset];
                u8 r = r5[color.r];
                u8 g = r5[color.g];
                u8 b = r5[color.b];

                r += ((r_ - r) * d) >> 4;
                g += ((g_ - g) * d) >> 4;
                b += ((b_ - b) * d) >> 4;
                gPlttBufferFaded[palOffset++] = (b << 10) | (g << 5) | r;
            }
        }
        r4++;
    }
}

void sub_807D304(s8 a, u8 arg2, u16 c)
{
    struct RGBColor color;
    u8 r_;
    u8 g_;
    u8 b_;
    u16 r4;
    u16 r5;
    u16 r12;

    a = -a - 1;
    color = *(struct RGBColor *)&c;
    r_ = color.r;
    g_ = color.g;
    b_ = color.b;
    r5 = 0;
    for (r4 = 0; r4 < 32; r4++)
    {
        if (gUnknown_030006DC[r4] == 0)
        {
            BlendPalette(r5, 16, arg2, c);
            r5 += 16;
        }
        else
        {
            for (r12 = 0; r12 < 16; r12++)
            {
                u32 offset;
                struct RGBColor color1;
                struct RGBColor color2;
                u8 r1, g1, b1;
                u8 r2, g2, b2;

                color1 = *(struct RGBColor *)&gPlttBufferUnfaded[r5];
                r1 = color1.r;
                g1 = color1.g;
                b1 = color1.b;

                offset = ((b1 & 0x1E) << 7) | ((g1 & 0x1E) << 3) | ((r1 & 0x1E) >> 1);
                color2 = *(struct RGBColor *)&eWeatherPaletteData.data[a][offset];
                r2 = color2.r;
                g2 = color2.g;
                b2 = color2.b;

                r2 += ((r_ - r2) * arg2) >> 4;
                g2 += ((g_ - g2) * arg2) >> 4;
                b2 += ((b_ - b2) * arg2) >> 4;

                gPlttBufferFaded[r5++] = (b2 << 10) | (g2 << 5) | r2;
            }
        }
    }
}

bool8 sub_807D574(u8);

void sub_807D424(u8 a, u16 b)
{
    struct RGBColor color;
    u8 r_;
    u8 g_;
    u8 b_;
    u16 r4;

    BlendPalette(0, 0x100, a, b);
    color = *(struct RGBColor *)&b;
    r_ = color.r;
    g_ = color.g;
    b_ = color.b;

    r4 = 16;
    while (r4 < 32)
    {
        if (sub_807D574(r4))
        {
            u16 r12 = (r4 + 1) * 16;
            u16 r6 = r4 * 16;

            while (r6 < r12)
            {
                struct RGBColor color = *(struct RGBColor *)&gPlttBufferUnfaded[r6];
                u8 r = color.r;
                u8 g = color.g;
                u8 b = color.b;

                r += ((28 - r) * 3) >> 2;
                g += ((31 - g) * 3) >> 2;
                b += ((28 - b) * 3) >> 2;

                r += ((r_ - r) * a) >> 4;
                g += ((g_ - g) * a) >> 4;
                b += ((b_ - b) * a) >> 4;

                gPlttBufferFaded[r6] = (b << 10) | (g << 5) | r;
                r6++;
            }
        }
        else
        {
            BlendPalette(r4 * 16, 16, a, b);
        }
        r4++;
    }
}

void sub_807D540(u8 a)
{
    if (gWeatherPtr->unknown_6FA < 6)
    {
        gWeatherPtr->unknown_6F4[gWeatherPtr->unknown_6FA] = a;
        gWeatherPtr->unknown_6FA++;
    }
}

bool8 sub_807D574(u8 a)
{
    u16 i;

    for (i = 0; i < gWeatherPtr->unknown_6FA; i++)
    {
        if (gWeatherPtr->unknown_6F4[i] == a)
            return TRUE;
    }
    return FALSE;
}

void sub_807D5BC(s8 a)
{
    if (gWeatherPtr->unknown_6C6 == 3)
    {
        sub_807CEBC(0, 32, a);
        gWeatherPtr->unknown_6C0 = a;
    }
}

void sub_807D5F0(u8 a, u8 b, u8 c)
{
    if (gWeatherPtr->unknown_6C6 == 3)
    {
        gWeatherPtr->unknown_6C6 = 0;
        gWeatherPtr->unknown_6C0 = a;
        gWeatherPtr->unknown_6C1 = b;
        gWeatherPtr->unknown_6C3 = 0;
        gWeatherPtr->unknown_6C2 = c;
        sub_807D5BC(a);
    }
}

void fade_screen(u8 a, u8 b)
{
    u32 r4;
    u32 r1;
    u32 r2;

    switch (a)
    {
    case 0:
        r4 = 0;
        r1 = 0;
        break;
    case 2:
        r4 = 0xFFFF;
        r1 = 0;
        break;
    case 1:
        r4 = 0;
        r1 = 1;
        break;
    case 3:
        r4 = 0xFFFF;
        r1 = 1;
        break;
    default:
        return;
    }

    switch (gWeatherPtr->currWeather)
    {
    case WEATHER_RAIN_LIGHT:
    case WEATHER_RAIN_MED:
    case WEATHER_RAIN_HEAVY:
    case WEATHER_SNOW:
    case 6:
    case 11:
    case 12:
        r2 = 1;
        break;
    default:
        r2 = 0;
        break;
    }

    if (r1 != 0)
    {
        if (r2 != 0)
            CpuFastCopy(gPlttBufferFaded, gPlttBufferUnfaded, 0x400);
        BeginNormalPaletteFade(0xFFFFFFFF, b, 0, 16, r4);
        gWeatherPtr->unknown_6C6 = 2;
    }
    else
    {
        gWeatherPtr->unknown_6C4 = r4;
        if (r2 != 0)
            gWeatherPtr->unknown_6C7 = 0;
        else
            BeginNormalPaletteFade(0xFFFFFFFF, b, 16, 0, r4);
        gWeatherPtr->unknown_6C6 = 1;
        gWeatherPtr->unknown_6CA = 1;
        gWeatherPtr->unknown_6CB = 0;
        sub_807DB64(gWeatherPtr->unknown_730, gWeatherPtr->unknown_732);
        gWeatherPtr->unknown_6C8 = 1;
    }
}

bool8 sub_807D770(void)
{
    return gWeatherPtr->unknown_6C6 ^ 1 ? TRUE : FALSE;
}

void sub_807D78C(u8 a)
{
    u16 r4 = 16 + a;
    u16 i;

    switch (gWeatherPtr->unknown_6C6)
    {
    case 1:
        if (gWeatherPtr->unknown_6CA != 0)
        {
            if (gWeatherPtr->currWeather == 6)
                sub_807D540(r4);
            r4 *= 16;
            for (i = 0; i < 16; i++)
                gPlttBufferFaded[r4 + i] = gWeatherPtr->unknown_6C4;
        }
        break;
    case 2:
        r4 *= 16;
        CpuFastCopy(gPlttBufferFaded + r4, gPlttBufferUnfaded + r4, 32);
        BlendPalette(r4, 16, gPaletteFade.y, gPaletteFade.blendColor);
        break;
    default:
        if (gWeatherPtr->currWeather != 6)
        {
            sub_807CEBC(r4, 1, gWeatherPtr->unknown_6C0);
        }
        else
        {
            r4 *= 16;
            BlendPalette(r4, 16, 12, 0x73FC);
        }
        break;
    }
}

void sub_807D874(u8 a)
{
    sub_807CEBC(a, 1, gWeatherPtr->unknown_6C0);
}

u8 unref_sub_807D894(void)
{
    if (gWeatherPtr->unknown_6C6 == 1)
        return gWeatherPtr->unknown_6CA;
    else
        return 0;
}

void sub_807D8C0(const u16 *palette)
{
    LoadPalette(palette, 0x100 + gWeatherPtr->unknown_6D4 * 16, 32);
    sub_807D78C(gWeatherPtr->unknown_6D4);
}

void sub_807D8F0(u8 *a, u8 *b)
{
    u8 r4 = *a;
    u16 i;

    if (r4 < 7)
    {
        r4--;
        LZ77UnCompWram(gUnknown_08396FA8[r4], eWeatherPaletteData.data[r4]);
        if (r4 == 0)
        {
            eWeatherPaletteData.data[r4][0] = 0x421;
            for (i = 1; i < 0x1000; i++)
                eWeatherPaletteData.data[r4][i] += eWeatherPaletteData.data[r4][i - 1];
        }
        else
        {
            for (i = 0; i < 0x1000; i++)
                eWeatherPaletteData.data[r4][i] += eWeatherPaletteData.data[r4 - 1][i];
        }
        (*a)++;
        if (*a == 7)
        {
            *a = 32;
            *b = 32;
        }
    }
}

void sub_807D9A8(void)
{
    gWeatherPtr->unknown_74D = 1;
    gWeatherPtr->unknown_74E = 1;
}

bool8 sub_807D9C8(void)
{
    if (gWeatherPtr->unknown_74D < 32)
    {
        sub_807D8F0(&gWeatherPtr->unknown_74D, &gWeatherPtr->unknown_74E);
        if (gWeatherPtr->unknown_74D < 32)
            return TRUE;
    }
    return FALSE;
}

void sub_807DA04(s8 a)
{
    sub_807D5BC(-a - 1);
}

void sub_807DA14(void)
{
    gWeatherPtr->unknown_73C = 0;
    gWeatherPtr->unknown_740 = 0;
    gWeatherPtr->unknown_742 = 0;
    gWeatherPtr->unknown_73E = 0;
    gUnknown_0202FF58 = 5;
}

void sub_807DA4C(void)
{
    switch (gWeatherPtr->unknown_742)
    {
    case 0:
        if (++gWeatherPtr->unknown_740 > gUnknown_0202FF58)
        {
            gWeatherPtr->unknown_740 = 0;
            sub_807DA04(gWeatherPtr->unknown_73C++);
            if (gWeatherPtr->unknown_73C > 5)
            {
                gWeatherPtr->unknown_73E = gWeatherPtr->unknown_73C;
                gWeatherPtr->unknown_742 = 1;
                gWeatherPtr->unknown_740 = 0x3C;
            }
        }
        break;
    case 1:
        gWeatherPtr->unknown_740 = (gWeatherPtr->unknown_740 + 3) & 0x7F;
        gWeatherPtr->unknown_73C = ((gSineTable[gWeatherPtr->unknown_740] - 1) >> 6) + 2;
        if (gWeatherPtr->unknown_73C != gWeatherPtr->unknown_73E)
            sub_807DA04(gWeatherPtr->unknown_73C);
        gWeatherPtr->unknown_73E = gWeatherPtr->unknown_73C;
        break;
    case 2:
        if (++gWeatherPtr->unknown_740 > gUnknown_0202FF58)
        {
            gWeatherPtr->unknown_740 = 0;
            sub_807DA04(--gWeatherPtr->unknown_73C);
            if (gWeatherPtr->unknown_73C == 3)
                gWeatherPtr->unknown_742 = 0;
        }
        break;
    }
}

void sub_807DB64(u8 a, u8 b)
{
    gWeatherPtr->unknown_730 = a;
    gWeatherPtr->unknown_732 = b;
    gWeatherPtr->unknown_734 = a;
    gWeatherPtr->unknown_736 = b;
    REG_BLDALPHA = (b << 8) | a;
}

void sub_807DBA4(u8 a, u8 b, int c)
{
    gWeatherPtr->unknown_734 = a;
    gWeatherPtr->unknown_736 = b;
    gWeatherPtr->unknown_73A = c;
    gWeatherPtr->unknown_739 = 0;
    gWeatherPtr->unknown_738 = 0;
}

bool8 sub_807DBE8(void)
{
    if (gWeatherPtr->unknown_730 == gWeatherPtr->unknown_734
     && gWeatherPtr->unknown_732 == gWeatherPtr->unknown_736)
        return TRUE;
    if (++gWeatherPtr->unknown_739 > gWeatherPtr->unknown_73A)
    {
        gWeatherPtr->unknown_739 = 0;
        gWeatherPtr->unknown_738++;
        if (gWeatherPtr->unknown_738 & 1)
        {
            if (gWeatherPtr->unknown_730 < gWeatherPtr->unknown_734)
                gWeatherPtr->unknown_730++;
            else if (gWeatherPtr->unknown_730 > gWeatherPtr->unknown_734)
                gWeatherPtr->unknown_730--;
        }
        else
        {
            if (gWeatherPtr->unknown_732 < gWeatherPtr->unknown_736)
                gWeatherPtr->unknown_732++;
            else if (gWeatherPtr->unknown_732 > gWeatherPtr->unknown_736)
                gWeatherPtr->unknown_732--;
        }
    }
    REG_BLDALPHA = (gWeatherPtr->unknown_732 << 8) | gWeatherPtr->unknown_730;
    if (gWeatherPtr->unknown_730 == gWeatherPtr->unknown_734
     && gWeatherPtr->unknown_732 == gWeatherPtr->unknown_736)
        return TRUE;
    return FALSE;
}

void unref_sub_807DCB4(u8 a)
{
    switch (a)
    {
    case 1:
        SetWeather(1);
        break;
    case 2:
        SetWeather(2);
        break;
    case 3:
        SetWeather(3);
        break;
    case 4:
        SetWeather(4);
        break;
    case 5:
        SetWeather(5);
        break;
    case 6:
        SetWeather(6);
        break;
    case 7:
        SetWeather(9);
        break;
    case 8:
        SetWeather(7);
        break;
    case 9:
        SetWeather(8);
        break;
    case 10:
        SetWeather(11);
        break;
    }
}

u8 weather_get_current(void)
{
    return gWeatherPtr->currWeather;
}

void SetRainStrengthFromSoundEffect(u16 sndEff)
{
    if (gWeatherPtr->unknown_6C6 != 2)
    {
        switch (sndEff)
        {
        case SE_T_KOAME:
            gWeatherPtr->rainStrength = 0;
            break;
        case SE_T_OOAME:
            gWeatherPtr->rainStrength = 1;
            break;
        case SE_T_AME:
            gWeatherPtr->rainStrength = 2;
            break;
        default:
            return;
        }
        PlaySE(sndEff);
    }
}

void PlayRainSoundEffect(void)
{
    if (IsSpecialSEPlaying())
    {
        switch (gWeatherPtr->rainStrength)
        {
        case 0:
            PlaySE(SE_T_KOAME_E);
            break;
        case 1:
            PlaySE(SE_T_OOAME_E);
            break;
        case 2:
        default:
            PlaySE(SE_T_AME_E);
            break;
        }
    }
}

u8 sub_807DDFC(void)
{
    return gWeatherPtr->unknown_6D3;
}

void sub_807DE10(void)
{
    gWeatherPtr->unknown_6C6 = 2;
}

void unref_sub_807DE24(void)
{
    gWeatherPtr->unknown_6C6 = 3;
}

void sub_807DE38(u8 a)
{
    CpuCopy16(gUnknown_083970C8, gUnknown_0202FF38, 32);
    gUnknown_0202FF38[a] = 0;
    gUnknown_030006DC = gUnknown_0202FF38;
}

void sub_807DE68(void)
{
    gUnknown_030006DC = gUnknown_083970C8;
}
