# BmpFont

This is a text drawing class for use with [sf2dlib](https://github.com/xerpi/sf2dlib). It is designed as a lightweight alternative to [sftdlib](https://github.com/xerpi/sftdlib). sftdlib not only needs to be set up as a library, but also has the overhead of several dependency libraries which must also be linked. This "library" is much easier to set up, because all it requires is that you drag and drop its .cpp and .h files into your project and start using it. There are no dependencies other than sf2dlib.

While sftdlib uses vector-based TrueType font files, BmpFont loads raster-based .BFF font files. These fonts can be generated using [Codehead's Bitmap Font Generator (CBFG)](http://www.codehead.co.uk/cbfg/). It is recommended that you use the 8-bit grayscale format, and use the default white-on-black colors. This provides the smallest file size and still enables you to render text in any color, on a transparent background. The other two formats (24- and 32-bit) will still load fine, but their files are unnecessarily large, and in the case of the 24-bit format, text will not be drawn on a transparent background. These formats are useful if you are creating a full-color font, but while supported by the .BFF file format as well as this library, I don't know of any way to create these other than manually.

## Usage

The first step is to place BmpFont.cpp and BmpFont.h in your project's source directory. Then put one or more .bff font files in a location accessible by the program, such as romfs. Let's say you use the fixedsys.bff font included in this example. To draw text using that font, all you need to do is this:

    BmpFont font("fixedsys.bff"); //Load font file
    
    // ...
    
    sf2d_start_frame(GFX_TOP, GFX_LEFT);
    font.drawStr("Hello, world!", 8, 8, RGBA8(0x00, 0xFF, 0xFF, 0xFF));
    sf2d_end_frame();

This will use the loaded font to display the text "Hello, world!" in cyan at the coordinates 8, 8. There are also other ways to draw text, such as with character- and word-wrapping, and clipping text to a certain rectangle.

## Functions

The entire functionality of this library is contained within the BmpFont class. You draw text by calling member functions of this class. The following is a description of what each function does.

### (constructors)

    BmpFont();
    BmpFont(const char *filename);
    
The default constructor creates the BmpFont object without loading a font. A font must be loaded (using the `load` function) before it can be used. Attempting to perform any action on a BmpFont object without a font loaded, except for loading a font or checking the status using `operator bool`, results in undefined behavior.

If a filename is specified, a font will automatically be loaded upon creation. If an error occurs during loading, the result is the same as if no font was loaded. Use `operator bool` to check this.

### drawChar

    u8 drawChar(char ch, int x, int y, u32 color = WHITE) const;
    
Draws a single character on the screen, and returns the width of the character in pixels.

### drawStr

    u32 drawStr(const std::string &str, int x, int y, u32 color = WHITE) const;

Draws a string on the screen. The string is drawn on a single line, even if it doesn't fit on the screen, unless the string contains explicit new-line (`\n`) characters. The return value is the **width** of the string in pixels.

### drawStrWrap

    u32 drawStrWrap(const std::string &str, int x, int y, u32 wrapWidth, u32 color = WHITE) const;

Draws a string on the screen. Word wrapping is performed to keep it at a maximum width of `wrapWidth` pixels. The return value is the **height** of the string in pixels.

### drawStrCharWrap

    u32 drawStrCharWrap(const std::string &str, int x, int y, u32 wrapWidth, u32 color = WHITE) const;

Identical to `drawStrWrap`, except wrapping is performed as soon as the maximum width is reached, regardless of word boundaries.

### getTextDims, getTextWidth, getTextHeight

    void getTextDims(const std::string &str, u32 &width, u32 &height, u32 wrapWidth = 0) const;
    u32 getTextWidth(const std::string &str, u32 wrapWidth = 0) const;
    u32 getTextHeight(const std::string &str, u32 wrapWidth = 0) const;

Calculates the width and height of a string as it would be drawn, without actually drawing it. If `wrapWidth` is specified and greater than zero, the width and height are calculated according to how the string would be displayed by `drawStrCharWrap`.

`getTextWidth` and `getTextHeight` are helper functions that call `getTextDims` and only return one of the values; use these if you don't need both dimensions.

### clip, unclip

    BmpFont &clip(int left, int top, int right, int bottom);
    BmpFont &unclip();
    
After `clip` is called, any text drawn by this `BmpFont` object will be clipped to the given rectangle, cutting off anything not inside of it. Things like wrapping are unaffected; every pixel inside the rectangle is exactly as it would be if clipping was not being performed. This behavior will last until `clip` is called with different parameters, or `unclip` is called to disable clipping.

These functions return a reference to the object it is called upon, so function calls can be chained.

### isClipped

    bool isClipped() const;

Returns `true` if clip boundaries have been specified using the `clip` function, or `false` if clipping is disabled.

### height

    u32 height() const;

Returns the height of a single line displayed using this font.

### load

    bool load(const char *filename);

Loads a font. If a font is already loaded, `free` will be called automatically to unload the previous font. If successful, this function will return `true`. Otherwise, it will return `false` and the object will remain without a font loaded.

### free

    void free();

Unloads the currently-loaded font and frees the memory associated with it. After this function is called, no font will be loaded, similar to if the object was created using the default constructor. Note that there is no need to call this function in most cases, as it is automatically called by the destructor.

### operator bool

    operator bool() const;

Returns `true` if there is a font loaded, or `false` if not. This is the only way to check if a font was successfully loaded if it was loaded via the constructor, but generally this won't happen unless there's a problem with the font file.
