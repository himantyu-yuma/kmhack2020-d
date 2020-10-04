#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
 
const uint16_t kIrLed = 4;
IRsend irsend(kIrLed);
 

uint16_t turn_off[199] = {4386, 4442,  524, 1630,  524, 1630,  526, 552,  524, 552,  524, 552,  524, 554,  524, 1630,  524, 552,  524, 552,  524, 554,  524, 1630,  526, 1628,  526, 1628,  526, 1628,  524, 552,  524, 1630,  526, 552,  524, 1628,  524, 1630,  524, 1630,  524, 1630,  524, 554,  524, 1578,  574, 1580,  576, 1628,  524, 552,  524, 554,  524, 552,  524, 554,  522, 1630,  526, 552,  522, 554,  522, 1630,  524, 1630,  524, 1628,  524, 552,  524, 554,  522, 554,  524, 552,  524, 552,  524, 552,  524, 552,  524, 554,  524, 1630,  522, 1630,  524, 1630,  524, 1628,  524, 1578,  576, 5230,  4386, 4442,  524, 1630,  522, 1630,  524, 554,  522, 554,  522, 554,  524, 552,  522, 1632,  524, 554,  522, 554,  522, 554,  524, 1630,  524, 1578,  576, 1630,  524, 1630,  524, 554,  522, 1630,  522, 554,  522, 1630,  524, 1630,  524, 1630,  522, 1632,  526, 552,  522, 1630,  522, 1632,  522, 1584,  570, 554,  522, 554,  522, 554,  522, 554,  522, 1632,  524, 554,  522, 556,  520, 1632,  520, 1582,  574, 1582,  570, 556,  522, 554,  522, 554,  520, 556,  520, 556,  522, 556,  522, 554,  520, 556,  520, 1632,  522, 1632,  522, 1632,  522, 1578,  576, 1630,  522};  
uint16_t turn_on16[299]={4386, 4398,  570, 1630,  524, 1630,  526, 552,  522, 554,  522, 554,  522, 554,  520, 1632,  524, 552,  524, 554,  522, 554,  522, 1630,  526, 1628,  524, 1630,  526, 1630,  524, 552,  524, 1630,  526, 552,  522, 554,  522, 1630,  526, 1628,  524, 1630,  524, 1630,  524, 1630,  526, 1628,  526, 1628,  524, 1630,  526, 552,  524, 554,  522, 554,  522, 554,  522, 554,  522, 554,  522, 554,  524, 552,  524, 552,  522, 554,  522, 554,  522, 554,  522, 554,  522, 554,  522, 1630,  526, 1628,  526, 1628,  520, 1634,  524, 1630,  524, 1582,  572, 1580,  574, 1582,  572, 5230,  4388, 4440,  524, 1634,  520, 1630,  524, 552,  524, 554,  522, 554,  522, 554,  522, 1630,  526, 552,  524, 552,  522, 554,  522, 1630,  526, 1628,  526, 1584,  570, 1586,  568, 552,  524, 1628,  526, 552,  524, 554,  522, 1630,  524, 1630,  524, 1630,  524, 1630,  526, 1628,  526, 1628,  526, 1628,  526, 1630,  524, 552,  522, 554,  522, 554,  522, 554,  522, 556,  522, 556,  522, 554,  522, 554,  522, 554,  522, 556,  522, 554,  522, 556,  522, 554,  524, 554,  522, 1630,  526, 1628,  524, 1630,  524, 1630,  524, 1628,  526, 1628,  526, 1628,  524, 1630,  524, 5228,  4388, 4442,  524, 1628,  526, 1628,  524, 554,  522, 1630,  524, 554,  522, 1630,  526, 552,  522, 1630,  524, 554,  526, 1628,  524, 552,  522, 1632,  524, 552,  522, 554,  522, 556,  520, 556,  522, 554,  522, 554,  520, 556,  522, 556,  522, 554,  520, 556,  522, 554,  522, 554,  520, 556,  524, 554,  520, 556,  520, 1632,  524, 554,  522, 554,  522, 554,  520, 556,  522, 554,  522, 554,  520, 556,  520, 556,  520, 556,  520, 556,  522, 554,  524, 552,  520, 556,  520, 556,  520, 1632,  522, 1632,  524, 554,  522, 1630,  526, 552,  522, 1630,  524};  
uint16_t turn_on29[299]={4368, 4448, 584, 1572, 508, 1644, 508, 572, 584, 488, 508, 568, 588, 488, 588, 1564, 512, 564, 512, 568, 508, 568, 508, 1640, 512, 1640, 512, 1644, 512, 1640, 584, 492, 512, 1640, 512, 1640, 512, 564, 512, 1640, 512, 1640, 512, 1644, 508, 1644, 512, 1640, 512, 1636, 516, 564, 512, 1640, 512, 564, 512, 564, 512, 568, 508, 568, 508, 568, 508, 564, 516, 1636, 516, 564, 512, 1640, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 516, 560, 516, 1636, 516, 560, 516, 1640, 512, 1640, 512, 1640, 512, 1640, 512, 1640, 516, 5232, 4376, 4444, 596, 1560, 612, 1540, 644, 432, 608, 468, 616, 460, 624, 452, 624, 1528, 620, 456, 620, 460, 620, 456, 620, 1532, 624, 1528, 624, 1528, 620, 1532, 624, 452, 628, 1528, 624, 1528, 624, 452, 624, 1528, 628, 1524, 628, 1524, 664, 1488, 668, 1484, 668, 1484, 668, 412, 664, 1488, 668, 408, 668, 408, 668, 408, 668, 408, 668, 408, 668, 408, 668, 1484, 672, 408, 664, 1484, 672, 404, 672, 404, 672, 408, 668, 408, 672, 404, 672, 404, 672, 1484, 668, 404, 672, 1480, 676, 1476, 676, 1480, 672, 1480, 672, 1480, 676, 5072, 4536, 4284, 680, 1472, 680, 1472, 680, 396, 680, 1476, 676, 400, 680, 1472, 680, 396, 680, 1472, 672, 404, 672, 1480, 672, 1480, 604, 476, 672, 404, 600, 1552, 600, 1552, 600, 476, 604, 472, 604, 472, 604, 476, 600, 472, 604, 476, 600, 472, 604, 472, 604, 476, 600, 476, 600, 476, 600, 476, 600, 476, 600, 476, 600, 476, 600, 476, 604, 472, 604, 472, 604, 472, 604, 472, 604, 472, 604, 476, 600, 504, 572, 504, 572, 472, 604, 476, 600, 476, 600, 1580, 576, 1548, 600, 1552, 600, 476, 604, 1548, 604, 1552, 600};
uint16_t turn_on28[299]={4372, 4452, 512, 1592, 564, 1636, 516, 564, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 564, 516, 564, 508, 564, 512, 1640, 516, 1640, 512, 1640, 512, 1640, 512, 564, 512, 1640, 512, 1640, 512, 568, 508, 1644, 512, 1640, 512, 1640, 512, 1640, 512, 1640, 512, 1640, 512, 568, 512, 1640, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 568, 508, 1640, 512, 568, 512, 564, 512, 564, 512, 564, 516, 560, 512, 564, 516, 560, 516, 564, 508, 1640, 512, 1644, 512, 1640, 512, 1640, 512, 1640, 512, 1644, 508, 1644, 512, 5236, 4372, 4448, 512, 1592, 564, 1640, 508, 568, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 564, 436, 644, 508, 568, 508, 1640, 512, 1644, 512, 1640, 512, 1640, 512, 564, 512, 1640, 512, 1644, 512, 564, 512, 1640, 512, 1640, 436, 1716, 512, 1640, 512, 1644, 512, 1640, 512, 564, 512, 1552, 600, 568, 508, 568, 512, 564, 508, 568, 512, 564, 512, 564, 512, 1592, 560, 564, 512, 564, 512, 568, 508, 568, 512, 564, 512, 564, 512, 564, 436, 640, 512, 1640, 512, 1640, 512, 1644, 512, 1640, 512, 1640, 512, 1640, 512, 1640, 512, 5240, 4372, 4400, 560, 1596, 556, 1596, 556, 568, 512, 1592, 560, 564, 512, 1592, 560, 564, 512, 1640, 436, 644, 512, 1588, 564, 1588, 564, 564, 512, 564, 512, 1588, 564, 1596, 560, 564, 432, 644, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 568, 508, 568, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 516, 564, 508, 568, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 1592, 564, 1588, 564, 1588, 564, 564, 512, 1588, 564, 1588, 568};
uint16_t turn_on27[299]={4464, 4360, 600, 1640, 516, 1616, 536, 472, 604, 472, 604, 472, 604, 504, 572, 1552, 600, 504, 576, 472, 600, 476, 604, 1608, 544, 1548, 608, 1580, 568, 1552, 604, 472, 600, 1552, 604, 1548, 604, 500, 576, 1636, 520, 1548, 600, 1552, 600, 1552, 604, 1548, 604, 1636, 516, 560, 516, 1584, 572, 472, 604, 472, 604, 472, 604, 472, 604, 472, 604, 472, 604, 1552, 600, 476, 600, 476, 604, 1548, 604, 472, 604, 508, 568, 476, 600, 476, 600, 476, 600, 1552, 604, 1636, 516, 560, 516, 1548, 604, 1552, 600, 1552, 604, 1548, 604, 5232, 4376, 4360, 600, 1640, 516, 1548, 604, 472, 604, 476, 600, 472, 604, 508, 568, 1552, 604, 472, 604, 472, 600, 480, 600, 1548, 604, 1636, 516, 1552, 600, 1552, 600, 564, 512, 1552, 600, 1552, 604, 504, 572, 1552, 600, 1548, 604, 1552, 600, 1552, 600, 1640, 516, 1580, 572, 560, 516, 1640, 512, 476, 600, 476, 600, 564, 512, 564, 512, 476, 600, 476, 600, 1552, 604, 472, 604, 560, 516, 1636, 516, 476, 600, 472, 604, 472, 604, 564, 512, 564, 512, 1552, 604, 1636, 516, 560, 516, 1548, 608, 1544, 604, 1552, 600, 1640, 512, 5148, 4464, 4388, 572, 1548, 604, 1548, 604, 564, 512, 1584, 568, 476, 604, 1576, 572, 476, 604, 1548, 604, 472, 604, 1552, 600, 1552, 600, 476, 600, 512, 568, 1548, 604, 1548, 604, 472, 604, 476, 600, 476, 600, 476, 600, 476, 600, 476, 604, 472, 600, 476, 604, 472, 604, 472, 604, 472, 604, 472, 604, 472, 604, 472, 604, 472, 604, 504, 572, 476, 600, 508, 568, 508, 572, 472, 600, 476, 604, 472, 604, 472, 604, 472, 604, 476, 600, 476, 600, 476, 600, 1552, 600, 1552, 604, 1548, 604, 472, 604, 1548, 604, 1552, 600};
uint16_t turn_on26[299]={4372, 4448, 512, 1644, 508, 1640, 512, 568, 508, 568, 508, 568, 584, 492, 512, 1640, 512, 568, 512, 564, 580, 496, 508, 1640, 512, 1640, 512, 1644, 512, 1640, 512, 568, 508, 1644, 508, 1644, 580, 496, 508, 1644, 508, 1644, 512, 1640, 512, 1644, 508, 1644, 508, 1644, 512, 564, 512, 1640, 512, 568, 508, 568, 584, 492, 584, 492, 508, 568, 508, 568, 512, 1640, 512, 1644, 508, 568, 508, 1644, 508, 568, 584, 492, 508, 568, 512, 564, 588, 488, 584, 496, 508, 1640, 512, 568, 508, 1644, 508, 1644, 508, 1644, 512, 1640, 512, 5240, 4440, 4380, 508, 1644, 512, 1640, 512, 568, 508, 568, 584, 492, 508, 568, 508, 1644, 508, 568, 512, 568, 580, 492, 512, 1640, 512, 1640, 512, 1644, 508, 1640, 512, 568, 508, 1644, 508, 1644, 512, 564, 584, 1568, 588, 1564, 512, 1644, 508, 1644, 508, 1644, 512, 1640, 584, 492, 512, 1644, 508, 568, 508, 568, 508, 568, 508, 568, 512, 564, 508, 568, 512, 1640, 588, 1564, 512, 568, 584, 1568, 584, 492, 508, 568, 512, 564, 584, 496, 508, 564, 512, 568, 508, 1640, 588, 492, 508, 1644, 588, 1564, 512, 1640, 512, 1640, 588, 5164, 4444, 4376, 508, 1644, 512, 1640, 512, 568, 584, 1564, 512, 568, 508, 1644, 508, 568, 508, 1644, 516, 560, 584, 1568, 512, 1640, 512, 568, 508, 568, 584, 1568, 512, 1640, 584, 492, 512, 568, 508, 568, 580, 496, 508, 568, 508, 568, 512, 564, 512, 564, 584, 492, 512, 568, 508, 568, 584, 492, 508, 568, 584, 492, 508, 568, 512, 564, 584, 496, 508, 568, 580, 496, 584, 492, 584, 492, 584, 492, 508, 568, 584, 492, 512, 564, 588, 488, 512, 564, 588, 1564, 512, 1644, 512, 1640, 584, 492, 580, 1572, 584, 1568, 512};
uint16_t turn_on25[299]={4444, 4376, 512, 1640, 516, 1640, 508, 568, 512, 568, 508, 564, 512, 564, 512, 1640, 512, 564, 512, 564, 512, 568, 580, 1572, 508, 1644, 508, 1644, 508, 1640, 516, 564, 512, 1640, 588, 1564, 512, 568, 580, 1568, 584, 1572, 508, 1644, 508, 1644, 508, 1644, 588, 1564, 584, 492, 512, 1640, 512, 568, 508, 568, 508, 568, 508, 568, 508, 568, 508, 568, 512, 1640, 512, 1640, 512, 564, 584, 492, 512, 568, 508, 568, 508, 564, 512, 568, 508, 568, 508, 568, 508, 1644, 580, 1572, 512, 1640, 512, 1640, 588, 1564, 512, 1644, 580, 5168, 4368, 4452, 512, 1640, 512, 1640, 584, 492, 588, 492, 580, 496, 508, 568, 508, 1644, 512, 564, 512, 564, 512, 564, 512, 1640, 584, 1568, 512, 1644, 508, 1644, 508, 568, 568, 1584, 512, 1640, 512, 564, 512, 1640, 588, 1568, 512, 1640, 512, 1640, 512, 1640, 584, 1568, 584, 496, 580, 1568, 512, 568, 564, 512, 508, 568, 580, 496, 508, 568, 584, 492, 560, 1596, 584, 1564, 588, 492, 580, 496, 580, 496, 508, 568, 584, 492, 588, 488, 512, 564, 512, 564, 588, 1564, 588, 1568, 584, 1568, 508, 1644, 512, 1640, 588, 1564, 512, 5240, 4448, 4372, 584, 1568, 512, 1640, 588, 492, 508, 1644, 584, 492, 588, 1564, 584, 492, 588, 1564, 516, 564, 580, 1568, 592, 1564, 584, 492, 584, 492, 508, 1644, 588, 1564, 588, 492, 508, 568, 588, 488, 584, 492, 584, 492, 584, 492, 588, 488, 584, 492, 512, 564, 588, 488, 592, 488, 588, 484, 584, 496, 584, 492, 508, 568, 584, 492, 588, 488, 588, 488, 584, 492, 588, 488, 584, 492, 584, 496, 580, 492, 588, 492, 584, 488, 512, 568, 580, 496, 588, 1564, 584, 1568, 584, 1568, 584, 492, 588, 1564, 588, 1568, 588};
uint16_t turn_on24[299]={4384, 4448, 512, 1640, 516, 1636, 516, 564, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 564, 516, 560, 512, 564, 512, 1644, 512, 1640, 512, 1640, 512, 1640, 512, 564, 512, 1640, 512, 1640, 512, 568, 508, 1644, 512, 1640, 512, 1640, 512, 1592, 560, 1640, 512, 1640, 512, 568, 512, 1640, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 568, 508, 568, 512, 564, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 564, 512, 1640, 512, 1640, 512, 1640, 512, 1644, 512, 1640, 512, 1640, 512, 5236, 4372, 4448, 512, 1640, 516, 1588, 564, 564, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 1604, 548, 1644, 512, 1640, 512, 564, 512, 1640, 512, 1588, 564, 564, 512, 1588, 564, 1640, 436, 1716, 516, 1640, 512, 1640, 512, 1640, 512, 564, 508, 1644, 512, 564, 512, 568, 508, 568, 512, 564, 512, 564, 512, 564, 512, 564, 512, 1588, 564, 564, 512, 564, 512, 564, 512, 564, 516, 564, 508, 568, 512, 1584, 568, 564, 512, 1588, 564, 1588, 564, 1588, 564, 1592, 564, 1584, 568, 1592, 560, 5184, 4424, 4396, 564, 1588, 568, 1584, 568, 564, 512, 1588, 564, 564, 512, 1588, 564, 564, 512, 1592, 560, 564, 512, 1584, 568, 1588, 564, 568, 512, 564, 512, 1584, 568, 1584, 568, 564, 504, 572, 512, 524, 552, 524, 552, 524, 552, 524, 552, 540, 536, 544, 532, 524, 552, 568, 512, 540, 536, 540, 536, 524, 552, 520, 556, 520, 556, 564, 512, 528, 548, 564, 512, 524, 552, 524, 552, 524, 552, 532, 548, 528, 548, 540, 536, 520, 556, 520, 556, 524, 552, 1584, 568, 1588, 568, 1584, 568, 520, 552, 1588, 568, 1584, 568}; 
uint16_t turn_on23[299]={4424, 4392, 568, 1588, 564, 1592, 560, 520, 556, 528, 548, 528, 548, 540, 536, 1588, 568, 516, 556, 532, 544, 544, 532, 1588, 568, 1584, 568, 1584, 568, 1584, 572, 516, 556, 1592, 564, 1592, 560, 516, 556, 1552, 604, 1588, 568, 1580, 572, 1580, 572, 1584, 568, 1588, 564, 520, 552, 1600, 556, 524, 552, 540, 536, 540, 536, 524, 552, 544, 532, 544, 460, 616, 532, 1588, 568, 540, 536, 1584, 568, 540, 536, 540, 536, 540, 536, 540, 536, 1588, 568, 536, 536, 1588, 568, 540, 532, 1552, 604, 1584, 568, 1584, 572, 1584, 568, 5180, 4428, 4396, 564, 1580, 572, 1584, 568, 540, 536, 524, 552, 540, 536, 548, 528, 1592, 564, 528, 548, 544, 528, 528, 548, 1588, 568, 1584, 568, 1588, 564, 1584, 568, 540, 536, 1588, 568, 1580, 572, 516, 560, 1584, 568, 1584, 572, 1580, 568, 1584, 572, 1584, 568, 1584, 568, 524, 548, 1588, 568, 540, 536, 540, 536, 540, 536, 540, 536, 548, 528, 548, 528, 544, 532, 1588, 568, 540, 536, 1588, 564, 540, 536, 540, 536, 540, 536, 544, 536, 1584, 568, 540, 532, 1588, 568, 524, 552, 1584, 568, 1588, 568, 1584, 568, 1584, 568, 5176, 4432, 4392, 568, 1588, 564, 1588, 564, 524, 552, 1588, 568, 540, 532, 1592, 564, 540, 536, 1584, 572, 536, 536, 1588, 568, 1592, 560, 540, 532, 544, 532, 1588, 568, 1588, 564, 540, 536, 544, 532, 548, 528, 544, 532, 544, 532, 548, 528, 544, 532, 544, 532, 528, 552, 540, 532, 544, 532, 552, 524, 552, 524, 544, 536, 524, 548, 548, 532, 544, 532, 544, 532, 544, 532, 544, 532, 544, 532, 552, 524, 544, 532, 544, 532, 544, 532, 552, 524, 552, 524, 1588, 568, 1588, 568, 1584, 564, 544, 532, 1592, 560, 1588, 568};
uint16_t turn_on22[299]={4372, 4452, 512, 1640, 516, 1584, 564, 564, 512, 568, 508, 568, 508, 568, 512, 1640, 512, 564, 512, 564, 512, 564, 512, 1640, 512, 1640, 516, 1640, 512, 1592, 560, 564, 512, 1640, 512, 1640, 512, 568, 508, 1644, 508, 1596, 560, 1640, 512, 1640, 512, 1640, 512, 1640, 512, 568, 512, 1640, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 568, 508, 1640, 512, 1588, 564, 1644, 512, 564, 512, 564, 512, 564, 512, 564, 512, 1588, 564, 564, 512, 568, 508, 564, 512, 1592, 564, 1584, 568, 1588, 564, 1588, 564, 5188, 4420, 4392, 568, 1588, 568, 1584, 568, 564, 512, 564, 512, 564, 512, 564, 512, 1592, 560, 568, 504, 572, 508, 568, 512, 1584, 568, 1588, 564, 1588, 564, 1592, 560, 568, 508, 1592, 564, 1588, 564, 564, 512, 1584, 568, 1592, 556, 1588, 572, 1584, 568, 1592, 560, 1584, 568, 564, 512, 1588, 568, 564, 512, 540, 536, 564, 512, 524, 552, 564, 512, 564, 512, 564, 512, 1584, 568, 1588, 568, 1584, 568, 564, 512, 524, 552, 528, 548, 564, 512, 1588, 568, 564, 512, 524, 552, 520, 556, 1588, 564, 1584, 568, 1588, 564, 1592, 564, 5188, 4420, 4396, 568, 1588, 564, 1584, 568, 520, 556, 1588, 564, 524, 552, 1588, 568, 528, 548, 1588, 484, 644, 512, 1588, 564, 1588, 564, 568, 512, 536, 540, 1588, 564, 1584, 568, 540, 536, 540, 536, 524, 552, 520, 556, 520, 556, 544, 536, 524, 552, 520, 556, 520, 556, 532, 544, 524, 552, 540, 536, 524, 552, 540, 536, 528, 548, 528, 548, 528, 552, 520, 556, 540, 536, 524, 552, 540, 536, 520, 556, 528, 548, 540, 536, 524, 552, 528, 548, 532, 548, 1584, 568, 1584, 568, 1588, 564, 520, 556, 1584, 572, 1588, 564};
uint16_t turn_on21[299]={4424, 4396, 564, 1596, 556, 1552, 600, 520, 556, 568, 508, 540, 536, 544, 532, 1588, 568, 520, 552, 568, 508, 544, 532, 1588, 568, 1588, 564, 1588, 564, 1588, 564, 540, 536, 1552, 604, 1584, 568, 520, 552, 1588, 568, 1584, 568, 1588, 564, 1588, 564, 1592, 564, 1584, 568, 524, 548, 1588, 568, 520, 556, 540, 532, 524, 556, 520, 556, 564, 512, 564, 512, 564, 512, 1592, 560, 1584, 568, 568, 508, 540, 536, 544, 532, 568, 512, 524, 548, 1588, 568, 540, 536, 524, 552, 1548, 604, 1588, 564, 1588, 564, 1584, 572, 1592, 560, 5184, 4424, 4392, 568, 1592, 560, 1588, 564, 564, 512, 564, 512, 524, 556, 564, 512, 1584, 568, 564, 512, 564, 512, 564, 512, 1588, 564, 1548, 604, 1592, 560, 1588, 564, 564, 512, 1588, 564, 1588, 568, 564, 512, 1588, 564, 1640, 436, 1624, 604, 1588, 564, 1592, 560, 1640, 512, 568, 508, 1596, 556, 568, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 508, 1644, 512, 1640, 512, 564, 512, 568, 508, 568, 512, 564, 508, 568, 512, 1640, 508, 568, 512, 564, 512, 1640, 512, 1640, 512, 1640, 512, 1640, 512, 1592, 560, 5240, 4368, 4452, 512, 1640, 512, 1640, 512, 564, 512, 1640, 512, 564, 512, 1644, 508, 568, 508, 1644, 508, 568, 508, 1644, 512, 1640, 512, 564, 512, 564, 512, 1640, 512, 1640, 512, 568, 508, 568, 512, 564, 508, 568, 512, 564, 512, 564, 436, 640, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 568, 504, 572, 508, 568, 508, 568, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 564, 512, 1592, 560, 1592, 484, 1668, 564, 564, 512, 1584, 568, 1588, 564};
 

