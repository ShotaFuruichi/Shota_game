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
 46;
 -1.38246;-11.83045;-1.27246;,
 -1.85714;-11.81506;-1.27246;,
 -1.38246;-11.81506;-1.74714;,
 -1.79868;-0.46164;-1.08200;,
 -1.32400;0.01305;-1.08200;,
 -1.32400;-0.46164;-1.55668;,
 0.80809;0.01305;-1.08200;,
 1.95109;-0.46164;-1.08200;,
 0.80809;-0.46164;-1.55668;,
 1.90322;-11.81506;-1.27246;,
 1.42854;-11.83045;-1.27246;,
 1.42854;-11.81506;-1.74714;,
 -1.79868;-0.46164;-0.25993;,
 -1.32400;0.01305;-0.25993;,
 0.80809;0.01305;-0.25993;,
 1.95109;-0.46164;-0.25993;,
 -1.32400;-0.46164;0.72613;,
 0.80809;-0.46164;0.99758;,
 -1.85714;-11.81506;-0.25993;,
 -1.38246;-11.83045;-0.25993;,
 -1.38246;-11.81506;1.01533;,
 1.42854;-11.83045;-0.25993;,
 1.90322;-11.81506;-0.25993;,
 1.42854;-11.81506;1.04952;,
 -1.32400;-5.21088;-1.74714;,
 -1.79868;-5.21088;-1.27246;,
 1.43436;-5.21088;-1.74714;,
 1.90903;-5.21088;-1.27246;,
 -1.32400;-3.72514;1.95265;,
 -1.79868;-5.21088;-0.25993;,
 1.78105;-3.72514;1.21629;,
 1.90903;-5.21088;-0.25993;,
 -0.07308;-0.46164;-1.55668;,
 -0.07308;0.01305;-1.08200;,
 -0.07308;-11.81506;-1.74714;,
 -0.07308;-11.83045;-1.27246;,
 -0.07308;0.01305;-0.25993;,
 -0.07308;-0.46164;0.99758;,
 -0.07308;-11.81506;1.28678;,
 -0.07308;-11.83045;-0.25993;,
 -0.07308;-5.21088;-1.74714;,
 -0.07308;-3.72514;2.23674;,
 -0.29729;-11.83045;-1.27246;,
 -0.29729;-11.81506;-1.74714;,
 -0.29729;-11.81506;1.28678;,
 -0.29729;-11.83045;-0.25993;;
 
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
 4;32,5,4,33;,
 4;32,33,6,8;,
 4;34,11,10,35;,
 4;36,14,6,33;,
 4;36,33,4,13;,
 4;36,13,16,37;,
 4;36,37,17,14;,
 4;38,39,21,23;,
 4;35,10,21,39;,
 4;32,8,26,40;,
 4;32,40,24,5;,
 4;40,26,11,34;,
 4;40,34,2,24;,
 4;38,23,30,41;,
 4;38,41,28,20;,
 4;41,30,17,37;,
 4;41,37,16,28;,
 4;42,0,2,43;,
 4;42,43,34,35;,
 4;44,20,19,45;,
 4;44,45,39,38;,
 4;45,19,0,42;,
 4;45,42,35,39;;
 
 MeshMaterialList {
  10;
  47;
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
   0.097600;0.000000;0.800000;1.000000;;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.952941;0.784314;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.429804;0.549020;0.627451;1.000000;;
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
  59;
  -0.016196;-0.999344;-0.032401;,
  -0.364354;0.383841;-0.848477;,
  0.230171;0.407305;-0.883812;,
  0.016196;-0.999344;-0.032401;,
  -0.367005;0.854760;-0.367005;,
  -0.386909;0.901097;0.195768;,
  0.192907;0.965209;0.176516;,
  0.182344;0.906939;-0.379754;,
  -0.559617;0.590482;0.581514;,
  -0.016825;-0.999792;0.011536;,
  0.016596;-0.999798;0.011300;,
  0.451378;0.662949;0.597291;,
  -0.016515;-0.999847;0.005768;,
  -0.016202;-0.999738;-0.016202;,
  0.016202;-0.999738;-0.016202;,
  0.016401;-0.999850;0.005650;,
  -0.032404;-0.999457;0.006031;,
  -0.907414;0.383969;0.170785;,
  -0.852211;0.374010;-0.365859;,
  -0.032401;-0.999344;-0.016196;,
  0.032401;-0.999344;-0.016196;,
  0.478322;0.649582;-0.590975;,
  0.791322;0.571913;0.216160;,
  0.032404;-0.999458;0.005873;,
  -0.382642;0.020209;-0.923676;,
  0.336142;0.025353;-0.941470;,
  -0.955362;0.013407;0.295134;,
  0.696243;0.089845;0.712161;,
  -0.988762;0.009017;0.149224;,
  -0.923831;0.011760;-0.382620;,
  0.904581;0.012593;-0.426115;,
  0.986610;0.025052;0.161161;,
  0.000000;-0.999475;-0.032405;,
  0.000000;0.401116;-0.916027;,
  0.000000;0.923878;-0.382688;,
  -0.009748;0.981694;0.190215;,
  0.000699;0.692564;0.721356;,
  0.000393;-0.999946;0.010400;,
  0.000197;-0.999987;0.005200;,
  0.000000;-0.999869;-0.016205;,
  0.000000;0.020039;-0.999799;,
  0.040509;0.116510;0.992363;,
  0.000000;-0.999475;-0.032405;,
  -0.000622;-0.999945;0.010479;,
  -0.000311;-0.999986;0.005240;,
  0.000000;-0.999869;-0.016205;,
  -0.382677;0.003387;-0.923876;,
  -0.923847;0.008178;-0.382674;,
  0.923880;-0.000813;-0.382681;,
  0.382686;-0.000337;-0.923879;,
  -0.989507;0.001854;0.144473;,
  -0.958243;-0.005183;0.285908;,
  0.737548;-0.058024;0.672798;,
  0.992723;-0.012274;0.119790;,
  0.999961;-0.008855;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.058421;-0.099067;0.993364;,
  -0.212889;0.119980;0.969682;,
  -0.210891;-0.112532;0.971011;;
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
  4;24,29,18,1;,
  4;25,2,21,30;,
  4;25,30,48,49;,
  4;26,8,17,28;,
  4;26,28,50,51;,
  4;27,52,53,31;,
  4;27,31,22,11;,
  4;28,17,18,29;,
  4;28,29,47,50;,
  4;30,54,22,31;,
  4;30,31,53,48;,
  4;33,1,4,34;,
  4;33,34,7,2;,
  4;32,3,14,39;,
  4;35,6,7,34;,
  4;35,34,4,5;,
  4;35,5,8,36;,
  4;35,36,11,6;,
  4;37,38,15,10;,
  4;39,14,15,38;,
  4;33,2,25,40;,
  4;33,40,24,1;,
  4;40,25,49,55;,
  4;40,55,46,24;,
  4;56,52,27,41;,
  4;56,41,57,58;,
  4;41,27,11,36;,
  4;41,36,8,57;,
  4;45,13,0,42;,
  4;45,42,32,39;,
  4;43,9,12,44;,
  4;43,44,38,37;,
  4;44,12,13,45;,
  4;44,45,39,38;;
 }
 MeshTextureCoords {
  46;
  0.798983;3.329735;,
  0.794572;3.328436;,
  0.812921;3.328436;,
  0.789662;2.369815;,
  0.793689;2.329735;,
  0.808126;2.369815;,
  0.828831;2.329735;,
  0.879936;2.369815;,
  0.850722;2.369815;,
  0.887396;3.328436;,
  0.861480;3.329735;,
  0.883062;3.328436;,
  0.765360;2.369815;,
  0.766986;2.329735;,
  0.782259;2.329735;,
  0.811213;2.369815;,
  0.733796;2.369815;,
  0.702665;2.369815;,
  0.765181;3.328436;,
  0.766767;3.329735;,
  0.724528;3.328436;,
  0.793518;3.329735;,
  0.809042;3.328436;,
  0.683080;3.328436;,
  0.813662;2.770815;,
  0.795073;2.770815;,
  0.883333;2.770815;,
  0.887769;2.770815;,
  0.694652;2.645367;,
  0.765360;2.770815;,
  0.654861;2.645367;,
  0.809297;2.770815;,
  0.827777;2.369815;,
  0.809404;2.329735;,
  0.834589;3.328436;,
  0.817010;3.329735;,
  0.773536;2.329735;,
  0.715204;2.369815;,
  0.702515;3.328436;,
  0.773536;3.329735;,
  0.834589;2.770815;,
  0.665411;2.645367;,
  0.813084;3.329735;,
  0.829963;3.328436;,
  0.705456;3.328436;,
  0.772017;3.329735;;
 }
}
