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
 -1.58053;-1.49259;-5.72533;,
 -2.00912;-2.58516;-6.38295;,
 -2.00912;-2.58516;0.45043;,
 -2.00912;-0.40622;0.45043;,
 -1.49245;-2.58516;-6.81904;,
 -1.06385;-1.49259;-6.16141;,
 -1.49245;-2.94237;0.45043;,
 -1.49245;-2.94237;-6.38295;,
 -1.49245;-0.40622;0.88650;,
 -1.49245;-2.58516;0.88650;,
 -1.06385;-1.13537;-5.72533;,
 -1.49245;-0.04900;0.45043;,
 1.42082;-1.13537;-5.72533;,
 1.70866;-0.04900;0.45043;,
 1.42082;-1.49259;-6.16141;,
 1.70866;-0.40622;0.88650;,
 1.93750;-1.49259;-5.72533;,
 2.22534;-0.40622;0.45043;,
 2.22534;-2.58517;-6.38295;,
 2.22534;-2.58517;0.45043;,
 1.70866;-2.58517;-6.81904;,
 1.70866;-2.58517;0.88650;,
 1.70866;-2.94239;-6.38295;,
 1.70866;-2.94239;0.45043;;
 
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
  13;
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
  30;
  -0.690995;0.614642;-0.380449;,
  -0.830751;0.422499;-0.362417;,
  -0.835523;-0.197566;0.512708;,
  -0.797709;0.503334;0.332139;,
  0.275941;0.869233;-0.410232;,
  -0.275374;0.868012;-0.413188;,
  -0.293652;0.925620;0.238739;,
  0.293586;0.924815;0.241918;,
  0.852746;0.366936;-0.371729;,
  0.707292;0.593054;-0.384740;,
  0.803553;0.488225;0.340498;,
  0.830738;-0.218191;0.512120;,
  -0.285783;-0.900569;-0.327572;,
  0.285778;-0.900569;-0.327576;,
  0.285778;-0.900566;0.327586;,
  -0.285782;-0.900566;0.327583;,
  -0.274326;0.572623;-0.772560;,
  -0.260490;0.666901;-0.698132;,
  0.266488;0.656000;-0.706150;,
  0.285357;0.548320;-0.786076;,
  0.320892;0.418352;0.849711;,
  -0.320897;0.418352;0.849710;,
  -0.320896;-0.418357;0.849708;,
  0.320891;-0.418354;0.849711;,
  -0.568689;-0.822553;0.000000;,
  -0.543882;-0.786672;-0.292129;,
  -0.243108;-0.750391;-0.614665;,
  0.543884;-0.786669;-0.292134;,
  0.568692;-0.822551;-0.000000;,
  0.243104;-0.750387;-0.614670;;
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
