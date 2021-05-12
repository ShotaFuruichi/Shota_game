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
 44;
 9.12416;-0.39993;-0.55978;,
 0.62936;-0.71264;-0.55978;,
 0.62936;0.63486;-0.55978;,
 9.12416;0.32216;-0.55978;,
 0.62936;-1.01264;-0.25978;,
 9.12416;-0.69993;-0.25978;,
 0.32936;0.63486;-0.25978;,
 0.32936;-0.71264;-0.25978;,
 9.12416;0.62216;-0.25978;,
 0.62936;0.93486;-0.25978;,
 9.13388;-0.39993;-0.25978;,
 9.13388;0.32216;-0.25978;,
 0.32936;-0.71264;0.25978;,
 0.32936;0.63486;0.25978;,
 0.62936;-1.01264;0.25978;,
 0.62936;0.63486;0.55978;,
 0.62936;-0.71264;0.55978;,
 0.62936;0.93486;0.25978;,
 9.12416;-0.39993;0.55978;,
 9.12416;0.32216;0.55978;,
 9.12416;-0.69993;0.25978;,
 9.13388;0.32216;0.25978;,
 9.13388;-0.39993;0.25978;,
 9.12416;0.62216;0.25978;,
 8.21240;-1.02676;-0.58257;,
 0.01449;-1.56803;-0.58257;,
 0.01449;0.66393;-0.58257;,
 8.21240;0.33604;-0.58257;,
 0.01449;-2.08729;-0.27035;,
 8.21240;-1.54604;-0.27035;,
 -0.29772;0.76435;-0.27035;,
 -0.29772;-1.56803;-0.27035;,
 8.21240;0.74236;-0.27035;,
 0.01449;1.07022;-0.27035;,
 -0.29772;-1.56803;0.27035;,
 -0.29772;0.76435;0.27035;,
 0.01449;-2.08729;0.27035;,
 0.01449;0.90240;0.58257;,
 0.01449;-1.56803;0.58257;,
 0.01449;1.07022;0.27035;,
 8.21240;-1.02676;0.58257;,
 8.21240;0.36112;0.58257;,
 8.21240;-1.54604;0.27035;,
 8.21240;0.74236;0.27035;;
 
 61;
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
 3;28,31,25;,
 3;30,33,26;,
 4;31,34,35,30;,
 4;36,34,31,28;,
 4;37,35,34,38;,
 4;33,30,35,39;,
 3;36,38,34;,
 3;37,39,35;,
 4;38,40,41,37;,
 4;42,40,38,36;,
 4;39,37,41,43;,
 4;42,36,28,29;,
 4;32,33,39,43;,
 4;37,41,40,38;,
 4;27,26,25,24;,
 4;29,24,25,28;,
 4;31,25,26,30;,
 4;33,26,27,32;,
 3;25,31,28;,
 3;26,33,30;,
 4;30,35,34,31;,
 4;28,31,34,36;,
 4;38,34,35,37;,
 4;39,35,30,33;,
 3;34,38,36;,
 3;35,39,37;,
 4;36,38,40,42;,
 4;43,41,37,39;,
 4;29,28,36,42;,
 4;43,39,33,32;,
 4;38,40,41,37;;
 
 MeshMaterialList {
  9;
  61;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.000000;0.031200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.476800;0.476800;1.000000;;
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
    "C:\\Users\\student\\Desktop\\�X�J�[�g.jpg";
   }
  }
  Material {
   0.304314;0.153725;0.175686;1.000000;;
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
  72;
  0.014083;-0.382581;-0.923815;,
  -0.360572;-0.367959;-0.857085;,
  -0.360572;0.367959;-0.857085;,
  0.014083;0.382581;-0.923815;,
  -0.854763;-0.367001;-0.367001;,
  -0.854763;-0.367001;0.367001;,
  -0.854763;0.367001;0.367001;,
  -0.854763;0.367001;-0.367001;,
  -0.360572;-0.367959;0.857085;,
  0.014083;-0.382581;0.923815;,
  0.014083;0.382581;0.923815;,
  -0.360572;0.367959;0.857085;,
  0.999738;-0.016191;0.016191;,
  0.999738;-0.016191;-0.016191;,
  0.999738;0.016191;-0.016191;,
  0.999738;0.016191;0.016191;,
  0.033989;-0.923319;0.382527;,
  -0.351408;-0.860262;0.369406;,
  -0.351408;-0.860262;-0.369406;,
  0.033989;-0.923319;-0.382527;,
  0.033989;0.923319;-0.382527;,
  -0.351408;0.860262;-0.369406;,
  -0.351408;0.860262;0.369406;,
  0.033989;0.923319;0.382527;,
  0.999345;-0.016185;-0.032378;,
  0.999345;0.016185;-0.032378;,
  0.999345;-0.032378;-0.016185;,
  0.999345;0.032378;-0.016185;,
  0.999345;0.016185;0.032378;,
  0.999345;-0.016185;0.032378;,
  0.999345;-0.032378;0.016185;,
  0.999345;0.032378;0.016185;,
  0.017646;-0.267264;-0.963462;,
  -0.368509;-0.252267;-0.894741;,
  -0.333749;0.316159;-0.888063;,
  0.012866;0.321696;-0.946756;,
  -0.891614;-0.251424;-0.376577;,
  -0.891614;-0.251424;0.376577;,
  -0.868768;0.392099;0.302490;,
  -0.843446;0.357518;-0.400972;,
  -0.293579;-0.200973;0.934570;,
  0.011714;-0.177416;0.984066;,
  0.014293;0.280904;0.959629;,
  -0.315741;0.343712;0.884404;,
  0.057359;-0.868774;0.491875;,
  -0.442841;-0.761003;0.474095;,
  -0.442841;-0.761003;-0.474095;,
  0.057359;-0.868774;-0.491875;,
  0.035851;0.896396;-0.441802;,
  -0.337256;0.835996;-0.432862;,
  -0.359693;0.889897;0.280544;,
  0.042073;0.940432;0.337369;,
  0.396415;-0.431533;-0.810330;,
  -0.021704;-0.426547;-0.904205;,
  -0.017646;0.267264;-0.963462;,
  0.368509;0.252267;-0.894741;,
  -0.012866;-0.321696;0.946756;,
  0.333749;-0.316159;0.888063;,
  0.368509;0.252267;0.894741;,
  -0.017646;0.267264;0.963462;,
  -0.057359;0.868774;0.491875;,
  0.442841;0.761003;0.474095;,
  0.891614;0.251424;0.376577;,
  0.843446;-0.357518;0.400972;,
  0.337256;-0.835996;0.432862;,
  -0.035851;-0.896396;0.441802;,
  0.868768;-0.392099;-0.302490;,
  0.891614;0.251424;-0.376577;,
  0.442841;0.761003;-0.474095;,
  0.359693;-0.889897;-0.280544;,
  -0.057359;0.868774;-0.491875;,
  -0.042073;-0.940432;-0.337369;;
  61;
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
  4;46,33,32,47;,
  4;39,34,33,36;,
  4;48,35,34,49;,
  3;46,36,33;,
  3;39,49,34;,
  4;36,37,38,39;,
  4;45,37,36,46;,
  4;43,38,37,40;,
  4;49,39,38,50;,
  3;45,40,37;,
  3;43,50,38;,
  4;40,41,42,43;,
  4;44,41,40,45;,
  4;50,43,42,51;,
  4;44,45,46,47;,
  4;48,49,50,51;,
  4;52,53,54,55;,
  4;56,57,58,59;,
  4;60,59,58,61;,
  4;62,58,57,63;,
  4;64,57,56,65;,
  3;58,62,61;,
  3;57,64,63;,
  4;63,66,67,62;,
  4;61,62,67,68;,
  4;55,67,66,52;,
  4;69,66,63,64;,
  3;67,55,68;,
  3;66,69,52;,
  4;68,55,54,70;,
  4;71,53,52,69;,
  4;60,61,68,70;,
  4;71,69,64,65;,
  4;40,41,42,43;;
 }
 MeshTextureCoords {
  44;
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
  0.000000;0.000000;;
 }
}
