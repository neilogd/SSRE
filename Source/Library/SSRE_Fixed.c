/*
Simple Software Rasterising Engine

Copyright (c) 2014 Neil Richardson (neilogd)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "SSRE_Fixed.h"

SSRE_Fixed_t s_SineTable[256] = 
{
	SSRE_Fixed_FromFloat( 0 ),
	SSRE_Fixed_FromFloat( 0.02454122 ),
	SSRE_Fixed_FromFloat( 0.04906767 ),
	SSRE_Fixed_FromFloat( 0.07356456 ),
	SSRE_Fixed_FromFloat( 0.09801714 ),
	SSRE_Fixed_FromFloat( 0.12241068 ),
	SSRE_Fixed_FromFloat( 0.14673047 ),
	SSRE_Fixed_FromFloat( 0.17096188 ),
	SSRE_Fixed_FromFloat( 0.19509031 ),
	SSRE_Fixed_FromFloat( 0.21910122 ),
	SSRE_Fixed_FromFloat( 0.24298016 ),
	SSRE_Fixed_FromFloat( 0.26671274 ),
	SSRE_Fixed_FromFloat( 0.29028467 ),
	SSRE_Fixed_FromFloat( 0.31368175 ),
	SSRE_Fixed_FromFloat( 0.33688987 ),
	SSRE_Fixed_FromFloat( 0.35989506 ),
	SSRE_Fixed_FromFloat( 0.38268346 ),
	SSRE_Fixed_FromFloat( 0.40524136 ),
	SSRE_Fixed_FromFloat( 0.42755514 ),
	SSRE_Fixed_FromFloat( 0.44961139 ),
	SSRE_Fixed_FromFloat( 0.47139680 ),
	SSRE_Fixed_FromFloat( 0.49289827 ),
	SSRE_Fixed_FromFloat( 0.51410283 ),
	SSRE_Fixed_FromFloat( 0.53499771 ),
	SSRE_Fixed_FromFloat( 0.55557033 ),
	SSRE_Fixed_FromFloat( 0.57580829 ),
	SSRE_Fixed_FromFloat( 0.59569941 ),
	SSRE_Fixed_FromFloat( 0.61523170 ),
	SSRE_Fixed_FromFloat( 0.63439340 ),
	SSRE_Fixed_FromFloat( 0.65317297 ),
	SSRE_Fixed_FromFloat( 0.67155908 ),
	SSRE_Fixed_FromFloat( 0.68954068 ),
	SSRE_Fixed_FromFloat( 0.70710692 ),
	SSRE_Fixed_FromFloat( 0.72424722 ),
	SSRE_Fixed_FromFloat( 0.74095127 ),
	SSRE_Fixed_FromFloat( 0.75720899 ),
	SSRE_Fixed_FromFloat( 0.77301060 ),
	SSRE_Fixed_FromFloat( 0.78834658 ),
	SSRE_Fixed_FromFloat( 0.80320768 ),
	SSRE_Fixed_FromFloat( 0.81758496 ),
	SSRE_Fixed_FromFloat( 0.83146976 ),
	SSRE_Fixed_FromFloat( 0.84485368 ),
	SSRE_Fixed_FromFloat( 0.85772870 ),
	SSRE_Fixed_FromFloat( 0.87008705 ),
	SSRE_Fixed_FromFloat( 0.88192130 ),
	SSRE_Fixed_FromFloat( 0.89322431 ),
	SSRE_Fixed_FromFloat( 0.90398928 ),
	SSRE_Fixed_FromFloat( 0.91420972 ),
	SSRE_Fixed_FromFloat( 0.92387948 ),
	SSRE_Fixed_FromFloat( 0.93299273 ),
	SSRE_Fixed_FromFloat( 0.94154399 ),
	SSRE_Fixed_FromFloat( 0.94952809 ),
	SSRE_Fixed_FromFloat( 0.95694024 ),
	SSRE_Fixed_FromFloat( 0.96377596 ),
	SSRE_Fixed_FromFloat( 0.97003115 ),
	SSRE_Fixed_FromFloat( 0.97570202 ),
	SSRE_Fixed_FromFloat( 0.98078518 ),
	SSRE_Fixed_FromFloat( 0.98527754 ),
	SSRE_Fixed_FromFloat( 0.98917642 ),
	SSRE_Fixed_FromFloat( 0.99247945 ),
	SSRE_Fixed_FromFloat( 0.99518465 ),
	SSRE_Fixed_FromFloat( 0.99729040 ),
	SSRE_Fixed_FromFloat( 0.99879541 ),
	SSRE_Fixed_FromFloat( 0.99969879 ),
	SSRE_Fixed_FromFloat( 0.99999999 ),
	SSRE_Fixed_FromFloat( 0.99969884 ),
	SSRE_Fixed_FromFloat( 0.99879550 ),
	SSRE_Fixed_FromFloat( 0.99729053 ),
	SSRE_Fixed_FromFloat( 0.99518483 ),
	SSRE_Fixed_FromFloat( 0.99247967 ),
	SSRE_Fixed_FromFloat( 0.98917668 ),
	SSRE_Fixed_FromFloat( 0.98527785 ),
	SSRE_Fixed_FromFloat( 0.98078553 ),
	SSRE_Fixed_FromFloat( 0.97570242 ),
	SSRE_Fixed_FromFloat( 0.97003159 ),
	SSRE_Fixed_FromFloat( 0.96377645 ),
	SSRE_Fixed_FromFloat( 0.95694077 ),
	SSRE_Fixed_FromFloat( 0.94952866 ),
	SSRE_Fixed_FromFloat( 0.94154460 ),
	SSRE_Fixed_FromFloat( 0.93299339 ),
	SSRE_Fixed_FromFloat( 0.92388018 ),
	SSRE_Fixed_FromFloat( 0.91421046 ),
	SSRE_Fixed_FromFloat( 0.90399001 ),
	SSRE_Fixed_FromFloat( 0.89322502 ),
	SSRE_Fixed_FromFloat( 0.88192199 ),
	SSRE_Fixed_FromFloat( 0.87008771 ),
	SSRE_Fixed_FromFloat( 0.85772933 ),
	SSRE_Fixed_FromFloat( 0.84485427 ),
	SSRE_Fixed_FromFloat( 0.83147031 ),
	SSRE_Fixed_FromFloat( 0.81758550 ),
	SSRE_Fixed_FromFloat( 0.80320820 ),
	SSRE_Fixed_FromFloat( 0.78834707 ),
	SSRE_Fixed_FromFloat( 0.77301107 ),
	SSRE_Fixed_FromFloat( 0.75720944 ),
	SSRE_Fixed_FromFloat( 0.74095169 ),
	SSRE_Fixed_FromFloat( 0.72424762 ),
	SSRE_Fixed_FromFloat( 0.70710728 ),
	SSRE_Fixed_FromFloat( 0.68954100 ),
	SSRE_Fixed_FromFloat( 0.67155937 ),
	SSRE_Fixed_FromFloat( 0.65317322 ),
	SSRE_Fixed_FromFloat( 0.63439361 ),
	SSRE_Fixed_FromFloat( 0.61523187 ),
	SSRE_Fixed_FromFloat( 0.59569953 ),
	SSRE_Fixed_FromFloat( 0.57580837 ),
	SSRE_Fixed_FromFloat( 0.55557035 ),
	SSRE_Fixed_FromFloat( 0.53499768 ),
	SSRE_Fixed_FromFloat( 0.51410275 ),
	SSRE_Fixed_FromFloat( 0.49289814 ),
	SSRE_Fixed_FromFloat( 0.47139662 ),
	SSRE_Fixed_FromFloat( 0.44961115 ),
	SSRE_Fixed_FromFloat( 0.42755485 ),
	SSRE_Fixed_FromFloat( 0.40524100 ),
	SSRE_Fixed_FromFloat( 0.38268305 ),
	SSRE_Fixed_FromFloat( 0.35989459 ),
	SSRE_Fixed_FromFloat( 0.33688934 ),
	SSRE_Fixed_FromFloat( 0.31368115 ),
	SSRE_Fixed_FromFloat( 0.29028402 ),
	SSRE_Fixed_FromFloat( 0.26671203 ),
	SSRE_Fixed_FromFloat( 0.24297938 ),
	SSRE_Fixed_FromFloat( 0.21910037 ),
	SSRE_Fixed_FromFloat( 0.19508937 ),
	SSRE_Fixed_FromFloat( 0.17096087 ),
	SSRE_Fixed_FromFloat( 0.14672938 ),
	SSRE_Fixed_FromFloat( 0.12240951 ),
	SSRE_Fixed_FromFloat( 0.09801590 ),
	SSRE_Fixed_FromFloat( 0.07356325 ),
	SSRE_Fixed_FromFloat( 0.04906629 ),
	SSRE_Fixed_FromFloat( 0.02453978 ),
	SSRE_Fixed_FromFloat( -0.00000151 ),
	SSRE_Fixed_FromFloat( -0.02454281 ),
	SSRE_Fixed_FromFloat( -0.04906932 ),
	SSRE_Fixed_FromFloat( -0.07356628 ),
	SSRE_Fixed_FromFloat( -0.09801892 ),
	SSRE_Fixed_FromFloat( -0.12241252 ),
	SSRE_Fixed_FromFloat( -0.14673238 ),
	SSRE_Fixed_FromFloat( -0.17096386 ),
	SSRE_Fixed_FromFloat( -0.19509235 ),
	SSRE_Fixed_FromFloat( -0.21910333 ),
	SSRE_Fixed_FromFloat( -0.24298232 ),
	SSRE_Fixed_FromFloat( -0.26671495 ),
	SSRE_Fixed_FromFloat( -0.29028692 ),
	SSRE_Fixed_FromFloat( -0.31368404 ),
	SSRE_Fixed_FromFloat( -0.33689220 ),
	SSRE_Fixed_FromFloat( -0.35989742 ),
	SSRE_Fixed_FromFloat( -0.38268586 ),
	SSRE_Fixed_FromFloat( -0.40524378 ),
	SSRE_Fixed_FromFloat( -0.42755759 ),
	SSRE_Fixed_FromFloat( -0.44961386 ),
	SSRE_Fixed_FromFloat( -0.47139930 ),
	SSRE_Fixed_FromFloat( -0.49290078 ),
	SSRE_Fixed_FromFloat( -0.51410535 ),
	SSRE_Fixed_FromFloat( -0.53500025 ),
	SSRE_Fixed_FromFloat( -0.55557288 ),
	SSRE_Fixed_FromFloat( -0.57581085 ),
	SSRE_Fixed_FromFloat( -0.59570197 ),
	SSRE_Fixed_FromFloat( -0.61523426 ),
	SSRE_Fixed_FromFloat( -0.63439596 ),
	SSRE_Fixed_FromFloat( -0.65317552 ),
	SSRE_Fixed_FromFloat( -0.67156162 ),
	SSRE_Fixed_FromFloat( -0.68954320 ),
	SSRE_Fixed_FromFloat( -0.70710942 ),
	SSRE_Fixed_FromFloat( -0.72424971 ),
	SSRE_Fixed_FromFloat( -0.74095373 ),
	SSRE_Fixed_FromFloat( -0.75721127 ),
	SSRE_Fixed_FromFloat( -0.77301285 ),
	SSRE_Fixed_FromFloat( -0.78834879 ),
	SSRE_Fixed_FromFloat( -0.80320986 ),
	SSRE_Fixed_FromFloat( -0.81758711 ),
	SSRE_Fixed_FromFloat( -0.83147186 ),
	SSRE_Fixed_FromFloat( -0.84485577 ),
	SSRE_Fixed_FromFloat( -0.85773077 ),
	SSRE_Fixed_FromFloat( -0.87008909 ),
	SSRE_Fixed_FromFloat( -0.88192331 ),
	SSRE_Fixed_FromFloat( -0.89322628 ),
	SSRE_Fixed_FromFloat( -0.90399120 ),
	SSRE_Fixed_FromFloat( -0.91421159 ),
	SSRE_Fixed_FromFloat( -0.92388130 ),
	SSRE_Fixed_FromFloat( -0.93299448 ),
	SSRE_Fixed_FromFloat( -0.94154566 ),
	SSRE_Fixed_FromFloat( -0.94952969 ),
	SSRE_Fixed_FromFloat( -0.95694175 ),
	SSRE_Fixed_FromFloat( -0.96377739 ),
	SSRE_Fixed_FromFloat( -0.97003247 ),
	SSRE_Fixed_FromFloat( -0.97570324 ),
	SSRE_Fixed_FromFloat( -0.98078629 ),
	SSRE_Fixed_FromFloat( -0.98527853 ),
	SSRE_Fixed_FromFloat( -0.98917729 ),
	SSRE_Fixed_FromFloat( -0.99248019 ),
	SSRE_Fixed_FromFloat( -0.99518526 ),
	SSRE_Fixed_FromFloat( -0.99729086 ),
	SSRE_Fixed_FromFloat( -0.99879573 ),
	SSRE_Fixed_FromFloat( -0.99969895 ),
	SSRE_Fixed_FromFloat( -0.99999999 ),
	SSRE_Fixed_FromFloat( -0.99969867 ),
	SSRE_Fixed_FromFloat( -0.99879516 ),
	SSRE_Fixed_FromFloat( -0.99729001 ),
	SSRE_Fixed_FromFloat( -0.99518413 ),
	SSRE_Fixed_FromFloat( -0.99247879 ),
	SSRE_Fixed_FromFloat( -0.98917560 ),
	SSRE_Fixed_FromFloat( -0.98527657 ),
	SSRE_Fixed_FromFloat( -0.98078405 ),
	SSRE_Fixed_FromFloat( -0.97570073 ),
	SSRE_Fixed_FromFloat( -0.97002969 ),
	SSRE_Fixed_FromFloat( -0.96377433 ),
	SSRE_Fixed_FromFloat( -0.95693842 ),
	SSRE_Fixed_FromFloat( -0.94952609 ),
	SSRE_Fixed_FromFloat( -0.94154180 ),
	SSRE_Fixed_FromFloat( -0.93299035 ),
	SSRE_Fixed_FromFloat( -0.92387691 ),
	SSRE_Fixed_FromFloat( -0.91420695 ),
	SSRE_Fixed_FromFloat( -0.90398630 ),
	SSRE_Fixed_FromFloat( -0.89322112 ),
	SSRE_Fixed_FromFloat( -0.88191790 ),
	SSRE_Fixed_FromFloat( -0.87008344 ),
	SSRE_Fixed_FromFloat( -0.85772487 ),
	SSRE_Fixed_FromFloat( -0.84484964 ),
	SSRE_Fixed_FromFloat( -0.83146549 ),
	SSRE_Fixed_FromFloat( -0.81758050 ),
	SSRE_Fixed_FromFloat( -0.80320303 ),
	SSRE_Fixed_FromFloat( -0.78834174 ),
	SSRE_Fixed_FromFloat( -0.77300557 ),
	SSRE_Fixed_FromFloat( -0.75720378 ),
	SSRE_Fixed_FromFloat( -0.74094587 ),
	SSRE_Fixed_FromFloat( -0.72424164 ),
	SSRE_Fixed_FromFloat( -0.70710115 ),
	SSRE_Fixed_FromFloat( -0.68953472 ),
	SSRE_Fixed_FromFloat( -0.67155295 ),
	SSRE_Fixed_FromFloat( -0.65316665 ),
	SSRE_Fixed_FromFloat( -0.63438691 ),
	SSRE_Fixed_FromFloat( -0.61522504 ),
	SSRE_Fixed_FromFloat( -0.59569257 ),
	SSRE_Fixed_FromFloat( -0.57580128 ),
	SSRE_Fixed_FromFloat( -0.55556315 ),
	SSRE_Fixed_FromFloat( -0.53499036 ),
	SSRE_Fixed_FromFloat( -0.51409531 ),
	SSRE_Fixed_FromFloat( -0.49289059 ),
	SSRE_Fixed_FromFloat( -0.47138897 ),
	SSRE_Fixed_FromFloat( -0.44960341 ),
	SSRE_Fixed_FromFloat( -0.42754701 ),
	SSRE_Fixed_FromFloat( -0.40523308 ),
	SSRE_Fixed_FromFloat( -0.38267504 ),
	SSRE_Fixed_FromFloat( -0.35988650 ),
	SSRE_Fixed_FromFloat( -0.33688117 ),
	SSRE_Fixed_FromFloat( -0.31367292 ),
	SSRE_Fixed_FromFloat( -0.29027572 ),
	SSRE_Fixed_FromFloat( -0.26670367 ),
	SSRE_Fixed_FromFloat( -0.24297097 ),
	SSRE_Fixed_FromFloat( -0.21909191 ),
	SSRE_Fixed_FromFloat( -0.19508087 ),
	SSRE_Fixed_FromFloat( -0.17095233 ),
	SSRE_Fixed_FromFloat( -0.14672080 ),
	SSRE_Fixed_FromFloat( -0.12240090 ),
	SSRE_Fixed_FromFloat( -0.09800727 ),
	SSRE_Fixed_FromFloat( -0.07355461 ),
	SSRE_Fixed_FromFloat( -0.04905763 ),
	SSRE_Fixed_FromFloat( -0.02453111 )
};

SSRE_Fixed_t s_TangentTable[256] = 
{
	SSRE_Fixed_FromFloat( 0 ),
	SSRE_Fixed_FromFloat( 0.02454862 ),
	SSRE_Fixed_FromFloat( 0.04912685 ),
	SSRE_Fixed_FromFloat( 0.07376443 ),
	SSRE_Fixed_FromFloat( 0.09849140 ),
	SSRE_Fixed_FromFloat( 0.12333824 ),
	SSRE_Fixed_FromFloat( 0.14833598 ),
	SSRE_Fixed_FromFloat( 0.17351645 ),
	SSRE_Fixed_FromFloat( 0.19891235 ),
	SSRE_Fixed_FromFloat( 0.22455749 ),
	SSRE_Fixed_FromFloat( 0.25048693 ),
	SSRE_Fixed_FromFloat( 0.27673726 ),
	SSRE_Fixed_FromFloat( 0.30334668 ),
	SSRE_Fixed_FromFloat( 0.33035538 ),
	SSRE_Fixed_FromFloat( 0.35780574 ),
	SSRE_Fixed_FromFloat( 0.38574260 ),
	SSRE_Fixed_FromFloat( 0.41421361 ),
	SSRE_Fixed_FromFloat( 0.44326957 ),
	SSRE_Fixed_FromFloat( 0.47296485 ),
	SSRE_Fixed_FromFloat( 0.50335778 ),
	SSRE_Fixed_FromFloat( 0.53451123 ),
	SSRE_Fixed_FromFloat( 0.56649312 ),
	SSRE_Fixed_FromFloat( 0.59937707 ),
	SSRE_Fixed_FromFloat( 0.63324317 ),
	SSRE_Fixed_FromFloat( 0.66817881 ),
	SSRE_Fixed_FromFloat( 0.70427965 ),
	SSRE_Fixed_FromFloat( 0.74165076 ),
	SSRE_Fixed_FromFloat( 0.78040790 ),
	SSRE_Fixed_FromFloat( 0.82067905 ),
	SSRE_Fixed_FromFloat( 0.86260622 ),
	SSRE_Fixed_FromFloat( 0.90634749 ),
	SSRE_Fixed_FromFloat( 0.95207951 ),
	SSRE_Fixed_FromFloat( 1.00000040 ),
	SSRE_Fixed_FromFloat( 1.05033328 ),
	SSRE_Fixed_FromFloat( 1.10333046 ),
	SSRE_Fixed_FromFloat( 1.15927844 ),
	SSRE_Fixed_FromFloat( 1.21850412 ),
	SSRE_Fixed_FromFloat( 1.28138224 ),
	SSRE_Fixed_FromFloat( 1.34834464 ),
	SSRE_Fixed_FromFloat( 1.41989171 ),
	SSRE_Fixed_FromFloat( 1.49660667 ),
	SSRE_Fixed_FromFloat( 1.57917337 ),
	SSRE_Fixed_FromFloat( 1.66839989 ),
	SSRE_Fixed_FromFloat( 1.76524741 ),
	SSRE_Fixed_FromFloat( 1.87086878 ),
	SSRE_Fixed_FromFloat( 1.98665895 ),
	SSRE_Fixed_FromFloat( 2.11432226 ),
	SSRE_Fixed_FromFloat( 2.25596344 ),
	SSRE_Fixed_FromFloat( 2.41421276 ),
	SSRE_Fixed_FromFloat( 2.59240123 ),
	SSRE_Fixed_FromFloat( 2.79481087 ),
	SSRE_Fixed_FromFloat( 3.02704051 ),
	SSRE_Fixed_FromFloat( 3.29655447 ),
	SSRE_Fixed_FromFloat( 3.61353056 ),
	SSRE_Fixed_FromFloat( 3.99221677 ),
	SSRE_Fixed_FromFloat( 4.45319256 ),
	SSRE_Fixed_FromFloat( 5.02732601 ),
	SSRE_Fixed_FromFloat( 5.76312275 ),
	SSRE_Fixed_FromFloat( 6.74142396 ),
	SSRE_Fixed_FromFloat( 8.10774162 ),
	SSRE_Fixed_FromFloat( 10.15309632 ),
	SSRE_Fixed_FromFloat( 13.55652859 ),
	SSRE_Fixed_FromFloat( 20.35513089 ),
	SSRE_Fixed_FromFloat( 40.73405540 ),
	SSRE_Fixed_FromFloat( 1098945.87019177 ),
	SSRE_Fixed_FromFloat( -40.73707718 ),
	SSRE_Fixed_FromFloat( -20.35588679 ),
	SSRE_Fixed_FromFloat( -13.55686489 ),
	SSRE_Fixed_FromFloat( -10.15328575 ),
	SSRE_Fixed_FromFloat( -8.10786308 ),
	SSRE_Fixed_FromFloat( -6.74150849 ),
	SSRE_Fixed_FromFloat( -5.76318501 ),
	SSRE_Fixed_FromFloat( -5.02737382 ),
	SSRE_Fixed_FromFloat( -4.45323048 ),
	SSRE_Fixed_FromFloat( -3.99224759 ),
	SSRE_Fixed_FromFloat( -3.61355614 ),
	SSRE_Fixed_FromFloat( -3.29657607 ),
	SSRE_Fixed_FromFloat( -3.02705900 ),
	SSRE_Fixed_FromFloat( -2.79482690 ),
	SSRE_Fixed_FromFloat( -2.59241528 ),
	SSRE_Fixed_FromFloat( -2.41422519 ),
	SSRE_Fixed_FromFloat( -2.25597452 ),
	SSRE_Fixed_FromFloat( -2.11433156 ),
	SSRE_Fixed_FromFloat( -1.98666677 ),
	SSRE_Fixed_FromFloat( -1.87087536 ),
	SSRE_Fixed_FromFloat( -1.76525294 ),
	SSRE_Fixed_FromFloat( -1.66840452 ),
	SSRE_Fixed_FromFloat( -1.57917723 ),
	SSRE_Fixed_FromFloat( -1.49660986 ),
	SSRE_Fixed_FromFloat( -1.41989451 ),
	SSRE_Fixed_FromFloat( -1.34834708 ),
	SSRE_Fixed_FromFloat( -1.28138437 ),
	SSRE_Fixed_FromFloat( -1.21850597 ),
	SSRE_Fixed_FromFloat( -1.15928005 ),
	SSRE_Fixed_FromFloat( -1.10333185 ),
	SSRE_Fixed_FromFloat( -1.05033448 ),
	SSRE_Fixed_FromFloat( -1.00000141 ),
	SSRE_Fixed_FromFloat( -0.95208036 ),
	SSRE_Fixed_FromFloat( -0.90634820 ),
	SSRE_Fixed_FromFloat( -0.86260680 ),
	SSRE_Fixed_FromFloat( -0.82067951 ),
	SSRE_Fixed_FromFloat( -0.78040824 ),
	SSRE_Fixed_FromFloat( -0.74165099 ),
	SSRE_Fixed_FromFloat( -0.70427979 ),
	SSRE_Fixed_FromFloat( -0.66817885 ),
	SSRE_Fixed_FromFloat( -0.63324313 ),
	SSRE_Fixed_FromFloat( -0.59937695 ),
	SSRE_Fixed_FromFloat( -0.56649292 ),
	SSRE_Fixed_FromFloat( -0.53451097 ),
	SSRE_Fixed_FromFloat( -0.50335745 ),
	SSRE_Fixed_FromFloat( -0.47296445 ),
	SSRE_Fixed_FromFloat( -0.44326911 ),
	SSRE_Fixed_FromFloat( -0.41421308 ),
	SSRE_Fixed_FromFloat( -0.38574202 ),
	SSRE_Fixed_FromFloat( -0.35780510 ),
	SSRE_Fixed_FromFloat( -0.33035469 ),
	SSRE_Fixed_FromFloat( -0.30334593 ),
	SSRE_Fixed_FromFloat( -0.27673646 ),
	SSRE_Fixed_FromFloat( -0.25048608 ),
	SSRE_Fixed_FromFloat( -0.22455657 ),
	SSRE_Fixed_FromFloat( -0.19891136 ),
	SSRE_Fixed_FromFloat( -0.17351539 ),
	SSRE_Fixed_FromFloat( -0.14833486 ),
	SSRE_Fixed_FromFloat( -0.12333704 ),
	SSRE_Fixed_FromFloat( -0.09849015 ),
	SSRE_Fixed_FromFloat( -0.07376311 ),
	SSRE_Fixed_FromFloat( -0.04912546 ),
	SSRE_Fixed_FromFloat( -0.02454717 ),
	SSRE_Fixed_FromFloat( 0.00000151 ),
	SSRE_Fixed_FromFloat( 0.02455021 ),
	SSRE_Fixed_FromFloat( 0.04912851 ),
	SSRE_Fixed_FromFloat( 0.07376616 ),
	SSRE_Fixed_FromFloat( 0.09849321 ),
	SSRE_Fixed_FromFloat( 0.12334013 ),
	SSRE_Fixed_FromFloat( 0.14833796 ),
	SSRE_Fixed_FromFloat( 0.17351852 ),
	SSRE_Fixed_FromFloat( 0.19891452 ),
	SSRE_Fixed_FromFloat( 0.22455976 ),
	SSRE_Fixed_FromFloat( 0.25048931 ),
	SSRE_Fixed_FromFloat( 0.27673972 ),
	SSRE_Fixed_FromFloat( 0.30334925 ),
	SSRE_Fixed_FromFloat( 0.33035806 ),
	SSRE_Fixed_FromFloat( 0.35780853 ),
	SSRE_Fixed_FromFloat( 0.38574550 ),
	SSRE_Fixed_FromFloat( 0.41421664 ),
	SSRE_Fixed_FromFloat( 0.44327274 ),
	SSRE_Fixed_FromFloat( 0.47296816 ),
	SSRE_Fixed_FromFloat( 0.50336125 ),
	SSRE_Fixed_FromFloat( 0.53451487 ),
	SSRE_Fixed_FromFloat( 0.56649693 ),
	SSRE_Fixed_FromFloat( 0.59938107 ),
	SSRE_Fixed_FromFloat( 0.63324738 ),
	SSRE_Fixed_FromFloat( 0.66818324 ),
	SSRE_Fixed_FromFloat( 0.70428433 ),
	SSRE_Fixed_FromFloat( 0.74165570 ),
	SSRE_Fixed_FromFloat( 0.78041312 ),
	SSRE_Fixed_FromFloat( 0.82068459 ),
	SSRE_Fixed_FromFloat( 0.86261210 ),
	SSRE_Fixed_FromFloat( 0.90635373 ),
	SSRE_Fixed_FromFloat( 0.95208615 ),
	SSRE_Fixed_FromFloat( 1.00000749 ),
	SSRE_Fixed_FromFloat( 1.05034086 ),
	SSRE_Fixed_FromFloat( 1.10333858 ),
	SSRE_Fixed_FromFloat( 1.15928661 ),
	SSRE_Fixed_FromFloat( 1.21851293 ),
	SSRE_Fixed_FromFloat( 1.28139176 ),
	SSRE_Fixed_FromFloat( 1.34835497 ),
	SSRE_Fixed_FromFloat( 1.41990294 ),
	SSRE_Fixed_FromFloat( 1.49661892 ),
	SSRE_Fixed_FromFloat( 1.57918700 ),
	SSRE_Fixed_FromFloat( 1.66841510 ),
	SSRE_Fixed_FromFloat( 1.76526445 ),
	SSRE_Fixed_FromFloat( 1.87088795 ),
	SSRE_Fixed_FromFloat( 1.98668061 ),
	SSRE_Fixed_FromFloat( 2.11434687 ),
	SSRE_Fixed_FromFloat( 2.25599156 ),
	SSRE_Fixed_FromFloat( 2.41424511 ),
	SSRE_Fixed_FromFloat( 2.59243872 ),
	SSRE_Fixed_FromFloat( 2.79485470 ),
	SSRE_Fixed_FromFloat( 3.02709228 ),
	SSRE_Fixed_FromFloat( 3.29661634 ),
	SSRE_Fixed_FromFloat( 3.61360552 ),
	SSRE_Fixed_FromFloat( 3.99230911 ),
	SSRE_Fixed_FromFloat( 4.45330862 ),
	SSRE_Fixed_FromFloat( 5.02747552 ),
	SSRE_Fixed_FromFloat( 5.76332152 ),
	SSRE_Fixed_FromFloat( 6.74169934 ),
	SSRE_Fixed_FromFloat( 8.10814525 ),
	SSRE_Fixed_FromFloat( 10.15373827 ),
	SSRE_Fixed_FromFloat( 13.55769027 ),
	SSRE_Fixed_FromFloat( 20.35779164 ),
	SSRE_Fixed_FromFloat( 40.74489104 ),
	SSRE_Fixed_FromFloat( -174399.21453213 ),
	SSRE_Fixed_FromFloat( -40.72585001 ),
	SSRE_Fixed_FromFloat( -20.35302852 ),
	SSRE_Fixed_FromFloat( -13.55557120 ),
	SSRE_Fixed_FromFloat( -10.15254461 ),
	SSRE_Fixed_FromFloat( -8.10737993 ),
	SSRE_Fixed_FromFloat( -6.74116669 ),
	SSRE_Fixed_FromFloat( -5.76292916 ),
	SSRE_Fixed_FromFloat( -5.02717421 ),
	SSRE_Fixed_FromFloat( -4.45306973 ),
	SSRE_Fixed_FromFloat( -3.99211487 ),
	SSRE_Fixed_FromFloat( -3.61344431 ),
	SSRE_Fixed_FromFloat( -3.29648025 ),
	SSRE_Fixed_FromFloat( -3.02697573 ),
	SSRE_Fixed_FromFloat( -2.79475366 ),
	SSRE_Fixed_FromFloat( -2.59235018 ),
	SSRE_Fixed_FromFloat( -2.41416680 ),
	SSRE_Fixed_FromFloat( -2.25592173 ),
	SSRE_Fixed_FromFloat( -2.11428413 ),
	SSRE_Fixed_FromFloat( -1.98662388 ),
	SSRE_Fixed_FromFloat( -1.87083634 ),
	SSRE_Fixed_FromFloat( -1.76521725 ),
	SSRE_Fixed_FromFloat( -1.66837171 ),
	SSRE_Fixed_FromFloat( -1.57914694 ),
	SSRE_Fixed_FromFloat( -1.49658177 ),
	SSRE_Fixed_FromFloat( -1.41986836 ),
	SSRE_Fixed_FromFloat( -1.34832265 ),
	SSRE_Fixed_FromFloat( -1.28136146 ),
	SSRE_Fixed_FromFloat( -1.21848443 ),
	SSRE_Fixed_FromFloat( -1.15925973 ),
	SSRE_Fixed_FromFloat( -1.10331263 ),
	SSRE_Fixed_FromFloat( -1.05031624 ),
	SSRE_Fixed_FromFloat( -0.99998407 ),
	SSRE_Fixed_FromFloat( -0.95206383 ),
	SSRE_Fixed_FromFloat( -0.90633241 ),
	SSRE_Fixed_FromFloat( -0.86259168 ),
	SSRE_Fixed_FromFloat( -0.82066500 ),
	SSRE_Fixed_FromFloat( -0.78039428 ),
	SSRE_Fixed_FromFloat( -0.74163755 ),
	SSRE_Fixed_FromFloat( -0.70426682 ),
	SSRE_Fixed_FromFloat( -0.66816631 ),
	SSRE_Fixed_FromFloat( -0.63323098 ),
	SSRE_Fixed_FromFloat( -0.59936516 ),
	SSRE_Fixed_FromFloat( -0.56648147 ),
	SSRE_Fixed_FromFloat( -0.53449982 ),
	SSRE_Fixed_FromFloat( -0.50334658 ),
	SSRE_Fixed_FromFloat( -0.47295384 ),
	SSRE_Fixed_FromFloat( -0.44325873 ),
	SSRE_Fixed_FromFloat( -0.41420293 ),
	SSRE_Fixed_FromFloat( -0.38573206 ),
	SSRE_Fixed_FromFloat( -0.35779532 ),
	SSRE_Fixed_FromFloat( -0.33034508 ),
	SSRE_Fixed_FromFloat( -0.30333646 ),
	SSRE_Fixed_FromFloat( -0.27672712 ),
	SSRE_Fixed_FromFloat( -0.25047687 ),
	SSRE_Fixed_FromFloat( -0.22454746 ),
	SSRE_Fixed_FromFloat( -0.19890235 ),
	SSRE_Fixed_FromFloat( -0.17350646 ),
	SSRE_Fixed_FromFloat( -0.14832600 ),
	SSRE_Fixed_FromFloat( -0.12332824 ),
	SSRE_Fixed_FromFloat( -0.09848139 ),
	SSRE_Fixed_FromFloat( -0.07375439 ),
	SSRE_Fixed_FromFloat( -0.04911677 ),
	SSRE_Fixed_FromFloat( -0.02453849 )
};

/**
 * Functions.
 */
