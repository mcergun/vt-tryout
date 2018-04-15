# Terminal Implementation
This application tries to imitate a limited virtual terminal functionality inside shell terminal.

The keycodes are constants embedded in Key classes. Following keys are implemented currently:

- Return
- Tab
- Home and End
- Backspace
- Delete
- Visual characters
- Arrow keys

The design is divided into three main parts:

- A single line buffer (Line class) to keep status of a single line (character count, cursor position, etc.)
- A collection of lines (LineBuffer class) to keep previous entries to the console
- A key handler (Key, KeyCommand, KeyConverter classes) to handle I/O interactions

Known issues:

- If string/command length is greater than console's length, things aren't interpreted correctly
- Auto complete functionality is fed by a static list that only has "auto", "complete", "list" members

Here's a demo from the application:

[![asciicast](https://asciinema.org/a/mAnIU3U4e22e9qAfMp87hgHnm.png)](https://asciinema.org/a/mAnIU3U4e22e9qAfMp87hgHnm)