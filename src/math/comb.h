//
// BAGEL - Parallel electron correlation program.
// Filename: comb.h
// Copyright (C) 2011 Toru Shiozaki
//
// Author: Toru Shiozaki <shiozaki@northwestern.edu>
// Maintainer: Shiozaki group
//
// This file is part of the BAGEL package.
//
// The BAGEL package is free software; you can redistribute it and/or modify
// it under the terms of the GNU Library General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// The BAGEL package is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public License
// along with the BAGEL package; see COPYING.  If not, write to
// the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
//

//

#ifndef __BAGEL_UTIL_COMB_H
#define __BAGEL_UTIL_COMB_H

#include <algorithm>
#include <array>
#include <cassert>

namespace bagel {

class Comb {
    constexpr static int max_ = 32;
    std::array<unsigned long, max_*max_> c_;
  public:
    Comb() {
      std::fill(c_.begin(), c_.end(), 0U);
      c_[0*max_+0] = 1;
      c_[1*max_+0] = 1;
      c_[1*max_+1] = 1;
      c_[2*max_+0] = 1;
      c_[2*max_+1] = 2;
      c_[2*max_+2] = 1;
      c_[3*max_+0] = 1;
      c_[3*max_+1] = 3;
      c_[3*max_+2] = 3;
      c_[3*max_+3] = 1;
      c_[4*max_+0] = 1;
      c_[4*max_+1] = 4;
      c_[4*max_+2] = 6;
      c_[4*max_+3] = 4;
      c_[4*max_+4] = 1;
      c_[5*max_+0] = 1;
      c_[5*max_+1] = 5;
      c_[5*max_+2] = 10;
      c_[5*max_+3] = 10;
      c_[5*max_+4] = 5;
      c_[5*max_+5] = 1;
      c_[6*max_+0] = 1;
      c_[6*max_+1] = 6;
      c_[6*max_+2] = 15;
      c_[6*max_+3] = 20;
      c_[6*max_+4] = 15;
      c_[6*max_+5] = 6;
      c_[6*max_+6] = 1;
      c_[7*max_+0] = 1;
      c_[7*max_+1] = 7;
      c_[7*max_+2] = 21;
      c_[7*max_+3] = 35;
      c_[7*max_+4] = 35;
      c_[7*max_+5] = 21;
      c_[7*max_+6] = 7;
      c_[7*max_+7] = 1;
      c_[8*max_+0] = 1;
      c_[8*max_+1] = 8;
      c_[8*max_+2] = 28;
      c_[8*max_+3] = 56;
      c_[8*max_+4] = 70;
      c_[8*max_+5] = 56;
      c_[8*max_+6] = 28;
      c_[8*max_+7] = 8;
      c_[8*max_+8] = 1;
      c_[9*max_+0] = 1;
      c_[9*max_+1] = 9;
      c_[9*max_+2] = 36;
      c_[9*max_+3] = 84;
      c_[9*max_+4] = 126;
      c_[9*max_+5] = 126;
      c_[9*max_+6] = 84;
      c_[9*max_+7] = 36;
      c_[9*max_+8] = 9;
      c_[9*max_+9] = 1;
      c_[10*max_+0] = 1;
      c_[10*max_+1] = 10;
      c_[10*max_+2] = 45;
      c_[10*max_+3] = 120;
      c_[10*max_+4] = 210;
      c_[10*max_+5] = 252;
      c_[10*max_+6] = 210;
      c_[10*max_+7] = 120;
      c_[10*max_+8] = 45;
      c_[10*max_+9] = 10;
      c_[10*max_+10] = 1;
      c_[11*max_+0] = 1;
      c_[11*max_+1] = 11;
      c_[11*max_+2] = 55;
      c_[11*max_+3] = 165;
      c_[11*max_+4] = 330;
      c_[11*max_+5] = 462;
      c_[11*max_+6] = 462;
      c_[11*max_+7] = 330;
      c_[11*max_+8] = 165;
      c_[11*max_+9] = 55;
      c_[11*max_+10] = 11;
      c_[11*max_+11] = 1;
      c_[12*max_+0] = 1;
      c_[12*max_+1] = 12;
      c_[12*max_+2] = 66;
      c_[12*max_+3] = 220;
      c_[12*max_+4] = 495;
      c_[12*max_+5] = 792;
      c_[12*max_+6] = 924;
      c_[12*max_+7] = 792;
      c_[12*max_+8] = 495;
      c_[12*max_+9] = 220;
      c_[12*max_+10] = 66;
      c_[12*max_+11] = 12;
      c_[12*max_+12] = 1;
      c_[13*max_+0] = 1;
      c_[13*max_+1] = 13;
      c_[13*max_+2] = 78;
      c_[13*max_+3] = 286;
      c_[13*max_+4] = 715;
      c_[13*max_+5] = 1287;
      c_[13*max_+6] = 1716;
      c_[13*max_+7] = 1716;
      c_[13*max_+8] = 1287;
      c_[13*max_+9] = 715;
      c_[13*max_+10] = 286;
      c_[13*max_+11] = 78;
      c_[13*max_+12] = 13;
      c_[13*max_+13] = 1;
      c_[14*max_+0] = 1;
      c_[14*max_+1] = 14;
      c_[14*max_+2] = 91;
      c_[14*max_+3] = 364;
      c_[14*max_+4] = 1001;
      c_[14*max_+5] = 2002;
      c_[14*max_+6] = 3003;
      c_[14*max_+7] = 3432;
      c_[14*max_+8] = 3003;
      c_[14*max_+9] = 2002;
      c_[14*max_+10] = 1001;
      c_[14*max_+11] = 364;
      c_[14*max_+12] = 91;
      c_[14*max_+13] = 14;
      c_[14*max_+14] = 1;
      c_[15*max_+0] = 1;
      c_[15*max_+1] = 15;
      c_[15*max_+2] = 105;
      c_[15*max_+3] = 455;
      c_[15*max_+4] = 1365;
      c_[15*max_+5] = 3003;
      c_[15*max_+6] = 5005;
      c_[15*max_+7] = 6435;
      c_[15*max_+8] = 6435;
      c_[15*max_+9] = 5005;
      c_[15*max_+10] = 3003;
      c_[15*max_+11] = 1365;
      c_[15*max_+12] = 455;
      c_[15*max_+13] = 105;
      c_[15*max_+14] = 15;
      c_[15*max_+15] = 1;
      c_[16*max_+0] = 1;
      c_[16*max_+1] = 16;
      c_[16*max_+2] = 120;
      c_[16*max_+3] = 560;
      c_[16*max_+4] = 1820;
      c_[16*max_+5] = 4368;
      c_[16*max_+6] = 8008;
      c_[16*max_+7] = 11440;
      c_[16*max_+8] = 12870;
      c_[16*max_+9] = 11440;
      c_[16*max_+10] = 8008;
      c_[16*max_+11] = 4368;
      c_[16*max_+12] = 1820;
      c_[16*max_+13] = 560;
      c_[16*max_+14] = 120;
      c_[16*max_+15] = 16;
      c_[16*max_+16] = 1;
      c_[17*max_+0] = 1;
      c_[17*max_+1] = 17;
      c_[17*max_+2] = 136;
      c_[17*max_+3] = 680;
      c_[17*max_+4] = 2380;
      c_[17*max_+5] = 6188;
      c_[17*max_+6] = 12376;
      c_[17*max_+7] = 19448;
      c_[17*max_+8] = 24310;
      c_[17*max_+9] = 24310;
      c_[17*max_+10] = 19448;
      c_[17*max_+11] = 12376;
      c_[17*max_+12] = 6188;
      c_[17*max_+13] = 2380;
      c_[17*max_+14] = 680;
      c_[17*max_+15] = 136;
      c_[17*max_+16] = 17;
      c_[17*max_+17] = 1;
      c_[18*max_+0] = 1;
      c_[18*max_+1] = 18;
      c_[18*max_+2] = 153;
      c_[18*max_+3] = 816;
      c_[18*max_+4] = 3060;
      c_[18*max_+5] = 8568;
      c_[18*max_+6] = 18564;
      c_[18*max_+7] = 31824;
      c_[18*max_+8] = 43758;
      c_[18*max_+9] = 48620;
      c_[18*max_+10] = 43758;
      c_[18*max_+11] = 31824;
      c_[18*max_+12] = 18564;
      c_[18*max_+13] = 8568;
      c_[18*max_+14] = 3060;
      c_[18*max_+15] = 816;
      c_[18*max_+16] = 153;
      c_[18*max_+17] = 18;
      c_[18*max_+18] = 1;
      c_[19*max_+0] = 1;
      c_[19*max_+1] = 19;
      c_[19*max_+2] = 171;
      c_[19*max_+3] = 969;
      c_[19*max_+4] = 3876;
      c_[19*max_+5] = 11628;
      c_[19*max_+6] = 27132;
      c_[19*max_+7] = 50388;
      c_[19*max_+8] = 75582;
      c_[19*max_+9] = 92378;
      c_[19*max_+10] = 92378;
      c_[19*max_+11] = 75582;
      c_[19*max_+12] = 50388;
      c_[19*max_+13] = 27132;
      c_[19*max_+14] = 11628;
      c_[19*max_+15] = 3876;
      c_[19*max_+16] = 969;
      c_[19*max_+17] = 171;
      c_[19*max_+18] = 19;
      c_[19*max_+19] = 1;
      c_[20*max_+0] = 1;
      c_[20*max_+1] = 20;
      c_[20*max_+2] = 190;
      c_[20*max_+3] = 1140;
      c_[20*max_+4] = 4845;
      c_[20*max_+5] = 15504;
      c_[20*max_+6] = 38760;
      c_[20*max_+7] = 77520;
      c_[20*max_+8] = 125970;
      c_[20*max_+9] = 167960;
      c_[20*max_+10] = 184756;
      c_[20*max_+11] = 167960;
      c_[20*max_+12] = 125970;
      c_[20*max_+13] = 77520;
      c_[20*max_+14] = 38760;
      c_[20*max_+15] = 15504;
      c_[20*max_+16] = 4845;
      c_[20*max_+17] = 1140;
      c_[20*max_+18] = 190;
      c_[20*max_+19] = 20;
      c_[20*max_+20] = 1;
      c_[21*max_+0] = 1;
      c_[21*max_+1] = 21;
      c_[21*max_+2] = 210;
      c_[21*max_+3] = 1330;
      c_[21*max_+4] = 5985;
      c_[21*max_+5] = 20349;
      c_[21*max_+6] = 54264;
      c_[21*max_+7] = 116280;
      c_[21*max_+8] = 203490;
      c_[21*max_+9] = 293930;
      c_[21*max_+10] = 352716;
      c_[21*max_+11] = 352716;
      c_[21*max_+12] = 293930;
      c_[21*max_+13] = 203490;
      c_[21*max_+14] = 116280;
      c_[21*max_+15] = 54264;
      c_[21*max_+16] = 20349;
      c_[21*max_+17] = 5985;
      c_[21*max_+18] = 1330;
      c_[21*max_+19] = 210;
      c_[21*max_+20] = 21;
      c_[21*max_+21] = 1;
      c_[22*max_+0] = 1;
      c_[22*max_+1] = 22;
      c_[22*max_+2] = 231;
      c_[22*max_+3] = 1540;
      c_[22*max_+4] = 7315;
      c_[22*max_+5] = 26334;
      c_[22*max_+6] = 74613;
      c_[22*max_+7] = 170544;
      c_[22*max_+8] = 319770;
      c_[22*max_+9] = 497420;
      c_[22*max_+10] = 646646;
      c_[22*max_+11] = 705432;
      c_[22*max_+12] = 646646;
      c_[22*max_+13] = 497420;
      c_[22*max_+14] = 319770;
      c_[22*max_+15] = 170544;
      c_[22*max_+16] = 74613;
      c_[22*max_+17] = 26334;
      c_[22*max_+18] = 7315;
      c_[22*max_+19] = 1540;
      c_[22*max_+20] = 231;
      c_[22*max_+21] = 22;
      c_[22*max_+22] = 1;
      c_[23*max_+0] = 1;
      c_[23*max_+1] = 23;
      c_[23*max_+2] = 253;
      c_[23*max_+3] = 1771;
      c_[23*max_+4] = 8855;
      c_[23*max_+5] = 33649;
      c_[23*max_+6] = 100947;
      c_[23*max_+7] = 245157;
      c_[23*max_+8] = 490314;
      c_[23*max_+9] = 817190;
      c_[23*max_+10] = 1144066;
      c_[23*max_+11] = 1352078;
      c_[23*max_+12] = 1352078;
      c_[23*max_+13] = 1144066;
      c_[23*max_+14] = 817190;
      c_[23*max_+15] = 490314;
      c_[23*max_+16] = 245157;
      c_[23*max_+17] = 100947;
      c_[23*max_+18] = 33649;
      c_[23*max_+19] = 8855;
      c_[23*max_+20] = 1771;
      c_[23*max_+21] = 253;
      c_[23*max_+22] = 23;
      c_[23*max_+23] = 1;
      c_[24*max_+0] = 1;
      c_[24*max_+1] = 24;
      c_[24*max_+2] = 276;
      c_[24*max_+3] = 2024;
      c_[24*max_+4] = 10626;
      c_[24*max_+5] = 42504;
      c_[24*max_+6] = 134596;
      c_[24*max_+7] = 346104;
      c_[24*max_+8] = 735471;
      c_[24*max_+9] = 1307504;
      c_[24*max_+10] = 1961256;
      c_[24*max_+11] = 2496144;
      c_[24*max_+12] = 2704156;
      c_[24*max_+13] = 2496144;
      c_[24*max_+14] = 1961256;
      c_[24*max_+15] = 1307504;
      c_[24*max_+16] = 735471;
      c_[24*max_+17] = 346104;
      c_[24*max_+18] = 134596;
      c_[24*max_+19] = 42504;
      c_[24*max_+20] = 10626;
      c_[24*max_+21] = 2024;
      c_[24*max_+22] = 276;
      c_[24*max_+23] = 24;
      c_[24*max_+24] = 1;
      c_[25*max_+0] = 1;
      c_[25*max_+1] = 25;
      c_[25*max_+2] = 300;
      c_[25*max_+3] = 2300;
      c_[25*max_+4] = 12650;
      c_[25*max_+5] = 53130;
      c_[25*max_+6] = 177100;
      c_[25*max_+7] = 480700;
      c_[25*max_+8] = 1081575;
      c_[25*max_+9] = 2042975;
      c_[25*max_+10] = 3268760;
      c_[25*max_+11] = 4457400;
      c_[25*max_+12] = 5200300;
      c_[25*max_+13] = 5200300;
      c_[25*max_+14] = 4457400;
      c_[25*max_+15] = 3268760;
      c_[25*max_+16] = 2042975;
      c_[25*max_+17] = 1081575;
      c_[25*max_+18] = 480700;
      c_[25*max_+19] = 177100;
      c_[25*max_+20] = 53130;
      c_[25*max_+21] = 12650;
      c_[25*max_+22] = 2300;
      c_[25*max_+23] = 300;
      c_[25*max_+24] = 25;
      c_[25*max_+25] = 1;
      c_[26*max_+0] = 1;
      c_[26*max_+1] = 26;
      c_[26*max_+2] = 325;
      c_[26*max_+3] = 2600;
      c_[26*max_+4] = 14950;
      c_[26*max_+5] = 65780;
      c_[26*max_+6] = 230230;
      c_[26*max_+7] = 657800;
      c_[26*max_+8] = 1562275;
      c_[26*max_+9] = 3124550;
      c_[26*max_+10] = 5311735;
      c_[26*max_+11] = 7726160;
      c_[26*max_+12] = 9657700;
      c_[26*max_+13] = 10400600;
      c_[26*max_+14] = 9657700;
      c_[26*max_+15] = 7726160;
      c_[26*max_+16] = 5311735;
      c_[26*max_+17] = 3124550;
      c_[26*max_+18] = 1562275;
      c_[26*max_+19] = 657800;
      c_[26*max_+20] = 230230;
      c_[26*max_+21] = 65780;
      c_[26*max_+22] = 14950;
      c_[26*max_+23] = 2600;
      c_[26*max_+24] = 325;
      c_[26*max_+25] = 26;
      c_[26*max_+26] = 1;
      c_[27*max_+0] = 1;
      c_[27*max_+1] = 27;
      c_[27*max_+2] = 351;
      c_[27*max_+3] = 2925;
      c_[27*max_+4] = 17550;
      c_[27*max_+5] = 80730;
      c_[27*max_+6] = 296010;
      c_[27*max_+7] = 888030;
      c_[27*max_+8] = 2220075;
      c_[27*max_+9] = 4686825;
      c_[27*max_+10] = 8436285;
      c_[27*max_+11] = 13037895;
      c_[27*max_+12] = 17383860;
      c_[27*max_+13] = 20058300;
      c_[27*max_+14] = 20058300;
      c_[27*max_+15] = 17383860;
      c_[27*max_+16] = 13037895;
      c_[27*max_+17] = 8436285;
      c_[27*max_+18] = 4686825;
      c_[27*max_+19] = 2220075;
      c_[27*max_+20] = 888030;
      c_[27*max_+21] = 296010;
      c_[27*max_+22] = 80730;
      c_[27*max_+23] = 17550;
      c_[27*max_+24] = 2925;
      c_[27*max_+25] = 351;
      c_[27*max_+26] = 27;
      c_[27*max_+27] = 1;
      c_[28*max_+0] = 1;
      c_[28*max_+1] = 28;
      c_[28*max_+2] = 378;
      c_[28*max_+3] = 3276;
      c_[28*max_+4] = 20475;
      c_[28*max_+5] = 98280;
      c_[28*max_+6] = 376740;
      c_[28*max_+7] = 1184040;
      c_[28*max_+8] = 3108105;
      c_[28*max_+9] = 6906900;
      c_[28*max_+10] = 13123110;
      c_[28*max_+11] = 21474180;
      c_[28*max_+12] = 30421755;
      c_[28*max_+13] = 37442160;
      c_[28*max_+14] = 40116600;
      c_[28*max_+15] = 37442160;
      c_[28*max_+16] = 30421755;
      c_[28*max_+17] = 21474180;
      c_[28*max_+18] = 13123110;
      c_[28*max_+19] = 6906900;
      c_[28*max_+20] = 3108105;
      c_[28*max_+21] = 1184040;
      c_[28*max_+22] = 376740;
      c_[28*max_+23] = 98280;
      c_[28*max_+24] = 20475;
      c_[28*max_+25] = 3276;
      c_[28*max_+26] = 378;
      c_[28*max_+27] = 28;
      c_[28*max_+28] = 1;
      c_[29*max_+0] = 1;
      c_[29*max_+1] = 29;
      c_[29*max_+2] = 406;
      c_[29*max_+3] = 3654;
      c_[29*max_+4] = 23751;
      c_[29*max_+5] = 118755;
      c_[29*max_+6] = 475020;
      c_[29*max_+7] = 1560780;
      c_[29*max_+8] = 4292145;
      c_[29*max_+9] = 10015005;
      c_[29*max_+10] = 20030010;
      c_[29*max_+11] = 34597290;
      c_[29*max_+12] = 51895935;
      c_[29*max_+13] = 67863915;
      c_[29*max_+14] = 77558760;
      c_[29*max_+15] = 77558760;
      c_[29*max_+16] = 67863915;
      c_[29*max_+17] = 51895935;
      c_[29*max_+18] = 34597290;
      c_[29*max_+19] = 20030010;
      c_[29*max_+20] = 10015005;
      c_[29*max_+21] = 4292145;
      c_[29*max_+22] = 1560780;
      c_[29*max_+23] = 475020;
      c_[29*max_+24] = 118755;
      c_[29*max_+25] = 23751;
      c_[29*max_+26] = 3654;
      c_[29*max_+27] = 406;
      c_[29*max_+28] = 29;
      c_[29*max_+29] = 1;
      c_[30*max_+0] = 1;
      c_[30*max_+1] = 30;
      c_[30*max_+2] = 435;
      c_[30*max_+3] = 4060;
      c_[30*max_+4] = 27405;
      c_[30*max_+5] = 142506;
      c_[30*max_+6] = 593775;
      c_[30*max_+7] = 2035800;
      c_[30*max_+8] = 5852925;
      c_[30*max_+9] = 14307150;
      c_[30*max_+10] = 30045015;
      c_[30*max_+11] = 54627300;
      c_[30*max_+12] = 86493225;
      c_[30*max_+13] = 119759850;
      c_[30*max_+14] = 145422675;
      c_[30*max_+15] = 155117520;
      c_[30*max_+16] = 145422675;
      c_[30*max_+17] = 119759850;
      c_[30*max_+18] = 86493225;
      c_[30*max_+19] = 54627300;
      c_[30*max_+20] = 30045015;
      c_[30*max_+21] = 14307150;
      c_[30*max_+22] = 5852925;
      c_[30*max_+23] = 2035800;
      c_[30*max_+24] = 593775;
      c_[30*max_+25] = 142506;
      c_[30*max_+26] = 27405;
      c_[30*max_+27] = 4060;
      c_[30*max_+28] = 435;
      c_[30*max_+29] = 30;
      c_[30*max_+30] = 1;
      c_[31*max_+0] = 1;
      c_[31*max_+1] = 31;
      c_[31*max_+2] = 465;
      c_[31*max_+3] = 4495;
      c_[31*max_+4] = 31465;
      c_[31*max_+5] = 169911;
      c_[31*max_+6] = 736281;
      c_[31*max_+7] = 2629575;
      c_[31*max_+8] = 7888725;
      c_[31*max_+9] = 20160075;
      c_[31*max_+10] = 44352165;
      c_[31*max_+11] = 84672315;
      c_[31*max_+12] = 141120525;
      c_[31*max_+13] = 206253075;
      c_[31*max_+14] = 265182525;
      c_[31*max_+15] = 300540195;
      c_[31*max_+16] = 300540195;
      c_[31*max_+17] = 265182525;
      c_[31*max_+18] = 206253075;
      c_[31*max_+19] = 141120525;
      c_[31*max_+20] = 84672315;
      c_[31*max_+21] = 44352165;
      c_[31*max_+22] = 20160075;
      c_[31*max_+23] = 7888725;
      c_[31*max_+24] = 2629575;
      c_[31*max_+25] = 736281;
      c_[31*max_+26] = 169911;
      c_[31*max_+27] = 31465;
      c_[31*max_+28] = 4495;
      c_[31*max_+29] = 465;
      c_[31*max_+30] = 31;
      c_[31*max_+31] = 1;
    }
    size_t c(const int i, const int j) const { assert(i >= 0 && j >= 0); return c_[i*max_+j]; }
};

#endif

#if 0
// The code to generate this file (with mpfrc++).
#include <iostream>
#include <cassert>
#include "mpreal.h"
using namespace mpfr;
using namespace std;

mpreal fac(const mpreal i) {
  if (i < 1.1) { return 1; }
  else { return i * fac(i-1); }
}

int main() {
  mpreal::set_default_prec(2048);
  for (int i=0; i!=32; ++i) {
    for (int j=0; j!=i+1; ++j) {
      mpreal ii(i);
      mpreal jj(j);
      mpreal kk = ii - jj;
      mpreal out = fac(ii)/fac(jj)/fac(kk);
      int iout = (int)(out+0.1);
      if (abs(out-iout) > 1.0e-10) assert(false);
      cout << "c_[" << i << "*max_+" << j << "] = " << iout << ";" << endl;
    }
  }
  return 0;
}
#endif


}
