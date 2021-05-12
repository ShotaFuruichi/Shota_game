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
 67;
 0.00000;0.57250;-3.10404;,
 -0.02417;0.57085;-0.47727;,
 -1.50279;-0.00993;-2.87390;,
 -2.88978;2.43042;-4.40227;,
 0.00000;3.73587;-3.50801;,
 -1.50279;-0.00993;-2.87390;,
 -0.02417;0.57085;-0.47727;,
 -3.34855;-0.00993;-2.16409;,
 -4.58142;2.43042;-3.23979;,
 -3.34855;-0.00993;-2.16409;,
 -0.02417;0.57085;-0.47727;,
 -4.36286;-0.00993;-1.11826;,
 -5.59989;2.43042;-1.52703;,
 -4.36286;-0.00993;-1.11826;,
 -0.02417;0.57085;-0.47727;,
 -4.57490;-0.00993;0.08274;,
 -5.94716;2.43042;0.43986;,
 -4.57490;-0.00993;0.08274;,
 -0.02417;0.57085;-0.47727;,
 -3.94803;-0.00993;1.23125;,
 -4.92052;2.43042;2.32079;,
 -3.94803;-0.00993;1.23125;,
 -0.02417;0.57085;-0.47727;,
 -1.90879;-0.00993;2.12868;,
 -3.34015;2.43042;3.06750;,
 -1.90879;-0.00993;2.12868;,
 -0.02417;0.57085;-0.47727;,
 -1.43246;-0.00993;2.61986;,
 -1.30124;2.43042;3.87191;,
 1.58779;-0.00993;2.61986;,
 2.23024;-0.00993;2.12868;,
 3.15376;2.43042;3.06750;,
 1.66114;2.43042;3.87191;,
 2.23024;-0.00993;2.12868;,
 4.04754;-0.00993;1.23125;,
 4.73413;2.43042;2.32079;,
 4.04754;-0.00993;1.23125;,
 4.67441;-0.00993;0.08274;,
 5.76077;2.43042;0.43986;,
 4.67441;-0.00993;0.08274;,
 4.46237;-0.00993;-1.11826;,
 5.41350;2.43042;-1.52703;,
 4.46237;-0.00993;-1.11826;,
 3.44806;-0.00993;-2.16409;,
 4.39503;2.43042;-3.23979;,
 3.44806;-0.00993;-2.16409;,
 1.59875;-0.00993;-2.87390;,
 2.73553;2.43042;-4.40227;,
 0.00000;0.60582;3.20465;,
 1.58779;-0.00993;2.61986;,
 0.00000;3.73587;3.87191;,
 -1.43246;-0.00993;2.61986;,
 0.00000;0.60582;3.20465;,
 -0.02417;0.57085;-0.47727;,
 0.00000;0.57250;-3.10404;,
 1.59875;-0.00993;-2.87390;,
 -0.02417;0.57085;-0.47727;,
 0.00000;3.73587;-3.48750;,
 0.00000;0.57250;-3.10404;,
 0.00000;3.73587;-3.50801;,
 -0.02417;0.57085;-0.47727;,
 -0.02417;0.57085;-0.47727;,
 -0.02417;0.57085;-0.47727;,
 -0.02417;0.57085;-0.47727;,
 -0.02417;0.57085;-0.47727;,
 0.00000;0.60582;3.20465;,
 -0.02417;0.57085;-0.47727;;
 
 32;
 3;0,1,2;,
 4;0,2,3,4;,
 3;5,6,7;,
 4;5,7,8,3;,
 3;9,10,11;,
 4;9,11,12,8;,
 3;13,14,15;,
 4;13,15,16,12;,
 3;17,18,19;,
 4;17,19,20,16;,
 3;21,22,23;,
 4;21,23,24,20;,
 3;25,26,27;,
 4;25,27,28,24;,
 4;29,30,31,32;,
 4;33,34,35,31;,
 4;36,37,38,35;,
 4;39,40,41,38;,
 4;42,43,44,41;,
 4;45,46,47,44;,
 4;48,49,32,50;,
 4;48,50,28,51;,
 4;52,53,30,29;,
 3;54,55,56;,
 4;54,57,47,55;,
 3;58,59,57;,
 3;60,40,39;,
 3;61,37,36;,
 3;62,34,33;,
 3;63,43,42;,
 3;64,46,45;,
 3;65,51,66;;
 
 MeshMaterialList {
  12;
  32;
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.768800;0.000000;1.000000;;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.796863;0.401569;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.269600;0.135200;0.800000;1.000000;;
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
    "data\\TEXTURE\\Bomb.jpg";
   }
  }
  Material {
   0.310588;0.310588;0.310588;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.053333;0.040784;0.373333;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  36;
  0.208840;-0.320727;-0.923862;,
  -0.091266;-0.481525;-0.871667;,
  -0.541448;-0.558496;-0.628424;,
  -0.794383;-0.500685;-0.343905;,
  -0.854584;-0.500708;0.137760;,
  -0.584178;-0.516590;0.625996;,
  -0.416408;-0.503312;0.757154;,
  -0.236556;-0.434560;0.869022;,
  0.247461;-0.408029;0.878792;,
  0.435847;-0.454973;0.776555;,
  0.615512;-0.456989;0.642110;,
  0.896044;-0.419961;0.144009;,
  0.830519;-0.425919;-0.358930;,
  0.563064;-0.512714;-0.648138;,
  0.092733;-0.466642;-0.879571;,
  0.010640;-0.999943;-0.000530;,
  0.221091;-0.970244;0.098717;,
  0.094733;-0.983825;0.152036;,
  0.122568;-0.990160;0.067523;,
  0.124033;-0.992057;-0.020942;,
  0.095979;-0.988643;-0.115642;,
  0.101385;-0.984076;-0.145997;,
  0.264150;-0.962589;-0.060395;,
  -0.219373;-0.320824;-0.921383;,
  0.005371;-0.334688;0.942314;,
  0.021855;-0.999760;0.001151;,
  -0.005392;-0.328391;-0.944526;,
  0.084638;-0.995989;-0.029008;,
  -0.154701;-0.982043;-0.107976;,
  -0.232145;-0.970753;-0.061213;,
  -0.210000;-0.973207;0.093634;,
  1.000000;0.000000;0.000000;,
  -0.118882;-0.990741;0.065574;,
  -0.120258;-0.992534;-0.020362;,
  -0.095631;-0.989491;-0.108453;,
  -0.092393;-0.984542;0.148796;;
  32;
  3;15,25,16;,
  4;26,1,1,0;,
  3;16,25,17;,
  4;1,2,2,1;,
  3;17,25,18;,
  4;2,3,3,2;,
  3;18,25,19;,
  4;3,4,4,3;,
  3;19,25,20;,
  4;4,5,5,4;,
  3;20,25,21;,
  4;5,6,6,5;,
  3;21,25,22;,
  4;6,7,7,6;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;24,8,8,24;,
  4;24,24,7,7;,
  4;27,25,28,29;,
  3;15,30,25;,
  4;26,23,14,14;,
  3;31,31,31;,
  3;25,32,33;,
  3;25,33,34;,
  3;25,34,28;,
  3;25,35,32;,
  3;25,30,35;,
  3;27,22,25;;
 }
 MeshTextureCoords {
  67;
  0.012890;0.834960;,
  0.033110;0.576160;,
  0.053600;0.834960;,
  0.066670;1.000000;,
  0.000000;1.000000;,
  0.074060;0.832390;,
  0.085650;0.569550;,
  0.114770;0.832390;,
  0.133330;1.000000;,
  0.135140;0.832390;,
  0.137970;0.569550;,
  0.175850;0.832390;,
  0.200000;1.000000;,
  0.196220;0.832390;,
  0.190290;0.569550;,
  0.236930;0.832390;,
  0.266670;1.000000;,
  0.257300;0.832390;,
  0.242610;0.569550;,
  0.298000;0.832390;,
  0.333330;1.000000;,
  0.318380;0.832390;,
  0.294920;0.569550;,
  0.359080;0.832390;,
  0.400000;1.000000;,
  0.380060;0.834960;,
  0.348790;0.576160;,
  0.420770;0.834960;,
  0.466670;1.000000;,
  0.501610;0.832390;,
  0.542320;0.832390;,
  0.600000;1.000000;,
  0.533330;1.000000;,
  0.562700;0.832390;,
  0.603400;0.832390;,
  0.666670;1.000000;,
  0.623780;0.832390;,
  0.664480;0.832390;,
  0.733330;1.000000;,
  0.684850;0.832390;,
  0.725560;0.832390;,
  0.800000;1.000000;,
  0.745930;0.832390;,
  0.786640;0.832390;,
  0.866670;1.000000;,
  0.807020;0.832390;,
  0.847720;0.832390;,
  0.933330;1.000000;,
  0.464726;0.834960;,
  0.481760;0.834960;,
  0.499021;1.000000;,
  0.441050;0.834960;,
  0.459793;0.611374;,
  0.458324;0.588277;,
  0.906695;0.834960;,
  0.869380;0.834960;,
  0.777237;0.597161;,
  0.996674;1.000000;,
  0.908392;0.834960;,
  1.000000;1.000000;,
  0.612219;0.578748;,
  0.559692;0.579227;,
  0.508241;0.584098;,
  0.665570;0.580334;,
  0.721081;0.586294;,
  0.439242;0.726151;,
  0.400890;0.576160;;
 }
}
