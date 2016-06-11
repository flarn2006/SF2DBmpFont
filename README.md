# BmpFont

This is a text drawing class for use with [sf2dlib](https://github.com/xerpi/sf2dlib). It is designed as a lightweight alternative to [sftdlib](https://github.com/xerpi/sftdlib). sftdlib not only needs to be set up as a library, but also has the overhead of several dependency libraries which must also be linked. This "library" is much easier to set up, because all it requires is that you drag and drop its .cpp and .h files into your project and start using it. There are no dependencies other than sf2dlib.

While sftdlib uses vector-based TrueType font files, BmpFont loads raster-based .BFF font files. These fonts can be generated using [Codehead's Bitmap Font Generator (CBFG)](http://www.codehead.co.uk/cbfg/). It is recommended that you use the 8-bit grayscale format, and use the default white-on-black colors. This provides the smallest file size and still enables you to render text in any color, on a transparent background. The other two formats (24- and 32-bit) will still load fine, but their files are unnecessarily large. These formats are useful if you are creating a full-color font, but while supported by the .BFF file format, I don't know of any way to create these other than manually.

## Usage

The first step is to place BmpFont.cpp and BmpFont.h in your project's source directory. Then put one or more .bff font files in a location accessible by the program, such as romfs. Let's say you use the fixedsys.bff font included in this example. To draw text using that font, all you need to do is this:

    BmpFont font("fixedsys.bff"); //Load font file
    
    // ...
    
    sf2d_start_frame(GFX_TOP, GFX_LEFT);
    font.drawStr("Hello, world!", 8, 8, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
    sf2d_end_frame();

This will use the loaded font to display the text "Hello, world!" in cyan at the coordinates 8, 8. There are also other ways to draw text, such as with character- and word-wrapping, and clipping text to a certain rectangle. For now, look at the header file and the example program (main.cpp) for more information; traditional documentation has not yet been written. Sorry for the inconvenience.

Note that while it is possible to manually free the memory used by a font by calling `BmpFont::free()`, you do not need to worry about doing so before the program exits, as it is automatically called by the destructor.
