[![Made by Styczynsky Digital Systems][badge sts]][link isis97]

[![Platform - Windows][badge support windows]][link isis97]

# WACCGL (C/C++ library, Windows)
Windows Advanced Console Componental Graphics Library

Some examples involving WACCGL usage:

TicTacConsole game involves usage of old integrated WACCGL code [see...](https://github.com/isis97/TicTacConsole)

![WACCGL Screenshot No. 1](https://raw.githubusercontent.com/isis97/waccgl/master/static/screenshot0.png "Example no. 1")
![WACCGL Screenshot No. 2](https://raw.githubusercontent.com/isis97/waccgl/master/static/screenshot1.png "Example no. 2")
![WACCGL Screenshot No. 3](https://raw.githubusercontent.com/isis97/waccgl/master/static/screenshot2.png "Example no. 3")


## About
This is just another crazy library, which allows you to create ascii-text graphical user interface inside Windows Command Prompt!

All Feautures:

  * Mouse (and scroll wheel) support (little fancy text cursor inside CMD!)
  * Fancy GUI inside command prompt
  * Handling special event
  * Many useful components (like lists, editboxes etc.)

Unfortunately this project isn't well documented yet (try to read the examples). :(

## Compiling
The library contains examples files.
Makefile commands:

 * To get some help type `make` or `make help`
 * To compile examples use the following command: `make all`
 * To get list of all available examples type: `make run-example`
 * To run an example type: `make run-example-NAME` (e.g. `make run-example-demo`)
 * To clean project directory use `make clean`
 * To rebuild everything run: `make rebuild`

## Examples
The library contains few examples.
You can see them to figure out how to use WACCGL.

 * `basic.cpp` - basic usage
 * `demo.cpp` - demo of some components
 * `manual-drawing.cpp` - some manual buffer manipulation code
 * `mouse.cpp` - simple mouse support
 * `no-buffer-cleaning.cpp` - you don't have to clean up this mess
 * `scene-animations.cpp` - some simple transitions
 * `windows.cpp` - how about an iternal window?
 * `own-component.cpp` - custom component implementation

## Support for other OSes
All the library depends on `./include/console.h`.

If you want to port this library to linux just rewrite the `console.h` code.

## Supported GUI components:

 * Scenes - `scene`
 * Checkboxes - `checkbox`
 * Text frames - `textframe`
 * Component frames - `frame`
 * Ascii image frames - `imgframe`
 * Buttons - `button`
 * Select boxes - `selbox / slistbox / listbox`
 * Expandable lists - `exlistbox`
 * Scrollbars - `vscrollbar`
 * Progressbars - `progressbar`
 * Edit boxes - `edittextframe`

Of course you can implement any GUI component by extending `scene_object` class.


[badge support windows]: https://img.shields.io/badge/platform-windows-blue.svg?style=flat-square&logoWidth=20&logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAABmJLR0QA%2FwD%2FAP%2BgvaeTAAAACXBIWXMAAA7EAAAOxAGVKw4bAAAAB3RJTUUH4AgSEisSipueyAAAAHBJREFUSMdjZKA2WPv%2BPzKXkSxDiuf%2FZ7AKIEopbgsW3v%2FPwCOA4AcLMqK7jhjAQo4mUgATA43BqAWjFlADiCvQ1HjsuXNJIwPD%2BgmMtLMAGyCzqBhNRaMWDAELWBiCBRmJrcDJy2hUaj1Q3wIiLQcAUjQgoD1kMJYAAAAASUVORK5CYII%3D

[badge sts]: https://img.shields.io/badge/-styczynsky_digital_systems-blue.svg?style=flat-square&logoWidth=20&logo=data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAABYAAAAXCAYAAAAP6L%2BeAAAABmJLR0QA%2FwD%2FAP%2BgvaeTAAAACXBIWXMAAA7DAAAOwwHHb6hkAAAAB3RJTUUH4AgSEh0nVTTLngAAAB1pVFh0Q29tbWVudAAAAAAAQ3JlYXRlZCB3aXRoIEdJTVBkLmUHAAAAm0lEQVQ4y2Pc%2Bkz2PwMNAAs2wVMzk4jSbJY%2BD6ccEwONACMsKIh1JSEgbXKeQdr4PO1cPPQMZiGkoC7bkCQD7%2Fx7znDn35AOClK9PEJSBbNYAJz999UGrOLocsM0KHB5EZ%2FXPxiVMDAwMDD8SP3DwJA6kFka5hJCQOBcDwMDAwPDm3%2FbGBj%2BbR8tNrFUTbiAB8tknHI7%2FuTilAMA9aAwA8miDpgAAAAASUVORK5CYII%3D

[link isis97]: https://github.com/isis97/
