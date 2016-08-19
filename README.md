
Castlabs programming test, reading a mpeg4 file. 
- Created a standard parser that handles the general case
of logging length and type in its class, and the uses subclassing
for the MDAT, furtherly used recursion to handle the Container Box
types. 
- Question 1, maximum mdat size can be 4GB this may be exceeded quickly
given its text data. 
- Question 2, the image files are written using the image:id tag name
provided in the xml. 
- I used TinyXml for parsing the xml, I was just going to use regexp
in the STL then determined I needed to parse out the 3 attributes
for the filename, type, and encoding, so I used TinyXml. 
- I also borrowed the base64 decoding code from the web, just to 
be honest. 

after doing this I realize how much I would have enjoyed
working the pipeline group at TiVo, I had some experience with them but
didn't persue it to move over to work on the latest UI. 

415.533.1743

Thanks
Tom