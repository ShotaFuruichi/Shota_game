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
 24;
 -1.43786;-1.41031;-5.92071;,
 -1.86646;-2.50288;-6.57833;,
 -1.86646;-2.50288;0.25505;,
 -1.86646;-0.32394;0.25505;,
 -1.34978;-2.50288;-7.01442;,
 -0.92118;-1.41031;-6.35679;,
 -1.34978;-2.86009;0.25505;,
 -1.34978;-2.86009;-6.57833;,
 -1.34978;-0.32394;0.69112;,
 -1.34978;-2.50288;0.69112;,
 -0.92118;-1.05309;-5.92071;,
 -1.34978;0.03328;0.25505;,
 0.94651;-1.05309;-5.92071;,
 1.23435;0.03328;0.25505;,
 0.94651;-1.41031;-6.35679;,
 1.23435;-0.32394;0.69112;,
 1.46319;-1.41031;-5.92071;,
 1.75103;-0.32394;0.25505;,
 1.75103;-2.50289;-6.57833;,
 1.75103;-2.50289;0.25505;,
 1.23435;-2.50289;-7.01442;,
 1.23435;-2.50289;0.69112;,
 1.23435;-2.86011;-6.57833;,
 1.23435;-2.86011;0.25505;;
 
 26;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;6,2,1,7;,
 4;8,3,2,9;,
 4;10,0,3,11;,
 3;10,5,0;,
 3;4,7,1;,
 3;6,9,2;,
 3;8,11,3;,
 4;12,10,11,13;,
 4;5,10,12,14;,
 4;15,13,11,8;,
 4;16,12,13,17;,
 3;16,14,12;,
 3;15,17,13;,
 4;18,16,17,19;,
 4;14,16,18,20;,
 4;21,19,17,15;,
 4;22,18,19,23;,
 3;22,20,18;,
 3;21,23,19;,
 4;7,22,23,6;,
 4;20,22,7,4;,
 4;9,6,23,21;,
 4;4,5,14,20;,
 4;15,8,9,21;;
 
 MeshMaterialList {
  12;
  26;
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
    "���f��_��2\\Bomb.jpg";
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
  30;
  -0.690993;0.614644;-0.380449;,
  -0.830749;0.422503;-0.362419;,
  -0.835520;-0.197566;0.512713;,
  -0.797705;0.503338;0.332142;,
  0.275941;0.869233;-0.410232;,
  -0.275373;0.868012;-0.413188;,
  -0.293649;0.925621;0.238740;,
  0.293586;0.924815;0.241918;,
  0.852746;0.366936;-0.371729;,
  0.707292;0.593054;-0.384740;,
  0.803553;0.488225;0.340498;,
  0.830738;-0.218191;0.512120;,
  -0.285779;-0.900570;-0.327573;,
  0.285778;-0.900569;-0.327576;,
  0.285777;-0.900566;0.327587;,
  -0.285778;-0.900567;0.327583;,
  -0.274324;0.572623;-0.772560;,
  -0.260489;0.666901;-0.698132;,
  0.266488;0.656000;-0.706150;,
  0.285357;0.548320;-0.786077;,
  0.320892;0.418352;0.849711;,
  -0.320892;0.418352;0.849712;,
  -0.320892;-0.418357;0.849709;,
  0.320891;-0.418354;0.849711;,
  -0.568681;-0.822558;0.000000;,
  -0.543874;-0.786677;-0.292131;,
  -0.243104;-0.750391;-0.614666;,
  0.543884;-0.786669;-0.292135;,
  0.568692;-0.822551;-0.000000;,
  0.243103;-0.750387;-0.614671;;
  26;
  4;0,1,2,3;,
  4;16,1,0,17;,
  4;15,24,25,12;,
  4;21,3,2,22;,
  4;5,0,3,6;,
  3;5,17,0;,
  3;26,12,25;,
  3;15,22,2;,
  3;21,6,3;,
  4;4,5,6,7;,
  4;17,5,4,18;,
  4;20,7,6,21;,
  4;9,4,7,10;,
  3;9,18,4;,
  3;20,10,7;,
  4;8,9,10,11;,
  4;18,9,8,19;,
  4;23,11,10,20;,
  4;13,27,28,14;,
  3;13,29,27;,
  3;23,14,11;,
  4;12,13,14,15;,
  4;29,13,12,26;,
  4;22,15,14,23;,
  4;16,17,18,19;,
  4;20,21,22,23;;
 }
 MeshTextureCoords {
  24;
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
