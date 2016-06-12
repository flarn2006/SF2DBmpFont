#ifndef BMPFONT_EXAMPLE
#error "main.cpp is the example program. Only BmpFont.h and BmpFont.cpp are needed to use the library."
#endif

#include <3ds.h>
#include <sf2d.h>
#include <string>
#include <sstream>
#include "BmpFont.h"

// This function needs to be implemented manually because of a bug in MinGW. Grrr...
template <typename _T>
inline std::string to_string(const _T &obj)
{
    std::ostringstream ss;
    ss << obj;
    return ss.str();
}

int main(int argc, char *argv[])
{
    romfsInit();
    sf2d_init();
    sf2d_set_clear_color(RGBA8(0x00, 0x00, 0xC0, 0xFF));
    
    BmpFont fixedsys("fixedsys.bff");
    BmpFont impact("impact.bff");
    BmpFont century("century.bff");
    BmpFont times("times.bff");
    
    if (!impact || !fixedsys) {
        sf2d_set_clear_color(RGBA8(0xFF, 0x00, 0x00, 0xFF));
    }
    
    unsigned int frame = 0;
    
    std::string clipclip = "";
    for (int i=0; i<7; ++i) {
        clipclip += "CLIP CLIP CLIP CLIP CLIP CLIP CLIP CLIP\n";
    }
    
    while (aptMainLoop()) {
        hidScanInput();
        int keys = hidKeysHeld();
        if (keys & KEY_START) {
            break;
        }
        
        sf2d_start_frame(GFX_TOP, GFX_LEFT);
        
        sf2d_draw_rectangle(frame % 140, frame % 140, 400 - 2*(frame % 140), 240 - 2*(frame % 140), RGBA8(0x00, 0x00, 0x00, 0xFF));
        impact.clip(frame % 140, frame % 140, 400 - frame % 140, 240 - frame % 140);
        impact.drawStr(clipclip, 6, 16, RGBA8(0xFF, 0x00, 0x00, 0xFF));
        impact.unclip();
        
        fixedsys.drawStr("Hello, world!", 5, 5, RGBA8(0x00, 0x00, 0x00, 0xFF));
        fixedsys.drawStr("Hello, world!", 4, 4, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
        
        u32 width, height;
        fixedsys.getTextDims("Hello, world!", width, height);
        std::string dimsText = "<- " + to_string(width) + " x " + to_string(height);
        fixedsys.drawStr(dimsText, width + 12, 4, RGBA8(0xFF, 0xFF, 0xFF, 0x80));
        
        sf2d_end_frame();
        
        sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
        
        century.drawStr("Variable-width fonts\nare supported here!", 0, 0, RGBA8(0x00, 0xFF, 0x00, 0xFF));
        
        std::string longString = "This is a long string of text that will be wrapped to multiple lines.\nIt also contains a line break, which works as you would expect. ";
        longString += "And_this_word_is_very_long_and_cannot_be_displayed_on_a_single_line. This-is_how_hyphens_are_treated.\n                    ";
        std::string str = longString.substr(0, frame % (longString.size() + 1));
        
        height = fixedsys.drawStrWrap(str, 0, 70, 320, RGBA8(0xFF, 0xFF, 0x00, 0xFF));
        fixedsys.drawStr("That makes " + to_string(height / fixedsys.height()) + " line(s) total + this one.", 0, 70 + height, RGBA8(0xFF, 0xFF, 0x00, 0xFF));
        
        sf2d_draw_rectangle(0, 240 - times.height(), 320, times.height(), RGBA8(0xFF, 0xFF, 0xFF, 0xFF));
        times.drawStr("Variable-width fonts work well for small text as well.", 0, 240 - times.height(), RGBA8(0x00, 0x00, 0x00, 0xFF));
        
        sf2d_end_frame();
        
        sf2d_swapbuffers();
        ++frame;
    }
    
    sf2d_fini();
    romfsExit();
    
    return 0;
}