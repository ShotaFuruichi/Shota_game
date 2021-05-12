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
 -8.75011;0.98031;-0.86826;,
 -0.25531;1.29302;-0.86826;,
 -0.25531;-1.23700;-0.86826;,
 -8.75011;-0.92430;-0.86826;,
 -0.25531;1.59302;-0.56826;,
 -8.75011;1.28031;-0.56826;,
 0.04469;-1.23700;-0.56826;,
 0.04469;1.29302;-0.56826;,
 -8.75011;-1.22430;-0.56826;,
 -0.25531;-1.53700;-0.56826;,
 -8.75984;0.98031;-0.56826;,
 -8.75984;-0.92430;-0.56826;,
 0.04469;1.29302;0.77392;,
 0.04469;-1.23700;0.77392;,
 -0.25531;1.59302;0.77392;,
 -0.25531;-1.23700;1.07392;,
 -0.25531;1.29302;1.07392;,
 -0.25531;-1.53700;0.77392;,
 -8.75011;0.98031;1.07392;,
 -8.75011;-0.92430;1.07392;,
 -8.75011;1.28031;0.77392;,
 -8.75984;-0.92430;0.77392;,
 -8.75984;0.98031;0.77392;,
 -8.75011;-1.22430;0.77392;,
 -6.65095;1.06457;-0.95419;,
 -0.23480;1.33144;-0.89776;,
 -0.23480;-1.27543;-0.89776;,
 -6.65095;-1.00857;-0.95419;,
 -0.23480;1.64056;-0.58865;,
 -6.65095;1.39112;-0.62764;,
 0.06670;-1.27543;-0.58865;,
 0.06670;1.33144;-0.58865;,
 -6.65095;-1.33511;-0.62764;,
 -0.23480;-1.58455;-0.58865;,
 -6.66127;1.06457;-0.62764;,
 -6.66127;-1.00857;-0.62764;,
 0.06670;1.33144;0.79431;,
 0.06670;-1.27543;0.79431;,
 -0.23480;1.64056;0.79431;,
 -0.23480;-1.27543;1.10342;,
 -0.23480;1.33144;1.10342;,
 -0.23480;-1.58455;0.79431;,
 -6.65095;1.06457;1.15985;,
 -6.65095;-1.00857;1.15985;,
 -6.65095;1.39112;0.83330;,
 -6.66127;-1.00857;0.83330;,
 -6.66127;1.06457;0.83330;,
 -6.65095;-1.33511;0.83330;;
 
 52;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;6,2,1,7;,
 4;8,3,2,9;,
 4;10,0,3,11;,
 3;10,5,0;,
 3;4,7,1;,
 3;6,9,2;,
 3;8,11,3;,
 4;7,12,13,6;,
 4;14,12,7,4;,
 4;15,13,12,16;,
 4;9,6,13,17;,
 3;14,16,12;,
 3;15,17,13;,
 4;16,18,19,15;,
 4;20,18,16,14;,
 4;21,19,18,22;,
 4;17,15,19,23;,
 3;20,22,18;,
 3;21,23,19;,
 4;22,10,11,21;,
 4;5,10,22,20;,
 4;23,21,11,8;,
 4;20,14,4,5;,
 4;8,9,17,23;,
 4;24,25,26,27;,
 4;28,25,24,29;,
 4;30,26,25,31;,
 4;32,27,26,33;,
 4;34,24,27,35;,
 3;34,29,24;,
 3;28,31,25;,
 3;30,33,26;,
 3;32,35,27;,
 4;31,36,37,30;,
 4;38,36,31,28;,
 4;39,37,36,40;,
 4;33,30,37,41;,
 3;38,40,36;,
 3;39,41,37;,
 4;40,42,43,39;,
 4;44,42,40,38;,
 4;45,43,42,46;,
 4;41,39,43,47;,
 3;44,46,42;,
 3;45,47,43;,
 4;46,34,35,45;,
 4;29,34,46,44;,
 4;47,45,35,32;,
 4;44,38,28,29;,
 4;32,33,41,47;;
 
 MeshMaterialList {
  13;
  52;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8;;
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
  -0.014084;0.382581;-0.923815;,
  0.360572;0.367959;-0.857085;,
  0.360572;-0.367959;-0.857085;,
  -0.014083;-0.382581;-0.923815;,
  0.854763;0.367001;-0.367001;,
  0.854763;0.367001;0.367001;,
  0.854763;-0.367001;0.367001;,
  0.854763;-0.367001;-0.367001;,
  0.360571;0.367959;0.857085;,
  -0.014084;0.382581;0.923815;,
  -0.014083;-0.382581;0.923815;,
  0.360572;-0.367959;0.857085;,
  -0.999737;0.016209;0.016209;,
  -0.999737;0.016209;-0.016209;,
  -0.999737;-0.016209;-0.016209;,
  -0.999737;-0.016209;0.016209;,
  -0.033989;0.923319;0.382527;,
  0.351408;0.860262;0.369406;,
  0.351408;0.860262;-0.369406;,
  -0.033989;0.923319;-0.382527;,
  -0.033988;-0.923319;-0.382527;,
  0.351409;-0.860262;-0.369406;,
  0.351409;-0.860262;0.369406;,
  -0.033988;-0.923319;0.382527;,
  -0.999343;0.016203;-0.032414;,
  -0.999343;-0.016203;-0.032414;,
  -0.999343;0.032414;-0.016203;,
  -0.999343;-0.032414;-0.016203;,
  -0.999343;-0.016203;0.032414;,
  -0.999343;0.016203;0.032414;,
  -0.999343;0.032414;0.016203;,
  -0.999343;-0.032414;0.016203;,
  -0.007790;0.382623;-0.923872;,
  0.369434;0.366843;-0.853783;,
  0.369434;-0.366846;-0.853781;,
  -0.007789;-0.382628;-0.923870;,
  0.859264;0.361703;-0.361713;,
  0.859264;0.361703;0.361713;,
  0.859263;-0.361705;0.361713;,
  0.859263;-0.361705;-0.361713;,
  0.369434;0.366843;0.853783;,
  -0.007790;0.382623;0.923872;,
  -0.007789;-0.382628;0.923870;,
  0.369434;-0.366846;0.853781;,
  -0.999751;0.015793;0.015793;,
  -0.999751;0.015793;-0.015793;,
  -0.999751;-0.015793;-0.015793;,
  -0.999751;-0.015793;0.015793;,
  -0.033571;0.923318;0.382565;,
  0.357618;0.857981;0.368752;,
  0.357618;0.857981;-0.368751;,
  -0.033571;0.923318;-0.382565;,
  -0.033570;-0.923320;-0.382561;,
  0.357616;-0.857983;-0.368748;,
  0.357616;-0.857983;0.368748;,
  -0.033570;-0.923320;0.382561;,
  -0.999377;0.015787;-0.031582;,
  -0.999376;-0.015787;-0.031582;,
  -0.999377;0.031582;-0.015787;,
  -0.999376;-0.031583;-0.015787;,
  -0.999376;-0.015787;0.031582;,
  -0.999377;0.015787;0.031582;,
  -0.999377;0.031582;0.015787;,
  -0.999376;-0.031583;0.015787;;
  52;
  4;0,1,2,3;,
  4;18,1,0,19;,
  4;7,2,1,4;,
  4;20,3,2,21;,
  4;13,24,25,14;,
  3;13,26,24;,
  3;18,4,1;,
  3;7,21,2;,
  3;27,14,25;,
  4;4,5,6,7;,
  4;17,5,4,18;,
  4;11,6,5,8;,
  4;21,7,6,22;,
  3;17,8,5;,
  3;11,22,6;,
  4;8,9,10,11;,
  4;16,9,8,17;,
  4;15,28,29,12;,
  4;22,11,10,23;,
  3;30,12,29;,
  3;15,31,28;,
  4;12,13,14,15;,
  4;26,13,12,30;,
  4;31,15,14,27;,
  4;16,17,18,19;,
  4;20,21,22,23;,
  4;32,33,34,35;,
  4;50,33,32,51;,
  4;39,34,33,36;,
  4;52,35,34,53;,
  4;45,56,57,46;,
  3;45,58,56;,
  3;50,36,33;,
  3;39,53,34;,
  3;59,46,57;,
  4;36,37,38,39;,
  4;49,37,36,50;,
  4;43,38,37,40;,
  4;53,39,38,54;,
  3;49,40,37;,
  3;43,54,38;,
  4;40,41,42,43;,
  4;48,41,40,49;,
  4;47,60,61,44;,
  4;54,43,42,55;,
  3;62,44,61;,
  3;47,63,60;,
  4;44,45,46,47;,
  4;58,45,44,62;,
  4;63,47,46,59;,
  4;48,49,50,51;,
  4;52,53,54,55;;
 }
 MeshTextureCoords {
  48;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.763563;-0.230338;,
  0.762336;0.192653;,
  0.761632;0.140770;,
  0.762916;-0.271598;,
  0.758596;0.198805;,
  0.759459;-0.223839;,
  0.758030;0.160397;,
  0.758516;0.212280;,
  0.758869;-0.278097;,
  0.757992;0.134618;,
  0.759385;-0.231009;,
  0.758936;-0.272270;,
  0.741483;0.212280;,
  0.741970;0.160397;,
  0.741403;0.198805;,
  0.738367;0.140770;,
  0.737663;0.192653;,
  0.742008;0.134618;,
  0.736436;-0.230338;,
  0.737084;-0.271598;,
  0.740540;-0.223839;,
  0.741063;-0.272270;,
  0.740614;-0.231009;,
  0.741130;-0.278097;;
 }
}
