xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 48;
 0.37604;-13.26468;-0.03625;,
 0.86271;-13.25562;-0.03625;,
 0.37604;-13.25562;0.56682;,
 1.95833;-0.16064;1.30909;,
 1.61586;-0.00520;1.09699;,
 1.61586;-0.01426;1.70007;,
 -1.38852;-0.00520;1.09699;,
 -1.88724;-0.01426;1.09699;,
 -1.38852;-0.01426;1.70007;,
 -1.94207;-13.25562;-0.03625;,
 -1.45540;-13.26468;-0.03625;,
 -1.45540;-13.25562;0.56682;,
 2.32747;-0.01426;-1.08068;,
 1.61586;-0.00520;-1.08068;,
 -1.38852;-0.00520;-1.08068;,
 -2.00372;-0.01426;-1.08068;,
 1.61586;-0.01426;-2.29330;,
 -1.38852;-0.01426;-2.33673;,
 0.86271;-13.25562;-1.08068;,
 0.37604;-13.26468;-1.08068;,
 0.37604;-13.25562;-1.33889;,
 -1.45540;-13.26468;-1.08068;,
 -1.94207;-13.25562;-1.08068;,
 -1.45540;-13.25562;-1.38232;,
 0.87767;-5.90956;1.76032;,
 1.81422;-5.90956;1.15724;,
 -1.78981;-5.90956;1.76032;,
 -2.27648;-5.90956;1.15724;,
 0.87767;-5.90956;-3.22809;,
 1.81422;-5.90956;-1.08068;,
 -1.78981;-5.90956;-3.27152;,
 -2.27648;-5.90956;-1.08068;,
 -0.89149;-0.01426;1.70007;,
 -0.89149;-0.00520;1.09699;,
 -0.89149;-0.00520;-1.08068;,
 -0.89149;-0.01426;-2.63817;,
 -0.66160;-13.25562;0.56682;,
 -0.66160;-13.26468;-0.03625;,
 -0.66160;-13.25562;-1.68376;,
 -0.66160;-13.26468;-1.08068;,
 -0.66160;-0.01426;1.70007;,
 -0.66160;-5.90956;2.34379;,
 -0.66161;-5.90956;-3.57297;,
 -0.66161;-0.01426;-2.63817;,
 -0.66160;-0.01426;1.70007;,
 -0.66160;-0.00520;1.09699;,
 -0.66160;-0.00520;-1.08068;,
 -0.66161;-0.01426;-2.63817;;
 
 47;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 4;12,13,4,3;,
 4;7,6,14,15;,
 3;12,16,13;,
 3;17,15,14;,
 3;18,19,20;,
 3;21,22,23;,
 4;1,0,19,18;,
 4;22,21,10,9;,
 4;24,2,1,25;,
 4;24,25,3,5;,
 4;26,8,7,27;,
 4;26,27,9,11;,
 4;28,16,12,29;,
 4;28,29,18,20;,
 4;30,23,22,31;,
 4;30,31,15,17;,
 4;29,12,3,25;,
 4;29,25,1,18;,
 4;27,7,15,31;,
 4;27,31,22,9;,
 4;32,33,6,8;,
 4;34,14,6,33;,
 4;34,35,17,14;,
 4;36,11,10,37;,
 4;36,37,0,2;,
 4;38,20,19,39;,
 4;38,39,21,23;,
 4;37,10,21,39;,
 4;37,39,19,0;,
 4;40,8,26,41;,
 4;40,41,24,5;,
 4;41,26,11,36;,
 4;41,36,2,24;,
 4;38,23,30,42;,
 4;38,42,28,20;,
 4;42,30,17,43;,
 4;42,43,16,28;,
 4;44,5,4,45;,
 4;44,45,33,32;,
 4;45,4,13,46;,
 4;45,46,34,33;,
 4;46,13,16,47;,
 4;46,47,35,34;;
 
 MeshMaterialList {
  13;
  47;
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.153600;0.800000;0.028000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.768800;0.674400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.304000;0.153600;0.176000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.231000;0.086000;0.137000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.125600;0.037600;0.047200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\clothes.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\clothes.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\denim.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\denim.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\denim.jpg";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  64;
  0.009307;-0.999844;0.015022;,
  0.207624;0.978098;0.014692;,
  -0.009080;0.999846;0.015019;,
  -0.009307;-0.999844;0.015022;,
  0.150255;0.988410;0.021671;,
  0.049925;0.998696;0.010670;,
  -0.008233;0.999961;-0.003333;,
  -0.008651;0.999934;0.007608;,
  0.006585;0.999953;-0.007057;,
  0.010550;-0.999493;-0.030056;,
  -0.010730;-0.999597;-0.026273;,
  -0.008244;0.999943;-0.006863;,
  0.009930;-0.999838;-0.015030;,
  0.009307;-0.999928;0.007511;,
  -0.009307;-0.999928;0.007511;,
  -0.010019;-0.999863;-0.013137;,
  0.018612;-0.999673;-0.017534;,
  0.099711;0.994710;0.024694;,
  0.298070;0.953886;0.035429;,
  0.018614;-0.999799;0.007510;,
  -0.018614;-0.999799;0.007510;,
  -0.017302;0.999821;0.007706;,
  -0.015583;0.999873;-0.003409;,
  -0.018612;-0.999714;-0.015011;,
  0.431464;-0.103935;0.896123;,
  -0.534268;-0.050932;0.843779;,
  0.559220;-0.099154;-0.823069;,
  -0.650360;-0.021890;-0.759311;,
  0.953902;-0.117305;-0.276243;,
  0.896199;-0.117848;0.427713;,
  -0.940261;-0.017876;0.339984;,
  -0.973467;0.003862;-0.228796;,
  0.000000;0.999887;0.015020;,
  0.000000;0.999972;0.007510;,
  -0.000441;0.999995;-0.003083;,
  -0.000882;0.999981;-0.006165;,
  0.000000;-0.999887;0.015023;,
  -0.029073;0.068254;0.997244;,
  0.000110;0.999995;-0.003115;,
  -0.069570;0.158035;-0.984980;,
  -0.000178;-0.999717;-0.023785;,
  -0.000089;-0.999929;-0.011894;,
  0.000000;-0.999972;0.007511;,
  -0.028476;-0.068242;0.997262;,
  -0.046005;-0.050240;-0.997677;,
  0.000220;0.999981;-0.006230;,
  0.432376;-0.204808;0.878126;,
  0.900401;-0.172480;0.399409;,
  0.888657;-0.063173;0.454201;,
  0.426029;-0.002065;0.904707;,
  -0.532166;0.071130;0.843647;,
  -0.935647;0.060394;0.347733;,
  -0.939021;-0.096373;0.330078;,
  -0.528404;-0.172280;0.831329;,
  0.600334;0.045767;-0.798439;,
  0.978507;-0.061675;-0.196777;,
  0.918483;-0.173497;-0.355369;,
  0.509481;-0.231418;-0.828779;,
  -0.586651;-0.164942;-0.792865;,
  -0.950993;-0.059098;-0.303511;,
  -0.985907;0.064813;-0.154229;,
  -0.699381;0.129247;-0.702966;,
  -0.027349;-0.203356;0.978723;,
  -0.020200;-0.257921;-0.965955;;
  47;
  3;13,19,0;,
  3;18,4,1;,
  3;7,21,2;,
  3;20,14,3;,
  4;17,5,4,18;,
  4;21,7,6,22;,
  3;17,8,5;,
  3;11,22,6;,
  3;16,12,9;,
  3;15,23,10;,
  4;19,13,12,16;,
  4;23,15,14,20;,
  4;24,46,47,29;,
  4;24,29,48,49;,
  4;25,50,51,30;,
  4;25,30,52,53;,
  4;26,54,55,28;,
  4;26,28,56,57;,
  4;27,58,59,31;,
  4;27,31,60,61;,
  4;28,55,48,29;,
  4;28,29,47,56;,
  4;30,51,60,31;,
  4;30,31,59,52;,
  4;32,33,7,2;,
  4;34,6,7,33;,
  4;34,35,11,6;,
  4;36,3,14,42;,
  4;36,42,13,0;,
  4;40,9,12,41;,
  4;40,41,15,10;,
  4;42,14,15,41;,
  4;42,41,12,13;,
  4;37,50,25,43;,
  4;37,43,24,49;,
  4;43,25,53,62;,
  4;43,62,46,24;,
  4;63,58,27,44;,
  4;63,44,26,57;,
  4;44,27,61,39;,
  4;44,39,54,26;,
  4;32,1,4,33;,
  4;32,33,33,32;,
  4;33,4,5,38;,
  4;33,38,34,33;,
  4;38,5,8,45;,
  4;38,45,35,34;;
 }
 MeshTextureCoords {
  48;
  0.262569;3.495319;,
  0.261041;3.494542;,
  0.289238;3.494542;,
  0.299232;2.372205;,
  0.296075;2.358883;,
  0.313997;2.359659;,
  0.358640;2.358883;,
  0.385420;2.359659;,
  0.386817;2.359659;,
  0.286602;3.494542;,
  0.276167;3.495319;,
  0.327264;3.494542;,
  0.227700;2.359659;,
  0.224407;2.358883;,
  0.183667;2.358883;,
  0.154365;2.359659;,
  0.186933;2.359659;,
  0.112760;2.359659;,
  0.219681;3.494542;,
  0.215590;3.495319;,
  0.204564;3.494542;,
  0.181324;3.495319;,
  0.158295;3.494542;,
  0.159240;3.494542;,
  0.326163;2.864930;,
  0.296112;2.864930;,
  0.409022;2.864930;,
  0.416744;2.864930;,
  0.149698;2.864930;,
  0.225418;2.864930;,
  0.067401;2.864930;,
  0.132880;2.864930;,
  0.366852;2.359659;,
  0.339717;2.358883;,
  0.197235;2.358883;,
  0.121686;2.359659;,
  0.304662;3.494542;,
  0.267824;3.495319;,
  0.169082;3.494542;,
  0.201849;3.495319;,
  0.359150;2.359659;,
  0.381119;2.864930;,
  0.102878;2.864930;,
  0.129476;2.359659;,
  0.359150;2.359659;,
  0.332831;2.358883;,
  0.201849;2.358883;,
  0.129476;2.359659;;
 }
}