SSRE_Fixed_t SSRE_Fixed_Mul( SSRE_Fixed_t lhs, SSRE_Fixed_t rhs )
{
	s64 value = (s64)lhs * (s64)rhs;
	return (SSRE_Fixed_t)( ( value ) >> SSRE_FIXED_PRECISION );
}

SSRE_Fixed_t SSRE_Fixed_FastMul( SSRE_Fixed_t lhs, SSRE_Fixed_t rhs )
{
	return ( lhs >> SSRE_FIXED_HALF_PRECISION ) * ( rhs >> SSRE_FIXED_HALF_PRECISION );
}

SSRE_Fixed_t SSRE_Fixed_Div( SSRE_Fixed_t lhs, SSRE_Fixed_t rhs )
{
	return (SSRE_Fixed_t)( ( ( (s64)lhs << SSRE_FIXED_DOUBLE_PRECISION ) / (s64)rhs ) >> SSRE_FIXED_PRECISION );
}

SSRE_Fixed_t SSRE_Fixed_Rcp( SSRE_Fixed_t lhs )
{
	return lhs != 0 ? SSRE_Fixed_Div( SSRE_FIXED_ONE, lhs ) : 0;
}

SSRE_Fixed_t SSRE_Fixed_Min2( SSRE_Fixed_t a, SSRE_Fixed_t b )
{
	return a < b ? a : b;
}

