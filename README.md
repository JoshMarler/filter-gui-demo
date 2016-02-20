# FilterGuiDemo
This plugin is an example of a simple filter frequency response display. 
The filter response GUI component is drawn using JUCE path's and is an evaluation of the filters transfer function. 

The code is basic and could do with some improvements. At present the filter in this plugin is a simple one pole 
virtual analogue filter so as to make the code dealing with the drawing of the filter response path as simple as 
possible to understand. 

Feel free to make any suggestions to this repo/code, I am hoping this plugin will be useful for JUCE newbies and give a 
starting point for a handy GUI class for others. I will gradually attempt to make the filter response GUI component/class more
reusable and generic for inclusion into people's projects.

For example the FilterReponseDisplay class could be setup to use a callback / std::function object to calculate the filters magnitude response rather than depending on an AudioFilter object. The function object would simply need to be passed into the FilterResponseDisplay class constructor. This could make the class a little more generic, I’ll leave it up to the reader for now and will add this in on a future version. 

Future revisions of this example plugin will implement further filter types (Moog Ladder, SVF etc.) and response shapes along with oversampling and some other goodies. 




Thanks and credit to the following for allowing me to use some of their code/Ideas to build off. 

The guys at Semantic Audio for letting me use/pull apart their own filter display class - http://www.semanticaudio.co.uk

Vadim Zavalishin for the excellent VA Filter paper - https://www.native-instruments.com/fileadmin/ni_media/downloads/pdf/VAFilterDesign_1.1.1.pdf

Cheers

Josh 