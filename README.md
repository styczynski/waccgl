# waccgl
Windows Advanced Console Componental Graphics Library

Some examples involving WACCGL usage:


## About
This is just another crazy library, which allows you to create ascii-text graphical user interface inside Windows Command Prompt!
Feautures:

  * Mouse (and scroll wheel) support (little fancy text cursor inside CMD!)
  * Fancy GUI inside command prompt
  * Handling special event
  * Many useful components (like lists, editboxes etc.)

Unfortunately this project isn't well documented yet (try to read the examples). :(

## Compiling
The library contains examples files.
To compile examples use the following command: `make all`
To get list of all available examples type: `make run-example`
To run an example type: `make run-example-NAME` (e.g. `make run-example-demo`)
To clean project directory use `make clean`

## Examples
The library contains few examples.
You can see them to figure out how to use WACCGL.

## Support for other OSes
All the library depends on `./include/console.h`.
If you want to port this library to linux just rewrite the `console.h` code.