SSRE_Fixed_t SSRE_Fixed_Min3( SSRE_Fixed_t a, SSRE_Fixed_t b, SSRE_Fixed_t c )
{
	return SSRE_Fixed_Min2( SSRE_Fixed_Min2( a, b ), c );
}

SSRE_Fixed_t SSRE_Fixed_Max2( SSRE_Fixed_t a, SSRE_Fixed_t b )
{
	return a > b ? a : b;
}

SSRE_Fixed_t SSRE_Fixed_Max3( SSRE_Fixed_t a, SSRE_Fixed_t b, SSRE_Fixed_t c )
{
	return SSRE_Fixed_Max2( SSRE_Fixed_Max2( a, b ), c );
}

SSRE_Fixed_t SSRE_Fixed_Clamp( SSRE_Fixed_t val, SSRE_Fixed_t min, SSRE_Fixed_t max )
{
	return SSRE_Fixed_Min2( SSRE_Fixed_Max2( val, min ), max );
}

SSRE_Fixed_t SSRE_Fixed_Floor( SSRE_Fixed_t val )
{
	return val & ~( ( 1 << SSRE_FIXED_PRECISION ) - 1 );
}


SSRE_Fixed_t SSRE_Fixed_Sqrt( SSRE_Fixed_t lhs )
{
	register u64 v = lhs;
	register u64 x = v >> 1;
	register u64 a = 0;
	if( v > 0 && x != 0 )
	{
		do
		{
			a = ( ( v << SSRE_FIXED_DOUBLE_PRECISION ) / x ) >> SSRE_FIXED_PRECISION;
			x = ( ( ( x + a ) << SSRE_FIXED_DOUBLE_PRECISION ) / SSRE_FIXED_TWO ) >> SSRE_FIXED_PRECISION;
		}
		while( ( x * x ) > ( v << SSRE_FIXED_PRECISION ) );
		return (SSRE_Fixed_t)x;
	}

	return 0;
}

SSRE_Fixed_t SSRE_Fixed_Sin( int lhs )
{
	return s_SineTable[ lhs & 0xff ];
}

SSRE_Fixed_t SSRE_Fixed_Cos( int lhs )
{
	return s_SineTable[ ( lhs + 64 ) & 0xff ];
}

SSRE_Fixed_t SSRE_Fixed_Tan( int lhs )
{
	return s_TangentTable[ lhs & 0xff ];
}
