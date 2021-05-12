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
 135;
 0.00000;16.26922;0.00000;,
 4.69150;14.89302;-7.30012;,
 0.00000;14.89302;-8.67768;,
 7.89350;14.89302;-3.60484;,
 8.58934;14.89302;1.23496;,
 6.55814;14.89302;5.68266;,
 2.44478;14.89302;8.32616;,
 -2.44478;14.89302;8.32616;,
 -6.55816;14.89302;5.68266;,
 -8.58934;14.89302;1.23496;,
 -7.89350;14.89302;-3.60484;,
 -4.69150;14.89302;-7.30012;,
 8.45380;11.03702;-13.15438;,
 0.00000;11.03702;-15.63664;,
 14.22358;11.03702;-6.49568;,
 15.47748;11.03702;2.22532;,
 11.81738;11.03702;10.23982;,
 4.40534;11.03702;15.00324;,
 -4.40536;11.03702;15.00324;,
 -11.81738;11.03702;10.23982;,
 -15.47748;11.03702;2.22532;,
 -14.22358;11.03702;-6.49570;,
 -8.45380;11.03702;-13.15438;,
 0.00000;14.89302;-8.67768;,
 0.00000;11.03702;-15.63664;,
 10.54172;5.46492;-16.40322;,
 0.00000;5.46492;-19.49856;,
 17.73652;5.46492;-8.10000;,
 19.30010;5.46492;2.77494;,
 14.73602;5.46492;12.76884;,
 5.49338;5.46492;18.70874;,
 -5.49338;5.46492;18.70872;,
 -14.73602;5.46492;12.76884;,
 -19.30010;5.46492;2.77492;,
 -17.73652;5.46492;-8.10000;,
 -10.54172;5.46492;-16.40322;,
 0.00000;5.46492;-19.49856;,
 10.54172;-0.71962;-16.40322;,
 0.00000;-0.71962;-19.49856;,
 17.73652;-0.71962;-8.10000;,
 19.30010;-0.71962;2.77494;,
 14.73602;-0.71962;12.76884;,
 5.49338;-0.71962;18.70874;,
 -5.49338;-0.71962;18.70872;,
 -14.73602;-0.71962;12.76884;,
 -19.30010;-0.71962;2.77492;,
 -17.73652;-0.71962;-8.10000;,
 -10.54172;-0.71962;-16.40322;,
 0.00000;-0.71962;-19.49856;,
 0.00000;-0.46590;-19.38000;,
 10.47762;-0.46590;-16.30350;,
 10.47762;-0.47924;-16.30350;,
 0.00000;-0.47924;-19.38000;,
 17.62866;-0.46590;-8.05074;,
 17.62866;-0.47924;-8.05074;,
 19.18274;-0.46590;2.75806;,
 19.18274;-0.47924;2.75806;,
 14.64642;-0.46590;12.69120;,
 14.64642;-0.47924;12.69120;,
 5.45998;-0.46590;18.59498;,
 5.45998;-0.47924;18.59498;,
 -5.45998;-0.46590;18.59498;,
 -5.45998;-0.47924;18.59498;,
 -14.64644;-0.46590;12.69120;,
 -14.64644;-0.47924;12.69120;,
 -19.18274;-0.46590;2.75806;,
 -19.18274;-0.47924;2.75806;,
 -17.62866;-0.46590;-8.05074;,
 -17.62866;-0.47924;-8.05074;,
 -10.47762;-0.46590;-16.30350;,
 -10.47762;-0.47924;-16.30350;,
 0.00000;-0.46590;-19.38000;,
 0.00000;-0.47924;-19.38000;,
 10.47762;-0.49256;-16.30350;,
 0.00000;-0.49256;-19.38000;,
 17.62866;-0.49256;-8.05074;,
 19.18274;-0.49256;2.75806;,
 14.64642;-0.49256;12.69120;,
 5.45998;-0.49256;18.59498;,
 -5.45998;-0.49256;18.59498;,
 -14.64644;-0.49256;12.69120;,
 -19.18274;-0.49256;2.75806;,
 -17.62866;-0.49256;-8.05074;,
 -10.47762;-0.49256;-16.30350;,
 0.00000;-0.49256;-19.38000;,
 10.47762;-0.50590;-16.30350;,
 0.00000;-0.50590;-19.38000;,
 17.62866;-0.50590;-8.05074;,
 19.18274;-0.50590;2.75806;,
 14.64642;-0.50590;12.69120;,
 5.45998;-0.50590;18.59498;,
 -5.45998;-0.50590;18.59498;,
 -14.64644;-0.50590;12.69120;,
 -19.18274;-0.50590;2.75806;,
 -17.62866;-0.50590;-8.05074;,
 -10.47762;-0.50590;-16.30350;,
 0.00000;-0.50590;-19.38000;,
 10.47762;-0.51924;-16.30350;,
 0.00000;-0.51924;-19.38000;,
 17.62866;-0.51924;-8.05074;,
 19.18274;-0.51924;2.75806;,
 14.64642;-0.51924;12.69120;,
 5.45998;-0.51924;18.59498;,
 -5.45998;-0.51924;18.59498;,
 -14.64644;-0.51924;12.69120;,
 -19.18274;-0.51924;2.75806;,
 -17.62866;-0.51924;-8.05074;,
 -10.47762;-0.51924;-16.30350;,
 0.00000;-0.51924;-19.38000;,
 10.47762;-0.53256;-16.30350;,
 0.00000;-0.53256;-19.38000;,
 17.62866;-0.53256;-8.05074;,
 19.18274;-0.53256;2.75806;,
 14.64642;-0.53256;12.69120;,
 5.45998;-0.53256;18.59498;,
 -5.45998;-0.53256;18.59498;,
 -14.64644;-0.53256;12.69120;,
 -19.18274;-0.53256;2.75806;,
 -17.62866;-0.53256;-8.05074;,
 -10.47762;-0.53256;-16.30350;,
 0.00000;-0.53256;-19.38000;,
 10.47762;-0.54590;-16.30350;,
 0.00000;-0.54590;-19.38000;,
 17.62866;-0.54590;-8.05074;,
 19.18274;-0.54590;2.75806;,
 14.64642;-0.54590;12.69120;,
 5.45998;-0.54590;18.59498;,
 -5.45998;-0.54590;18.59498;,
 -14.64644;-0.54590;12.69120;,
 -19.18274;-0.54590;2.75806;,
 -17.62866;-0.54590;-8.05074;,
 -10.47762;-0.54590;-16.30350;,
 0.00000;-0.54590;-19.38000;,
 0.00000;-0.46590;-0.00000;,
 0.00000;-0.54590;-0.00000;;
 
 132;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,11,10;,
 3;0,2,11;,
 4;2,1,12,13;,
 4;1,3,14,12;,
 4;3,4,15,14;,
 4;4,5,16,15;,
 4;5,6,17,16;,
 4;6,7,18,17;,
 4;7,8,19,18;,
 4;8,9,20,19;,
 4;9,10,21,20;,
 4;10,11,22,21;,
 4;11,23,24,22;,
 4;13,12,25,26;,
 4;12,14,27,25;,
 4;14,15,28,27;,
 4;15,16,29,28;,
 4;16,17,30,29;,
 4;17,18,31,30;,
 4;18,19,32,31;,
 4;19,20,33,32;,
 4;20,21,34,33;,
 4;21,22,35,34;,
 4;22,24,36,35;,
 4;26,25,37,38;,
 4;25,27,39,37;,
 4;27,28,40,39;,
 4;28,29,41,40;,
 4;29,30,42,41;,
 4;30,31,43,42;,
 4;31,32,44,43;,
 4;32,33,45,44;,
 4;33,34,46,45;,
 4;34,35,47,46;,
 4;35,36,48,47;,
 4;49,50,51,52;,
 4;50,53,54,51;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 4;59,61,62,60;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;65,67,68,66;,
 4;67,69,70,68;,
 4;69,71,72,70;,
 4;52,51,73,74;,
 4;51,54,75,73;,
 4;54,56,76,75;,
 4;56,58,77,76;,
 4;58,60,78,77;,
 4;60,62,79,78;,
 4;62,64,80,79;,
 4;64,66,81,80;,
 4;66,68,82,81;,
 4;68,70,83,82;,
 4;70,72,84,83;,
 4;74,73,85,86;,
 4;73,75,87,85;,
 4;75,76,88,87;,
 4;76,77,89,88;,
 4;77,78,90,89;,
 4;78,79,91,90;,
 4;79,80,92,91;,
 4;80,81,93,92;,
 4;81,82,94,93;,
 4;82,83,95,94;,
 4;83,84,96,95;,
 4;86,85,97,98;,
 4;85,87,99,97;,
 4;87,88,100,99;,
 4;88,89,101,100;,
 4;89,90,102,101;,
 4;90,91,103,102;,
 4;91,92,104,103;,
 4;92,93,105,104;,
 4;93,94,106,105;,
 4;94,95,107,106;,
 4;95,96,108,107;,
 4;98,97,109,110;,
 4;97,99,111,109;,
 4;99,100,112,111;,
 4;100,101,113,112;,
 4;101,102,114,113;,
 4;102,103,115,114;,
 4;103,104,116,115;,
 4;104,105,117,116;,
 4;105,106,118,117;,
 4;106,107,119,118;,
 4;107,108,120,119;,
 4;110,109,121,122;,
 4;109,111,123,121;,
 4;111,112,124,123;,
 4;112,113,125,124;,
 4;113,114,126,125;,
 4;114,115,127,126;,
 4;115,116,128,127;,
 4;116,117,129,128;,
 4;117,118,130,129;,
 4;118,119,131,130;,
 4;119,120,132,131;,
 3;133,50,49;,
 3;133,53,50;,
 3;133,55,53;,
 3;133,57,55;,
 3;133,59,57;,
 3;133,61,59;,
 3;133,63,61;,
 3;133,65,63;,
 3;133,67,65;,
 3;133,69,67;,
 3;133,49,69;,
 3;134,122,121;,
 3;134,121,123;,
 3;134,123,124;,
 3;134,124,125;,
 3;134,125,126;,
 3;134,126,127;,
 3;134,127,128;,
 3;134,128,129;,
 3;134,129,130;,
 3;134,130,131;,
 3;134,131,122;;
 
 MeshMaterialList {
  1;
  132;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Stone.jpg";
   }
  }
 }
 MeshNormals {
  67;
  0.000000;1.000000;0.000000;,
  0.000000;0.945768;-0.324843;,
  0.175623;0.945768;-0.273275;,
  0.295487;0.945768;-0.134944;,
  0.321536;0.945768;0.046230;,
  0.245500;0.945768;0.212727;,
  0.091519;0.945768;0.311684;,
  -0.091519;0.945768;0.311684;,
  -0.245500;0.945768;0.212727;,
  -0.321537;0.945768;0.046230;,
  -0.295487;0.945768;-0.134945;,
  -0.175623;0.945768;-0.273275;,
  0.000000;0.743019;-0.669270;,
  0.361835;0.743020;-0.563025;,
  0.608789;0.743020;-0.278025;,
  0.662457;0.743020;0.095247;,
  0.505800;0.743020;0.438278;,
  0.188555;0.743020;0.642159;,
  -0.188555;0.743020;0.642160;,
  -0.505800;0.743019;0.438279;,
  -0.662457;0.743020;0.095247;,
  -0.608789;0.743020;-0.278025;,
  -0.361835;0.743019;-0.563026;,
  0.000000;0.300363;-0.953825;,
  0.515677;0.300363;-0.802409;,
  0.867629;0.300364;-0.396233;,
  0.944116;0.300364;0.135744;,
  0.720852;0.300364;0.624623;,
  0.268723;0.300364;0.915188;,
  -0.268724;0.300363;0.915188;,
  -0.720852;0.300363;0.624623;,
  -0.944116;0.300364;0.135744;,
  -0.867629;0.300364;-0.396234;,
  -0.515677;0.300363;-0.802409;,
  0.000000;0.000000;-1.000000;,
  0.540641;0.000000;-0.841254;,
  0.909632;0.000000;-0.415416;,
  0.989821;0.000000;0.142316;,
  0.755749;0.000000;0.654861;,
  0.281732;0.000000;0.959493;,
  -0.281733;0.000000;0.959493;,
  -0.755749;0.000000;0.654861;,
  -0.989821;0.000000;0.142315;,
  -0.909632;0.000000;-0.415416;,
  -0.540641;0.000000;-0.841254;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.540641;0.000000;-0.841253;,
  0.909632;0.000000;-0.415415;,
  0.989821;0.000000;0.142315;,
  0.755750;0.000000;0.654861;,
  0.281733;0.000000;0.959493;,
  -0.281733;0.000000;0.959493;,
  -0.755750;0.000000;0.654860;,
  -0.989822;0.000000;0.142314;,
  -0.909632;0.000000;-0.415415;,
  -0.540641;0.000000;-0.841253;,
  0.989821;0.000000;0.142315;,
  0.755750;0.000000;0.654861;,
  0.281733;0.000000;0.959493;,
  -0.755750;0.000000;0.654860;,
  -0.989822;0.000000;0.142314;,
  -0.909632;0.000000;-0.415415;,
  -0.540641;0.000000;-0.841253;,
  -0.989822;0.000000;0.142314;,
  -0.909632;0.000000;-0.415415;,
  0.000000;-1.000000;-0.000000;;
  132;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,1,11;,
  4;1,2,13,12;,
  4;2,3,14,13;,
  4;3,4,15,14;,
  4;4,5,16,15;,
  4;5,6,17,16;,
  4;6,7,18,17;,
  4;7,8,19,18;,
  4;8,9,20,19;,
  4;9,10,21,20;,
  4;10,11,22,21;,
  4;11,1,12,22;,
  4;12,13,24,23;,
  4;13,14,25,24;,
  4;14,15,26,25;,
  4;15,16,27,26;,
  4;16,17,28,27;,
  4;17,18,29,28;,
  4;18,19,30,29;,
  4;19,20,31,30;,
  4;20,21,32,31;,
  4;21,22,33,32;,
  4;22,12,23,33;,
  4;23,24,35,34;,
  4;24,25,36,35;,
  4;25,26,37,36;,
  4;26,27,38,37;,
  4;27,28,39,38;,
  4;28,29,40,39;,
  4;29,30,41,40;,
  4;30,31,42,41;,
  4;31,32,43,42;,
  4;32,33,44,43;,
  4;33,23,34,44;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,57,48;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,52,59;,
  4;52,53,60,52;,
  4;53,54,61,60;,
  4;54,55,62,61;,
  4;55,56,63,62;,
  4;56,46,46,63;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,57,57,48;,
  4;57,58,50,57;,
  4;58,59,59,50;,
  4;59,52,52,59;,
  4;52,60,60,52;,
  4;60,61,64,60;,
  4;61,62,65,64;,
  4;62,63,56,65;,
  4;63,46,46,56;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,57,49,48;,
  4;57,50,50,49;,
  4;50,59,51,50;,
  4;59,52,52,51;,
  4;52,60,60,52;,
  4;60,64,61,60;,
  4;64,65,55,61;,
  4;65,56,56,55;,
  4;56,46,46,56;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,49,57,48;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,52,59;,
  4;52,60,60,52;,
  4;60,61,61,60;,
  4;61,55,62,61;,
  4;55,56,63,62;,
  4;56,46,46,63;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,57,57,48;,
  4;57,58,50,57;,
  4;58,59,59,50;,
  4;59,52,52,59;,
  4;52,60,60,52;,
  4;60,61,64,60;,
  4;61,62,65,64;,
  4;62,63,56,65;,
  4;63,46,46,56;,
  4;46,47,47,46;,
  4;47,48,48,47;,
  4;48,57,49,48;,
  4;57,50,50,49;,
  4;50,59,51,50;,
  4;59,52,52,51;,
  4;52,60,53,52;,
  4;60,64,54,53;,
  4;64,65,55,54;,
  4;65,56,56,55;,
  4;56,46,46,56;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;,
  3;66,66,66;;
 }
 MeshTextureCoords {
  135;
  0.500000;0.005471;,
  0.094224;0.126179;,
  0.000000;0.125652;,
  0.187959;0.127884;,
  0.280145;0.130720;,
  0.369762;0.133878;,
  0.456922;0.135982;,
  0.543078;0.135982;,
  0.630238;0.133878;,
  0.719855;0.130720;,
  0.812041;0.127884;,
  0.905776;0.126179;,
  0.092381;0.298326;,
  0.000000;0.298158;,
  0.184921;0.299171;,
  0.276960;0.301117;,
  0.367434;0.303677;,
  0.456080;0.305513;,
  0.543920;0.305513;,
  0.632565;0.303677;,
  0.723040;0.301117;,
  0.815080;0.299171;,
  0.907619;0.298326;,
  1.000000;0.125652;,
  1.000000;0.298158;,
  0.091936;0.521993;,
  0.000000;0.521999;,
  0.184178;0.521920;,
  0.276170;0.521703;,
  0.366850;0.521391;,
  0.455867;0.521161;,
  0.544133;0.521161;,
  0.633150;0.521391;,
  0.723830;0.521703;,
  0.815822;0.521920;,
  0.908064;0.521993;,
  1.000000;0.521999;,
  0.091936;0.714209;,
  0.000000;0.714250;,
  0.184178;0.713693;,
  0.276170;0.712147;,
  0.366850;0.709907;,
  0.455867;0.708235;,
  0.544133;0.708235;,
  0.633150;0.709907;,
  0.723830;0.712147;,
  0.815822;0.713693;,
  0.908064;0.714209;,
  1.000000;0.714250;,
  0.000000;0.709310;,
  0.091946;0.709266;,
  0.091946;0.709581;,
  0.000000;0.709625;,
  0.184196;0.708746;,
  0.184196;0.709061;,
  0.276190;0.707201;,
  0.276190;0.707514;,
  0.366864;0.704970;,
  0.366864;0.705282;,
  0.455872;0.703307;,
  0.455872;0.703618;,
  0.544128;0.703307;,
  0.544128;0.703618;,
  0.633136;0.704969;,
  0.633136;0.705282;,
  0.723810;0.707201;,
  0.723810;0.707514;,
  0.815804;0.708746;,
  0.815804;0.709061;,
  0.908054;0.709266;,
  0.908054;0.709581;,
  1.000000;0.709310;,
  1.000000;0.709625;,
  0.091946;0.709895;,
  0.000000;0.709939;,
  0.184196;0.709374;,
  0.276190;0.707827;,
  0.366864;0.705594;,
  0.455872;0.703929;,
  0.544128;0.703929;,
  0.633136;0.705594;,
  0.723810;0.707827;,
  0.815804;0.709374;,
  0.908054;0.709895;,
  1.000000;0.709939;,
  0.091946;0.710209;,
  0.000000;0.710253;,
  0.184196;0.709688;,
  0.276190;0.708140;,
  0.366864;0.705905;,
  0.455872;0.704239;,
  0.544128;0.704239;,
  0.633136;0.705905;,
  0.723810;0.708140;,
  0.815804;0.709688;,
  0.908054;0.710209;,
  1.000000;0.710253;,
  0.091946;0.710522;,
  0.000000;0.710566;,
  0.184196;0.710001;,
  0.276190;0.708452;,
  0.366864;0.706216;,
  0.455872;0.704550;,
  0.544128;0.704550;,
  0.633136;0.706216;,
  0.723810;0.708452;,
  0.815804;0.710001;,
  0.908054;0.710522;,
  1.000000;0.710566;,
  0.091946;0.710835;,
  0.000000;0.710879;,
  0.184196;0.710313;,
  0.276190;0.708764;,
  0.366864;0.706527;,
  0.455872;0.704859;,
  0.544128;0.704859;,
  0.633136;0.706526;,
  0.723810;0.708764;,
  0.815804;0.710313;,
  0.908054;0.710835;,
  1.000000;0.710879;,
  0.091946;0.711147;,
  0.000000;0.711191;,
  0.184196;0.710625;,
  0.276190;0.709075;,
  0.366864;0.706837;,
  0.455872;0.705168;,
  0.544128;0.705168;,
  0.633136;0.706837;,
  0.723810;0.709075;,
  0.815804;0.710625;,
  0.908054;0.711147;,
  1.000000;0.711191;,
  0.500000;0.991428;,
  0.500000;0.991532;;
 }
}
