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
 1.26417;-0.76496;-0.55978;,
 -0.06119;-0.76496;-0.55978;,
 -0.06119;0.58254;-0.55978;,
 1.26417;0.58254;-0.55978;,
 -0.06119;-1.06496;-0.25978;,
 1.26417;-1.06496;-0.25978;,
 -0.06699;0.58254;-0.25978;,
 -0.06699;-0.76496;-0.25978;,
 1.26417;0.88254;-0.25978;,
 -0.06119;0.88254;-0.25978;,
 1.56417;-0.76496;-0.25978;,
 1.56417;0.58254;-0.25978;,
 -0.06699;-0.76496;0.25978;,
 -0.06699;0.58254;0.25978;,
 -0.06119;-1.06496;0.25978;,
 -0.06119;0.58254;0.55978;,
 -0.06119;-0.76496;0.55978;,
 -0.06119;0.88254;0.25978;,
 1.26417;-0.76496;0.55978;,
 1.26417;0.58254;0.55978;,
 1.26417;-1.06496;0.25978;,
 1.56417;0.58254;0.25978;,
 1.56417;-0.76496;0.25978;,
 1.26417;0.88254;0.25978;;
 
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
 4;8,9,17,23;;
 
 MeshMaterialList {
  12;
  26;
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
  2;;
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
  32;
  0.367001;-0.367001;-0.854763;,
  0.000000;-0.382683;-0.923880;,
  0.000000;0.382683;-0.923880;,
  0.367001;0.367001;-0.854763;,
  -0.999907;-0.009665;-0.009665;,
  -0.999907;-0.009665;0.009665;,
  -0.999907;0.009665;0.009665;,
  -0.999907;0.009665;-0.009665;,
  -0.999767;-0.009663;0.019328;,
  0.367001;-0.367001;0.854763;,
  0.367001;0.367001;0.854763;,
  -0.999767;0.009663;0.019328;,
  0.854763;-0.367001;0.367001;,
  0.854763;-0.367001;-0.367001;,
  0.854763;0.367001;-0.367001;,
  0.854763;0.367001;0.367001;,
  0.367001;-0.854763;0.367001;,
  -0.999767;-0.019328;0.009663;,
  0.000000;-0.923880;-0.382683;,
  0.367001;-0.854763;-0.367001;,
  0.367001;0.854763;-0.367001;,
  0.000000;0.923880;-0.382683;,
  -0.999767;0.019328;0.009663;,
  0.367001;0.854763;0.367001;,
  -0.999767;0.009663;-0.019328;,
  -0.999767;-0.009663;-0.019328;,
  -0.999767;-0.019328;-0.009663;,
  -0.999767;0.019328;-0.009663;,
  0.000000;-0.382683;0.923880;,
  0.000000;0.382683;0.923880;,
  0.000000;-0.923880;0.382683;,
  0.000000;0.923880;0.382683;;
  26;
  4;0,1,2,3;,
  4;18,1,0,19;,
  4;7,24,25,4;,
  4;20,3,2,21;,
  4;13,0,3,14;,
  3;13,19,0;,
  3;26,4,25;,
  3;7,27,24;,
  3;20,14,3;,
  4;4,5,6,7;,
  4;17,5,4,26;,
  4;11,6,5,8;,
  4;27,7,6,22;,
  3;17,8,5;,
  3;11,22,6;,
  4;28,9,10,29;,
  4;16,9,28,30;,
  4;15,10,9,12;,
  4;31,29,10,23;,
  3;16,12,9;,
  3;15,23,10;,
  4;12,13,14,15;,
  4;19,13,12,16;,
  4;23,15,14,20;,
  4;16,30,18,19;,
  4;20,21,31,23;;
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