void setup() {

  pinMode(4, OUTPUT); 
  

  irsend.begin();
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("Start IRsend");
  delay(10000);
}
 
void loop() {
 // Serial.println("ON");

  byte var = Serial.read();
 
   
switch (var) {
    case 'o':
   irsend.sendRaw(turn_off, 199, 38);  
   break;
   
    case 's':
    irsend.sendRaw(turn_on16, 299, 38);  
     Serial.println("The current temperature is 16 degrees.");
     break;
     
    case '9':
   irsend.sendRaw(turn_on29, 299, 38);  
   Serial.println("The current temperature is 29 degrees.");
    break;
    
    case '8':
   irsend.sendRaw(turn_on28, 299, 38); 
   Serial.println("The current temperature is 28 degrees.");
   break;
   
   case '7':
   irsend.sendRaw(turn_on27, 299, 38);  
   Serial.println("The current temperature is 27 degrees.");
    break;
    
   case '6':
   irsend.sendRaw(turn_on26, 299, 38); 
   Serial.println("The current temperature is 26 degrees.");
   break;
   
   case '5':
   irsend.sendRaw(turn_on25, 299, 38); 
   Serial.println("The current temperature is 25 degrees.");
    break;
    
    case '4':
   irsend.sendRaw(turn_on24, 299, 38); 
   Serial.println("The current temperature is 24 degrees.");
    break;
    
    case '3':
   irsend.sendRaw(turn_on23, 299, 38); 
   Serial.println("The current temperature is 23 degrees.");
    break;

   case '2':
   irsend.sendRaw(turn_on23, 299, 38); 
   Serial.println("The current temperature is 23 degrees.");
    break;
}
    delay(1000); 

    
 
  }
  
