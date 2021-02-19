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
 10.50316;89.68799;-65.28021;,
 -39.55141;113.28306;6.78481;,
 55.32876;125.00248;-9.58023;,
 55.32876;125.00248;-9.58023;,
 -39.55141;113.28306;6.78481;,
 58.50605;102.01332;52.61482;,
 -39.55141;113.28306;6.78481;,
 4.17790;52.80280;71.52025;,
 58.50605;102.01332;52.61482;,
 -39.55141;113.28306;6.78481;,
 -51.66909;51.53921;-59.49503;,
 -54.71868;18.06731;9.35373;,
 10.50316;89.68799;-65.28021;,
 -51.66909;51.53921;-59.49503;,
 -39.55141;113.28306;6.78481;,
 10.50316;89.68799;-65.28021;,
 55.32876;125.00248;-9.58023;,
 73.46808;49.70300;-34.78078;,
 55.32876;125.00248;-9.58023;,
 58.50605;102.01332;52.61482;,
 73.46808;49.70300;-34.78078;,
 -39.55141;113.28306;6.78481;,
 -54.71868;18.06731;9.35373;,
 4.17790;52.80280;71.52025;,
 50.71954;14.17293;18.12442;,
 73.46808;49.70300;-34.78078;,
 58.50605;102.01332;52.61482;,
 4.17790;52.80280;71.52025;,
 50.71954;14.17293;18.12442;,
 58.50605;102.01332;52.61482;,
 10.50316;89.68799;-65.28021;,
 -5.22717;1.70432;-49.25250;,
 -51.66909;51.53921;-59.49503;,
 73.46808;49.70300;-34.78078;,
 -5.22717;1.70432;-49.25250;,
 10.50316;89.68799;-65.28021;,
 50.71954;14.17293;18.12442;,
 -54.71868;18.06731;9.35373;,
 -5.22717;1.70432;-49.25250;,
 50.71954;14.17293;18.12442;,
 -5.22717;1.70432;-49.25250;,
 73.46808;49.70300;-34.78078;,
 -54.71868;18.06731;9.35373;,
 50.71954;14.17293;18.12442;,
 4.17790;52.80280;71.52025;,
 -5.22717;1.70432;-49.25250;,
 -54.71868;18.06731;9.35373;,
 -51.66909;51.53921;-59.49503;;
 
 16;
 3;0,1,2;,
 3;3,4,5;,
 3;6,7,8;,
 3;9,10,11;,
 3;12,13,14;,
 3;15,16,17;,
 3;18,19,20;,
 3;21,22,23;,
 3;24,25,26;,
 3;27,28,29;,
 3;30,31,32;,
 3;33,34,35;,
 3;36,37,38;,
 3;39,40,41;,
 3;42,43,44;,
 3;45,46,47;;
 
 MeshMaterialList {
  4;
  16;
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
   0.000000;0.800000;0.414400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.615200;0.000000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.354400;0.000000;1.000000;;
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
 }
 MeshNormals {
  20;
  -0.333345;0.802790;-0.494378;,
  -0.128878;0.990949;-0.037556;,
  -0.175801;0.800489;0.572985;,
  -0.303457;0.952045;0.039051;,
  -0.827157;0.478569;-0.294591;,
  0.974365;0.160468;-0.157678;,
  0.795085;-0.281430;0.537250;,
  -0.921462;0.156377;0.355604;,
  0.325239;-0.450224;-0.831575;,
  -0.550857;0.390957;0.737367;,
  0.329307;-0.009204;-0.944178;,
  0.863884;0.334220;-0.376831;,
  0.914515;-0.114639;0.387969;,
  0.272576;-0.650933;0.708512;,
  0.020675;-0.182756;-0.982941;,
  0.468545;-0.562906;-0.680883;,
  0.151843;-0.972884;0.174475;,
  -0.294471;-0.942995;0.155072;,
  -0.390126;-0.917848;-0.073187;,
  -0.645715;-0.675086;-0.356805;;
  16;
  3;0,3,1;,
  3;1,3,2;,
  3;3,9,2;,
  3;7,4,7;,
  3;0,4,3;,
  3;10,11,5;,
  3;11,12,5;,
  3;7,7,9;,
  3;6,5,12;,
  3;13,6,12;,
  3;10,8,14;,
  3;15,8,10;,
  3;16,17,18;,
  3;16,8,15;,
  3;17,16,13;,
  3;18,17,19;;
 }
 MeshTextureCoords {
  48;
  0.492190;0.164060;,
  0.492190;0.171880;,
  0.484380;0.171880;,
  0.476560;0.179690;,
  0.476560;0.187500;,
  0.468750;0.187500;,
  0.476560;0.234380;,
  0.468750;0.242190;,
  0.468750;0.234380;,
  0.851560;0.367190;,
  0.851560;0.375000;,
  0.843750;0.375000;,
  0.867190;0.367190;,
  0.859380;0.375000;,
  0.859380;0.367190;,
  0.054690;0.421880;,
  0.054690;0.414060;,
  0.062500;0.414060;,
  0.250000;0.429690;,
  0.250000;0.437500;,
  0.242190;0.437500;,
  0.625000;0.460940;,
  0.625000;0.468750;,
  0.617190;0.468750;,
  0.281250;0.539060;,
  0.273440;0.539060;,
  0.281250;0.531250;,
  0.421880;0.507810;,
  0.414060;0.507810;,
  0.421880;0.500000;,
  0.007810;0.750000;,
  0.000000;0.757810;,
  0.000000;0.750000;,
  0.015620;0.757810;,
  0.007810;0.765620;,
  0.007810;0.757810;,
  0.007810;0.835940;,
  0.000000;0.835940;,
  0.007810;0.828120;,
  0.140620;0.773440;,
  0.132810;0.773440;,
  0.140620;0.765620;,
  0.539060;0.781250;,
  0.531250;0.781250;,
  0.539060;0.773440;,
  0.914060;0.781250;,
  0.906250;0.781250;,
  0.914060;0.773440;;
 }
}
