#pragma once
#include "lib/fixed/q0_23.h"
#include "lib/fixed/q0_23.h"
#include "lib/fixed/q0_23.h"
#include "lib/fixed/q0_23.h"
q0_23_t distortion_mono(q0_23_t x)
{
// Get lookup addr from top bits of value
uint8_t lut_addr = int24_23_16(x.qmn);
// And interpolation bits from lsbs
uint16_t interp_point = int24_15_0(x.qmn);
// Generated lookup values:
q0_23_t Y_VALUES[256];
Y_VALUES[128].qmn = -0x7ffffd;
Y_VALUES[129].qmn = -0x7ffffd;
Y_VALUES[130].qmn = -0x7ffffc;
Y_VALUES[131].qmn = -0x7ffffc;
Y_VALUES[132].qmn = -0x7ffffb;
Y_VALUES[133].qmn = -0x7ffffb;
Y_VALUES[134].qmn = -0x7ffffa;
Y_VALUES[135].qmn = -0x7ffffa;
Y_VALUES[136].qmn = -0x7ffff9;
Y_VALUES[137].qmn = -0x7ffff8;
Y_VALUES[138].qmn = -0x7ffff7;
Y_VALUES[139].qmn = -0x7ffff6;
Y_VALUES[140].qmn = -0x7ffff5;
Y_VALUES[141].qmn = -0x7ffff4;
Y_VALUES[142].qmn = -0x7ffff2;
Y_VALUES[143].qmn = -0x7ffff1;
Y_VALUES[144].qmn = -0x7fffef;
Y_VALUES[145].qmn = -0x7fffed;
Y_VALUES[146].qmn = -0x7fffea;
Y_VALUES[147].qmn = -0x7fffe8;
Y_VALUES[148].qmn = -0x7fffe5;
Y_VALUES[149].qmn = -0x7fffe1;
Y_VALUES[150].qmn = -0x7fffde;
Y_VALUES[151].qmn = -0x7fffd9;
Y_VALUES[152].qmn = -0x7fffd5;
Y_VALUES[153].qmn = -0x7fffcf;
Y_VALUES[154].qmn = -0x7fffc9;
Y_VALUES[155].qmn = -0x7fffc3;
Y_VALUES[156].qmn = -0x7fffbb;
Y_VALUES[157].qmn = -0x7fffb3;
Y_VALUES[158].qmn = -0x7fffa9;
Y_VALUES[159].qmn = -0x7fff9e;
Y_VALUES[160].qmn = -0x7fff92;
Y_VALUES[161].qmn = -0x7fff85;
Y_VALUES[162].qmn = -0x7fff76;
Y_VALUES[163].qmn = -0x7fff64;
Y_VALUES[164].qmn = -0x7fff51;
Y_VALUES[165].qmn = -0x7fff3b;
Y_VALUES[166].qmn = -0x7fff23;
Y_VALUES[167].qmn = -0x7fff08;
Y_VALUES[168].qmn = -0x7ffee9;
Y_VALUES[169].qmn = -0x7ffec6;
Y_VALUES[170].qmn = -0x7ffe9f;
Y_VALUES[171].qmn = -0x7ffe73;
Y_VALUES[172].qmn = -0x7ffe42;
Y_VALUES[173].qmn = -0x7ffe0b;
Y_VALUES[174].qmn = -0x7ffdcd;
Y_VALUES[175].qmn = -0x7ffd87;
Y_VALUES[176].qmn = -0x7ffd38;
Y_VALUES[177].qmn = -0x7ffce0;
Y_VALUES[178].qmn = -0x7ffc7c;
Y_VALUES[179].qmn = -0x7ffc0c;
Y_VALUES[180].qmn = -0x7ffb8f;
Y_VALUES[181].qmn = -0x7ffb01;
Y_VALUES[182].qmn = -0x7ffa62;
Y_VALUES[183].qmn = -0x7ff9b0;
Y_VALUES[184].qmn = -0x7ff8e7;
Y_VALUES[185].qmn = -0x7ff805;
Y_VALUES[186].qmn = -0x7ff707;
Y_VALUES[187].qmn = -0x7ff5e9;
Y_VALUES[188].qmn = -0x7ff4a8;
Y_VALUES[189].qmn = -0x7ff33f;
Y_VALUES[190].qmn = -0x7ff1a9;
Y_VALUES[191].qmn = -0x7fefe1;
Y_VALUES[192].qmn = -0x7fede0;
Y_VALUES[193].qmn = -0x7feb9f;
Y_VALUES[194].qmn = -0x7fe916;
Y_VALUES[195].qmn = -0x7fe63d;
Y_VALUES[196].qmn = -0x7fe309;
Y_VALUES[197].qmn = -0x7fdf70;
Y_VALUES[198].qmn = -0x7fdb63;
Y_VALUES[199].qmn = -0x7fd6d6;
Y_VALUES[200].qmn = -0x7fd1b8;
Y_VALUES[201].qmn = -0x7fcbf7;
Y_VALUES[202].qmn = -0x7fc57f;
Y_VALUES[203].qmn = -0x7fbe39;
Y_VALUES[204].qmn = -0x7fb60b;
Y_VALUES[205].qmn = -0x7facd9;
Y_VALUES[206].qmn = -0x7fa283;
Y_VALUES[207].qmn = -0x7f96e3;
Y_VALUES[208].qmn = -0x7f89d1;
Y_VALUES[209].qmn = -0x7f7b20;
Y_VALUES[210].qmn = -0x7f6a9b;
Y_VALUES[211].qmn = -0x7f5808;
Y_VALUES[212].qmn = -0x7f4326;
Y_VALUES[213].qmn = -0x7f2bab;
Y_VALUES[214].qmn = -0x7f1145;
Y_VALUES[215].qmn = -0x7ef396;
Y_VALUES[216].qmn = -0x7ed237;
Y_VALUES[217].qmn = -0x7eacb2;
Y_VALUES[218].qmn = -0x7e8282;
Y_VALUES[219].qmn = -0x7e5314;
Y_VALUES[220].qmn = -0x7e1dc0;
Y_VALUES[221].qmn = -0x7de1cb;
Y_VALUES[222].qmn = -0x7d9e61;
Y_VALUES[223].qmn = -0x7d5296;
Y_VALUES[224].qmn = -0x7cfd5e;
Y_VALUES[225].qmn = -0x7c9d8e;
Y_VALUES[226].qmn = -0x7c31d5;
Y_VALUES[227].qmn = -0x7bb8b6;
Y_VALUES[228].qmn = -0x7b3089;
Y_VALUES[229].qmn = -0x7a976d;
Y_VALUES[230].qmn = -0x79eb49;
Y_VALUES[231].qmn = -0x7929bd;
Y_VALUES[232].qmn = -0x785020;
Y_VALUES[233].qmn = -0x775b76;
Y_VALUES[234].qmn = -0x764860;
Y_VALUES[235].qmn = -0x751317;
Y_VALUES[236].qmn = -0x73b759;
Y_VALUES[237].qmn = -0x723060;
Y_VALUES[238].qmn = -0x7078ca;
Y_VALUES[239].qmn = -0x6e8a8d;
Y_VALUES[240].qmn = -0x6c5edd;
Y_VALUES[241].qmn = -0x69ee16;
Y_VALUES[242].qmn = -0x672fa2;
Y_VALUES[243].qmn = -0x6419d7;
Y_VALUES[244].qmn = -0x60a1db;
Y_VALUES[245].qmn = -0x5cbb77;
Y_VALUES[246].qmn = -0x5858f2;
Y_VALUES[247].qmn = -0x536add;
Y_VALUES[248].qmn = -0x4ddfdd;
Y_VALUES[249].qmn = -0x47a471;
Y_VALUES[250].qmn = -0x40a2a9;
Y_VALUES[251].qmn = -0x38c1dc;
Y_VALUES[252].qmn = -0x2fe64f;
Y_VALUES[253].qmn = -0x25f0d5;
Y_VALUES[254].qmn = -0x1abe60;
Y_VALUES[255].qmn = -0xe2789;
Y_VALUES[0].qmn = 0x0;
Y_VALUES[1].qmn = 0xe2789;
Y_VALUES[2].qmn = 0x1abe60;
Y_VALUES[3].qmn = 0x25f0d5;
Y_VALUES[4].qmn = 0x2fe64f;
Y_VALUES[5].qmn = 0x38c1dc;
Y_VALUES[6].qmn = 0x40a2a9;
Y_VALUES[7].qmn = 0x47a471;
Y_VALUES[8].qmn = 0x4ddfdd;
Y_VALUES[9].qmn = 0x536add;
Y_VALUES[10].qmn = 0x5858f2;
Y_VALUES[11].qmn = 0x5cbb77;
Y_VALUES[12].qmn = 0x60a1db;
Y_VALUES[13].qmn = 0x6419d7;
Y_VALUES[14].qmn = 0x672fa2;
Y_VALUES[15].qmn = 0x69ee16;
Y_VALUES[16].qmn = 0x6c5edd;
Y_VALUES[17].qmn = 0x6e8a8d;
Y_VALUES[18].qmn = 0x7078ca;
Y_VALUES[19].qmn = 0x723060;
Y_VALUES[20].qmn = 0x73b759;
Y_VALUES[21].qmn = 0x751317;
Y_VALUES[22].qmn = 0x764860;
Y_VALUES[23].qmn = 0x775b76;
Y_VALUES[24].qmn = 0x785020;
Y_VALUES[25].qmn = 0x7929bd;
Y_VALUES[26].qmn = 0x79eb49;
Y_VALUES[27].qmn = 0x7a976d;
Y_VALUES[28].qmn = 0x7b3089;
Y_VALUES[29].qmn = 0x7bb8b6;
Y_VALUES[30].qmn = 0x7c31d5;
Y_VALUES[31].qmn = 0x7c9d8e;
Y_VALUES[32].qmn = 0x7cfd5e;
Y_VALUES[33].qmn = 0x7d5296;
Y_VALUES[34].qmn = 0x7d9e61;
Y_VALUES[35].qmn = 0x7de1cb;
Y_VALUES[36].qmn = 0x7e1dc0;
Y_VALUES[37].qmn = 0x7e5314;
Y_VALUES[38].qmn = 0x7e8282;
Y_VALUES[39].qmn = 0x7eacb2;
Y_VALUES[40].qmn = 0x7ed237;
Y_VALUES[41].qmn = 0x7ef396;
Y_VALUES[42].qmn = 0x7f1145;
Y_VALUES[43].qmn = 0x7f2bab;
Y_VALUES[44].qmn = 0x7f4326;
Y_VALUES[45].qmn = 0x7f5808;
Y_VALUES[46].qmn = 0x7f6a9b;
Y_VALUES[47].qmn = 0x7f7b20;
Y_VALUES[48].qmn = 0x7f89d1;
Y_VALUES[49].qmn = 0x7f96e3;
Y_VALUES[50].qmn = 0x7fa283;
Y_VALUES[51].qmn = 0x7facd9;
Y_VALUES[52].qmn = 0x7fb60b;
Y_VALUES[53].qmn = 0x7fbe39;
Y_VALUES[54].qmn = 0x7fc57f;
Y_VALUES[55].qmn = 0x7fcbf7;
Y_VALUES[56].qmn = 0x7fd1b8;
Y_VALUES[57].qmn = 0x7fd6d6;
Y_VALUES[58].qmn = 0x7fdb63;
Y_VALUES[59].qmn = 0x7fdf70;
Y_VALUES[60].qmn = 0x7fe309;
Y_VALUES[61].qmn = 0x7fe63d;
Y_VALUES[62].qmn = 0x7fe916;
Y_VALUES[63].qmn = 0x7feb9f;
Y_VALUES[64].qmn = 0x7fede0;
Y_VALUES[65].qmn = 0x7fefe1;
Y_VALUES[66].qmn = 0x7ff1a9;
Y_VALUES[67].qmn = 0x7ff33f;
Y_VALUES[68].qmn = 0x7ff4a8;
Y_VALUES[69].qmn = 0x7ff5e9;
Y_VALUES[70].qmn = 0x7ff707;
Y_VALUES[71].qmn = 0x7ff805;
Y_VALUES[72].qmn = 0x7ff8e7;
Y_VALUES[73].qmn = 0x7ff9b0;
Y_VALUES[74].qmn = 0x7ffa62;
Y_VALUES[75].qmn = 0x7ffb01;
Y_VALUES[76].qmn = 0x7ffb8f;
Y_VALUES[77].qmn = 0x7ffc0c;
Y_VALUES[78].qmn = 0x7ffc7c;
Y_VALUES[79].qmn = 0x7ffce0;
Y_VALUES[80].qmn = 0x7ffd38;
Y_VALUES[81].qmn = 0x7ffd87;
Y_VALUES[82].qmn = 0x7ffdcd;
Y_VALUES[83].qmn = 0x7ffe0b;
Y_VALUES[84].qmn = 0x7ffe42;
Y_VALUES[85].qmn = 0x7ffe73;
Y_VALUES[86].qmn = 0x7ffe9f;
Y_VALUES[87].qmn = 0x7ffec6;
Y_VALUES[88].qmn = 0x7ffee9;
Y_VALUES[89].qmn = 0x7fff08;
Y_VALUES[90].qmn = 0x7fff23;
Y_VALUES[91].qmn = 0x7fff3b;
Y_VALUES[92].qmn = 0x7fff51;
Y_VALUES[93].qmn = 0x7fff64;
Y_VALUES[94].qmn = 0x7fff76;
Y_VALUES[95].qmn = 0x7fff85;
Y_VALUES[96].qmn = 0x7fff92;
Y_VALUES[97].qmn = 0x7fff9e;
Y_VALUES[98].qmn = 0x7fffa9;
Y_VALUES[99].qmn = 0x7fffb3;
Y_VALUES[100].qmn = 0x7fffbb;
Y_VALUES[101].qmn = 0x7fffc3;
Y_VALUES[102].qmn = 0x7fffc9;
Y_VALUES[103].qmn = 0x7fffcf;
Y_VALUES[104].qmn = 0x7fffd5;
Y_VALUES[105].qmn = 0x7fffd9;
Y_VALUES[106].qmn = 0x7fffde;
Y_VALUES[107].qmn = 0x7fffe1;
Y_VALUES[108].qmn = 0x7fffe5;
Y_VALUES[109].qmn = 0x7fffe8;
Y_VALUES[110].qmn = 0x7fffea;
Y_VALUES[111].qmn = 0x7fffed;
Y_VALUES[112].qmn = 0x7fffef;
Y_VALUES[113].qmn = 0x7ffff1;
Y_VALUES[114].qmn = 0x7ffff2;
Y_VALUES[115].qmn = 0x7ffff4;
Y_VALUES[116].qmn = 0x7ffff5;
Y_VALUES[117].qmn = 0x7ffff6;
Y_VALUES[118].qmn = 0x7ffff7;
Y_VALUES[119].qmn = 0x7ffff8;
Y_VALUES[120].qmn = 0x7ffff9;
Y_VALUES[121].qmn = 0x7ffffa;
Y_VALUES[122].qmn = 0x7ffffa;
Y_VALUES[123].qmn = 0x7ffffb;
Y_VALUES[124].qmn = 0x7ffffb;
Y_VALUES[125].qmn = 0x7ffffc;
Y_VALUES[126].qmn = 0x7ffffc;
Y_VALUES[127].qmn = 0x7ffffd;

// M Scaled down by 2^4
q0_23_t M_VALUES[256];
M_VALUES[128].qmn = 0x2;
M_VALUES[129].qmn = 0x2;
M_VALUES[130].qmn = 0x3;
M_VALUES[131].qmn = 0x3;
M_VALUES[132].qmn = 0x4;
M_VALUES[133].qmn = 0x4;
M_VALUES[134].qmn = 0x5;
M_VALUES[135].qmn = 0x5;
M_VALUES[136].qmn = 0x6;
M_VALUES[137].qmn = 0x7;
M_VALUES[138].qmn = 0x8;
M_VALUES[139].qmn = 0x9;
M_VALUES[140].qmn = 0xa;
M_VALUES[141].qmn = 0xb;
M_VALUES[142].qmn = 0xd;
M_VALUES[143].qmn = 0xe;
M_VALUES[144].qmn = 0x10;
M_VALUES[145].qmn = 0x12;
M_VALUES[146].qmn = 0x15;
M_VALUES[147].qmn = 0x17;
M_VALUES[148].qmn = 0x1a;
M_VALUES[149].qmn = 0x1d;
M_VALUES[150].qmn = 0x21;
M_VALUES[151].qmn = 0x25;
M_VALUES[152].qmn = 0x2a;
M_VALUES[153].qmn = 0x2f;
M_VALUES[154].qmn = 0x35;
M_VALUES[155].qmn = 0x3c;
M_VALUES[156].qmn = 0x43;
M_VALUES[157].qmn = 0x4c;
M_VALUES[158].qmn = 0x55;
M_VALUES[159].qmn = 0x60;
M_VALUES[160].qmn = 0x6c;
M_VALUES[161].qmn = 0x7a;
M_VALUES[162].qmn = 0x89;
M_VALUES[163].qmn = 0x9a;
M_VALUES[164].qmn = 0xad;
M_VALUES[165].qmn = 0xc2;
M_VALUES[166].qmn = 0xdb;
M_VALUES[167].qmn = 0xf6;
M_VALUES[168].qmn = 0x115;
M_VALUES[169].qmn = 0x137;
M_VALUES[170].qmn = 0x15e;
M_VALUES[171].qmn = 0x189;
M_VALUES[172].qmn = 0x1ba;
M_VALUES[173].qmn = 0x1f1;
M_VALUES[174].qmn = 0x22f;
M_VALUES[175].qmn = 0x275;
M_VALUES[176].qmn = 0x2c3;
M_VALUES[177].qmn = 0x31b;
M_VALUES[178].qmn = 0x37e;
M_VALUES[179].qmn = 0x3ed;
M_VALUES[180].qmn = 0x46a;
M_VALUES[181].qmn = 0x4f7;
M_VALUES[182].qmn = 0x595;
M_VALUES[183].qmn = 0x647;
M_VALUES[184].qmn = 0x70f;
M_VALUES[185].qmn = 0x7ef;
M_VALUES[186].qmn = 0x8ec;
M_VALUES[187].qmn = 0xa08;
M_VALUES[188].qmn = 0xb47;
M_VALUES[189].qmn = 0xcae;
M_VALUES[190].qmn = 0xe42;
M_VALUES[191].qmn = 0x1008;
M_VALUES[192].qmn = 0x1206;
M_VALUES[193].qmn = 0x1444;
M_VALUES[194].qmn = 0x16c9;
M_VALUES[195].qmn = 0x199e;
M_VALUES[196].qmn = 0x1cce;
M_VALUES[197].qmn = 0x2063;
M_VALUES[198].qmn = 0x246a;
M_VALUES[199].qmn = 0x28f1;
M_VALUES[200].qmn = 0x2e08;
M_VALUES[201].qmn = 0x33c1;
M_VALUES[202].qmn = 0x3a30;
M_VALUES[203].qmn = 0x416c;
M_VALUES[204].qmn = 0x498f;
M_VALUES[205].qmn = 0x52b4;
M_VALUES[206].qmn = 0x5cfc;
M_VALUES[207].qmn = 0x688c;
M_VALUES[208].qmn = 0x758b;
M_VALUES[209].qmn = 0x8429;
M_VALUES[210].qmn = 0x9497;
M_VALUES[211].qmn = 0xa711;
M_VALUES[212].qmn = 0xbbd6;
M_VALUES[213].qmn = 0xd331;
M_VALUES[214].qmn = 0xed73;
M_VALUES[215].qmn = 0x10af9;
M_VALUES[216].qmn = 0x12c2a;
M_VALUES[217].qmn = 0x1517c;
M_VALUES[218].qmn = 0x17b71;
M_VALUES[219].qmn = 0x1aa9f;
M_VALUES[220].qmn = 0x1dfa9;
M_VALUES[221].qmn = 0x21b4c;
M_VALUES[222].qmn = 0x25e5a;
M_VALUES[223].qmn = 0x2a9bd;
M_VALUES[224].qmn = 0x2fe80;
M_VALUES[225].qmn = 0x35dcc;
M_VALUES[226].qmn = 0x3c8f2;
M_VALUES[227].qmn = 0x4416a;
M_VALUES[228].qmn = 0x4c8dd;
M_VALUES[229].qmn = 0x56126;
M_VALUES[230].qmn = 0x60c5f;
M_VALUES[231].qmn = 0x6cce1;
M_VALUES[232].qmn = 0x7a553;
M_VALUES[233].qmn = 0x898ae;
M_VALUES[234].qmn = 0x9aa4b;
M_VALUES[235].qmn = 0xaddec;
M_VALUES[236].qmn = 0xc37cc;
M_VALUES[237].qmn = 0xdbcae;
M_VALUES[238].qmn = 0xf71e8;
M_VALUES[239].qmn = 0x115d7f;
M_VALUES[240].qmn = 0x138635;
M_VALUES[241].qmn = 0x15f3a3;
M_VALUES[242].qmn = 0x18ae54;
M_VALUES[243].qmn = 0x1bbfe3;
M_VALUES[244].qmn = 0x1f331d;
M_VALUES[245].qmn = 0x231428;
M_VALUES[246].qmn = 0x2770a9;
M_VALUES[247].qmn = 0x2c57fb;
M_VALUES[248].qmn = 0x31db60;
M_VALUES[249].qmn = 0x380e3f;
M_VALUES[250].qmn = 0x3f066b;
M_VALUES[251].qmn = 0x46dc6a;
M_VALUES[252].qmn = 0x4fabd0;
M_VALUES[253].qmn = 0x5993a1;
M_VALUES[254].qmn = 0x64b6ba;
M_VALUES[255].qmn = 0x713c4c;
M_VALUES[0].qmn = 0x713c4c;
M_VALUES[1].qmn = 0x64b6ba;
M_VALUES[2].qmn = 0x5993a1;
M_VALUES[3].qmn = 0x4fabd0;
M_VALUES[4].qmn = 0x46dc6a;
M_VALUES[5].qmn = 0x3f066b;
M_VALUES[6].qmn = 0x380e3f;
M_VALUES[7].qmn = 0x31db60;
M_VALUES[8].qmn = 0x2c57fb;
M_VALUES[9].qmn = 0x2770a9;
M_VALUES[10].qmn = 0x231428;
M_VALUES[11].qmn = 0x1f331d;
M_VALUES[12].qmn = 0x1bbfe3;
M_VALUES[13].qmn = 0x18ae54;
M_VALUES[14].qmn = 0x15f3a3;
M_VALUES[15].qmn = 0x138635;
M_VALUES[16].qmn = 0x115d7f;
M_VALUES[17].qmn = 0xf71e8;
M_VALUES[18].qmn = 0xdbcae;
M_VALUES[19].qmn = 0xc37cc;
M_VALUES[20].qmn = 0xaddec;
M_VALUES[21].qmn = 0x9aa4b;
M_VALUES[22].qmn = 0x898ae;
M_VALUES[23].qmn = 0x7a553;
M_VALUES[24].qmn = 0x6cce1;
M_VALUES[25].qmn = 0x60c5f;
M_VALUES[26].qmn = 0x56126;
M_VALUES[27].qmn = 0x4c8dd;
M_VALUES[28].qmn = 0x4416a;
M_VALUES[29].qmn = 0x3c8f2;
M_VALUES[30].qmn = 0x35dcc;
M_VALUES[31].qmn = 0x2fe80;
M_VALUES[32].qmn = 0x2a9bd;
M_VALUES[33].qmn = 0x25e5a;
M_VALUES[34].qmn = 0x21b4c;
M_VALUES[35].qmn = 0x1dfa9;
M_VALUES[36].qmn = 0x1aa9f;
M_VALUES[37].qmn = 0x17b71;
M_VALUES[38].qmn = 0x1517c;
M_VALUES[39].qmn = 0x12c2a;
M_VALUES[40].qmn = 0x10af9;
M_VALUES[41].qmn = 0xed73;
M_VALUES[42].qmn = 0xd331;
M_VALUES[43].qmn = 0xbbd6;
M_VALUES[44].qmn = 0xa711;
M_VALUES[45].qmn = 0x9497;
M_VALUES[46].qmn = 0x8429;
M_VALUES[47].qmn = 0x758b;
M_VALUES[48].qmn = 0x688c;
M_VALUES[49].qmn = 0x5cfc;
M_VALUES[50].qmn = 0x52b4;
M_VALUES[51].qmn = 0x498f;
M_VALUES[52].qmn = 0x416c;
M_VALUES[53].qmn = 0x3a30;
M_VALUES[54].qmn = 0x33c1;
M_VALUES[55].qmn = 0x2e08;
M_VALUES[56].qmn = 0x28f1;
M_VALUES[57].qmn = 0x246a;
M_VALUES[58].qmn = 0x2063;
M_VALUES[59].qmn = 0x1cce;
M_VALUES[60].qmn = 0x199e;
M_VALUES[61].qmn = 0x16c9;
M_VALUES[62].qmn = 0x1444;
M_VALUES[63].qmn = 0x1206;
M_VALUES[64].qmn = 0x1008;
M_VALUES[65].qmn = 0xe42;
M_VALUES[66].qmn = 0xcae;
M_VALUES[67].qmn = 0xb47;
M_VALUES[68].qmn = 0xa08;
M_VALUES[69].qmn = 0x8ec;
M_VALUES[70].qmn = 0x7ef;
M_VALUES[71].qmn = 0x70f;
M_VALUES[72].qmn = 0x647;
M_VALUES[73].qmn = 0x595;
M_VALUES[74].qmn = 0x4f7;
M_VALUES[75].qmn = 0x46a;
M_VALUES[76].qmn = 0x3ed;
M_VALUES[77].qmn = 0x37e;
M_VALUES[78].qmn = 0x31b;
M_VALUES[79].qmn = 0x2c3;
M_VALUES[80].qmn = 0x275;
M_VALUES[81].qmn = 0x22f;
M_VALUES[82].qmn = 0x1f1;
M_VALUES[83].qmn = 0x1ba;
M_VALUES[84].qmn = 0x189;
M_VALUES[85].qmn = 0x15e;
M_VALUES[86].qmn = 0x137;
M_VALUES[87].qmn = 0x115;
M_VALUES[88].qmn = 0xf6;
M_VALUES[89].qmn = 0xdb;
M_VALUES[90].qmn = 0xc2;
M_VALUES[91].qmn = 0xad;
M_VALUES[92].qmn = 0x9a;
M_VALUES[93].qmn = 0x89;
M_VALUES[94].qmn = 0x7a;
M_VALUES[95].qmn = 0x6c;
M_VALUES[96].qmn = 0x60;
M_VALUES[97].qmn = 0x55;
M_VALUES[98].qmn = 0x4c;
M_VALUES[99].qmn = 0x43;
M_VALUES[100].qmn = 0x3c;
M_VALUES[101].qmn = 0x35;
M_VALUES[102].qmn = 0x2f;
M_VALUES[103].qmn = 0x2a;
M_VALUES[104].qmn = 0x25;
M_VALUES[105].qmn = 0x21;
M_VALUES[106].qmn = 0x1d;
M_VALUES[107].qmn = 0x1a;
M_VALUES[108].qmn = 0x17;
M_VALUES[109].qmn = 0x15;
M_VALUES[110].qmn = 0x12;
M_VALUES[111].qmn = 0x10;
M_VALUES[112].qmn = 0xe;
M_VALUES[113].qmn = 0xd;
M_VALUES[114].qmn = 0xb;
M_VALUES[115].qmn = 0xa;
M_VALUES[116].qmn = 0x9;
M_VALUES[117].qmn = 0x8;
M_VALUES[118].qmn = 0x7;
M_VALUES[119].qmn = 0x6;
M_VALUES[120].qmn = 0x5;
M_VALUES[121].qmn = 0x5;
M_VALUES[122].qmn = 0x4;
M_VALUES[123].qmn = 0x4;
M_VALUES[124].qmn = 0x3;
M_VALUES[125].qmn = 0x3;
M_VALUES[126].qmn = 0x2;
M_VALUES[127].qmn = 0x2;

// Do lookup
q0_23_t y = Y_VALUES[lut_addr];
q0_23_t m = M_VALUES[lut_addr];

// Do linear interp, dy = dx * m
// Not using fixed point mult funcs since
// need intermediates to do different scaling than normal
q0_23_t dxi; // Fractional bits of input x
dxi.qmn = interp_point;
int48_t temp = dxi.qmn * m.qmn;
int48_t temp_rounded = temp + (1 << (23 - 1));
// Shift right by 23 for normal Q mult, then shift left by 4 to account for slope scaling
q0_23_t dy;
dy.qmn = temp >> 19;
// Interpolate
q0_23_t yi = q0_23_add(y, dy);
return yi;
}


//printf("y_lut %f, dx %X * %d m.qmn = %f dy\n",q0_23_to_float(y), dxi, m.qmn, q0_23_to_float(dy));

/*
#pragma MAIN_MHZ distortion_tb 100.0
void distortion_tb()
{
  // -1.0 + (interpolation size-1) = point most distance from LUT data
  static int24_t x_int = 0xFE0000;  //0; //0x1800000; // 0x181FFFF; //-0x800000 + (131072-1); 
  q0_23_t x;
  x.qmn = x_int;
  q0_23_t y = distortion_mono(x);
  printf("x,y,%f,%f\n", q0_23_to_float(x), q0_23_to_float(y));
  x_int += 1; //131072; // Increment by interp points between LUT entries
}
*/


// Stereo
//#include "../i2s/i2s_mac.c" // For stereo types
i2s_samples_s distortion(i2s_samples_s in_samples)
{
  i2s_samples_s rv;
  rv.samples.l_data = distortion_mono(in_samples.samples.l_data);
  rv.samples.r_data = distortion_mono(in_samples.samples.r_data);
  rv.valid = in_samples.valid;
  return rv;
}


