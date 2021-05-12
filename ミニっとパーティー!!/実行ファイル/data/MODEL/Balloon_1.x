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
 270;
 2.05855;92.60444;0.00000;,
 7.33785;90.93052;-5.20090;,
 2.05855;90.93052;-7.35519;,
 2.05855;92.60444;0.00000;,
 9.52460;90.93052;0.00000;,
 2.05855;92.60444;0.00000;,
 7.33785;90.93052;5.20090;,
 2.05855;92.60444;0.00000;,
 2.05855;90.93052;7.35519;,
 2.05855;92.60444;0.00000;,
 -3.22075;90.93052;5.20090;,
 2.05855;92.60444;0.00000;,
 -5.40752;90.93052;0.00000;,
 2.05855;92.60444;0.00000;,
 -3.22075;90.93052;-5.20090;,
 2.05855;92.60444;0.00000;,
 2.05855;90.93052;-7.35519;,
 11.81342;86.16348;-9.61001;,
 2.05855;86.16348;-13.59061;,
 15.85401;86.16348;0.00000;,
 11.81342;86.16348;9.61001;,
 2.05855;86.16348;13.59061;,
 -7.69635;86.16348;9.61001;,
 -11.73697;86.16348;0.00000;,
 -7.69635;86.16348;-9.61001;,
 2.05855;86.16348;-13.59061;,
 14.80390;79.02924;-12.55610;,
 2.05855;79.02924;-17.75699;,
 20.08320;79.02924;0.00000;,
 14.80390;79.02924;12.55610;,
 2.05855;79.02924;17.75699;,
 -10.68685;79.02924;12.55608;,
 -15.96617;79.02924;0.00000;,
 -10.68685;79.02924;-12.55609;,
 2.05855;79.02924;-17.75699;,
 15.85401;70.61381;-13.59061;,
 2.05855;70.61381;-19.22001;,
 21.56829;70.61381;0.00000;,
 15.85401;70.61381;13.59061;,
 2.05855;70.61381;19.22001;,
 -11.73697;70.61381;13.59061;,
 -17.45125;70.61381;0.00000;,
 -11.73697;70.61381;-13.59061;,
 2.05855;70.61381;-19.22001;,
 14.80390;62.19838;-12.55610;,
 2.05855;62.19838;-17.75699;,
 20.08320;62.19838;0.00000;,
 14.80390;62.19838;12.55610;,
 2.05855;62.19838;17.75699;,
 -10.68685;62.19838;12.55608;,
 -15.96617;62.19838;0.00000;,
 -10.68685;62.19838;-12.55609;,
 2.05855;62.19838;-17.75699;,
 11.81342;55.06415;-9.61001;,
 2.05855;55.06415;-13.59061;,
 15.85401;55.06415;0.00000;,
 11.81342;55.06415;9.61001;,
 2.05855;55.06415;13.59061;,
 -7.69635;55.06415;9.61001;,
 -11.73697;55.06415;0.00000;,
 -7.69635;55.06415;-9.61001;,
 2.05855;55.06415;-13.59061;,
 7.33785;50.29714;-5.20090;,
 2.05855;50.29714;-7.35519;,
 9.52460;50.29714;0.00000;,
 7.33785;50.29714;5.20090;,
 2.05855;50.29714;7.35519;,
 -3.22075;50.29714;5.20090;,
 -5.40752;50.29714;0.00000;,
 -3.22075;50.29714;-5.20090;,
 2.05855;50.29714;-7.35519;,
 2.05855;48.62327;0.00000;,
 2.05855;48.62327;0.00000;,
 2.05855;48.62327;0.00000;,
 2.05855;48.62327;0.00000;,
 2.05855;48.62327;0.00000;,
 2.05855;48.62327;0.00000;,
 2.05855;48.62327;0.00000;,
 2.05855;48.62327;0.00000;,
 3.18148;46.98198;-1.25943;,
 2.05855;46.39046;0.00000;,
 2.05855;46.98197;-1.78110;,
 3.64662;46.98199;0.00000;,
 3.18148;46.98198;1.25943;,
 2.05855;46.98197;1.78110;,
 0.93563;46.98195;1.25941;,
 0.47048;46.98199;0.00000;,
 0.93563;46.98195;-1.25941;,
 4.81775;50.16627;-3.09458;,
 2.05855;50.16626;-4.37639;,
 5.96063;50.16627;0.00000;,
 4.81775;50.16627;3.09458;,
 2.05855;50.16627;4.37639;,
 -0.70065;50.16628;3.09459;,
 -1.84354;50.16628;0.00000;,
 -0.70065;50.16628;-3.09458;,
 4.13947;47.02766;0.00000;,
 4.21565;47.46792;0.00000;,
 3.58385;47.46792;-1.52530;,
 3.52998;47.02766;-1.47143;,
 4.39958;47.65028;0.00000;,
 3.71390;47.65028;-1.65535;,
 4.58351;47.46792;0.00000;,
 3.84396;47.46792;-1.78541;,
 4.65969;47.02766;0.00000;,
 3.89784;47.02766;-1.83928;,
 4.58351;46.58741;0.00000;,
 3.84396;46.58741;-1.78541;,
 4.39958;46.40504;0.00000;,
 3.71390;46.40504;-1.65535;,
 4.21565;46.58741;0.00000;,
 3.58385;46.58741;-1.52530;,
 4.13947;47.02766;0.00000;,
 3.52998;47.02766;-1.47143;,
 2.05855;47.46792;-2.15710;,
 2.05855;47.02766;-2.08091;,
 2.05855;47.65028;-2.34102;,
 2.05855;47.46792;-2.52495;,
 2.05855;47.02766;-2.60114;,
 2.05855;46.58741;-2.52495;,
 2.05855;46.40504;-2.34102;,
 2.05855;46.58741;-2.15710;,
 2.05855;47.02766;-2.08091;,
 0.53325;47.46792;-1.52530;,
 0.58712;47.02766;-1.47143;,
 0.40320;47.65028;-1.65535;,
 0.27314;47.46792;-1.78541;,
 0.21927;47.02766;-1.83928;,
 0.27314;46.58741;-1.78541;,
 0.40320;46.40504;-1.65535;,
 0.53325;46.58741;-1.52530;,
 0.58712;47.02766;-1.47143;,
 -0.09855;47.46792;0.00000;,
 -0.02236;47.02766;0.00000;,
 -0.28247;47.65028;0.00000;,
 -0.46640;47.46792;0.00000;,
 -0.54259;47.02766;0.00000;,
 -0.46640;46.58741;0.00000;,
 -0.28247;46.40504;0.00000;,
 -0.09855;46.58741;0.00000;,
 -0.02236;47.02766;0.00000;,
 0.53325;47.46792;1.52530;,
 0.58712;47.02766;1.47143;,
 0.40320;47.65028;1.65535;,
 0.27314;47.46792;1.78541;,
 0.21927;47.02766;1.83928;,
 0.27314;46.58741;1.78541;,
 0.40320;46.40504;1.65535;,
 0.53325;46.58741;1.52530;,
 0.58712;47.02766;1.47143;,
 2.05855;47.46792;2.15710;,
 2.05855;47.02766;2.08091;,
 2.05855;47.65028;2.34102;,
 2.05855;47.46792;2.52495;,
 2.05855;47.02766;2.60114;,
 2.05855;46.58741;2.52495;,
 2.05855;46.40504;2.34102;,
 2.05855;46.58741;2.15710;,
 2.05855;47.02766;2.08091;,
 3.58385;47.46792;1.52530;,
 3.52998;47.02766;1.47143;,
 3.71390;47.65028;1.65535;,
 3.84396;47.46792;1.78541;,
 3.89784;47.02766;1.83928;,
 3.84396;46.58741;1.78541;,
 3.71390;46.40504;1.65535;,
 3.58385;46.58741;1.52530;,
 3.52998;47.02766;1.47143;,
 4.21565;47.46792;0.00000;,
 4.13947;47.02766;0.00000;,
 4.39958;47.65028;0.00000;,
 4.58351;47.46792;0.00000;,
 4.65969;47.02766;0.00000;,
 4.58351;46.58741;0.00000;,
 4.39958;46.40504;0.00000;,
 4.21565;46.58741;0.00000;,
 4.13947;47.02766;0.00000;,
 2.05855;44.13670;-3.95469;,
 2.05855;48.61599;0.00000;,
 4.85494;44.13670;-2.79639;,
 2.05855;48.61599;0.00000;,
 6.01325;44.13670;0.00000;,
 2.05855;48.61599;0.00000;,
 4.85494;44.13670;2.79639;,
 2.05855;48.61599;0.00000;,
 2.05855;44.13670;3.95469;,
 2.05855;48.61599;0.00000;,
 -0.73784;44.13670;2.79639;,
 2.05855;48.61599;0.00000;,
 -1.89614;44.13670;0.00000;,
 2.05855;48.61599;0.00000;,
 -0.73784;44.13670;-2.79639;,
 2.05855;48.61599;0.00000;,
 2.05855;44.13670;-3.95469;,
 0.01549;47.37174;-0.69714;,
 0.50844;47.37174;-0.49296;,
 0.50844;0.44509;-0.49296;,
 0.01549;0.44509;-0.69714;,
 0.71263;47.37174;0.00000;,
 0.71263;0.44509;0.00000;,
 0.50844;47.37174;0.49296;,
 0.50844;0.44509;0.49296;,
 0.01549;47.37174;0.69714;,
 0.01549;0.44509;0.69714;,
 -0.47747;47.37174;0.49296;,
 -0.47747;0.44509;0.49296;,
 -0.68166;47.37174;0.00000;,
 -0.68166;0.44509;0.00000;,
 -0.47747;47.37174;-0.49296;,
 -0.47747;0.44509;-0.49296;,
 0.01549;47.37174;-0.69714;,
 0.01549;0.44509;-0.69714;,
 0.01549;47.37174;0.00000;,
 0.01549;47.37174;0.00000;,
 0.01549;47.37174;0.00000;,
 0.01549;47.37174;0.00000;,
 0.01549;47.37174;0.00000;,
 0.01549;47.37174;0.00000;,
 0.01549;47.37174;0.00000;,
 0.01549;47.37174;0.00000;,
 0.01549;0.44509;0.00000;,
 0.01549;0.44509;0.00000;,
 0.01549;0.44509;0.00000;,
 0.01549;0.44509;0.00000;,
 0.01549;0.44509;0.00000;,
 0.01549;0.44509;0.00000;,
 0.01549;0.44509;0.00000;,
 0.01549;0.44509;0.00000;,
 0.00000;0.01529;0.00000;,
 0.00000;0.01529;-4.97452;,
 3.51752;0.01529;-3.51752;,
 4.97452;0.01529;0.00000;,
 3.51752;0.01529;3.51752;,
 0.00000;0.01529;4.97452;,
 -3.51752;0.01529;3.51752;,
 -4.97452;0.01529;0.00000;,
 -3.51752;0.01529;-3.51752;,
 0.00000;5.00163;-2.48135;,
 0.00000;5.00026;0.00000;,
 1.75458;5.00163;-1.75458;,
 3.51752;0.01529;-3.51752;,
 0.00000;0.01529;-4.97452;,
 1.75458;5.00163;-1.75458;,
 0.00000;5.00026;0.00000;,
 2.48135;5.00163;0.00000;,
 4.97452;0.01529;0.00000;,
 2.48135;5.00163;0.00000;,
 0.00000;5.00026;0.00000;,
 1.75458;5.00163;1.75458;,
 3.51752;0.01529;3.51752;,
 1.75458;5.00163;1.75458;,
 0.00000;5.00026;0.00000;,
 0.00000;5.00163;2.48135;,
 0.00000;0.01529;4.97452;,
 0.00000;5.00163;2.48135;,
 0.00000;5.00026;0.00000;,
 -1.75458;5.00163;1.75458;,
 -3.51752;0.01529;3.51752;,
 -1.75458;5.00163;1.75458;,
 0.00000;5.00026;0.00000;,
 -2.48135;5.00163;0.00000;,
 -4.97452;0.01529;0.00000;,
 -2.48135;5.00163;0.00000;,
 0.00000;5.00026;0.00000;,
 -1.75458;5.00163;-1.75458;,
 -3.51752;0.01529;-3.51752;,
 -1.75458;5.00163;-1.75458;,
 0.00000;5.00026;0.00000;,
 0.00000;5.00163;-2.48135;,
 0.00000;0.01529;-4.97452;;
 
 200;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;79,80,81;,
 3;82,80,79;,
 3;83,80,82;,
 3;84,80,83;,
 3;85,80,84;,
 3;86,80,85;,
 3;87,80,86;,
 3;81,80,87;,
 4;88,79,81,89;,
 4;90,82,79,88;,
 4;91,83,82,90;,
 4;92,84,83,91;,
 4;93,85,84,92;,
 4;94,86,85,93;,
 4;95,87,86,94;,
 4;89,81,87,95;,
 4;96,97,98,99;,
 4;97,100,101,98;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;99,98,114,115;,
 4;98,101,116,114;,
 4;101,103,117,116;,
 4;103,105,118,117;,
 4;105,107,119,118;,
 4;107,109,120,119;,
 4;109,111,121,120;,
 4;111,113,122,121;,
 4;115,114,123,124;,
 4;114,116,125,123;,
 4;116,117,126,125;,
 4;117,118,127,126;,
 4;118,119,128,127;,
 4;119,120,129,128;,
 4;120,121,130,129;,
 4;121,122,131,130;,
 4;124,123,132,133;,
 4;123,125,134,132;,
 4;125,126,135,134;,
 4;126,127,136,135;,
 4;127,128,137,136;,
 4;128,129,138,137;,
 4;129,130,139,138;,
 4;130,131,140,139;,
 4;133,132,141,142;,
 4;132,134,143,141;,
 4;134,135,144,143;,
 4;135,136,145,144;,
 4;136,137,146,145;,
 4;137,138,147,146;,
 4;138,139,148,147;,
 4;139,140,149,148;,
 4;142,141,150,151;,
 4;141,143,152,150;,
 4;143,144,153,152;,
 4;144,145,154,153;,
 4;145,146,155,154;,
 4;146,147,156,155;,
 4;147,148,157,156;,
 4;148,149,158,157;,
 4;151,150,159,160;,
 4;150,152,161,159;,
 4;152,153,162,161;,
 4;153,154,163,162;,
 4;154,155,164,163;,
 4;155,156,165,164;,
 4;156,157,166,165;,
 4;157,158,167,166;,
 4;160,159,168,169;,
 4;159,161,170,168;,
 4;161,162,171,170;,
 4;162,163,172,171;,
 4;163,164,173,172;,
 4;164,165,174,173;,
 4;165,166,175,174;,
 4;166,167,176,175;,
 3;177,178,179;,
 3;179,180,181;,
 3;181,182,183;,
 3;183,184,185;,
 3;185,186,187;,
 3;187,188,189;,
 3;189,190,191;,
 3;191,192,193;,
 4;194,195,196,197;,
 4;195,198,199,196;,
 4;198,200,201,199;,
 4;200,202,203,201;,
 4;202,204,205,203;,
 4;204,206,207,205;,
 4;206,208,209,207;,
 4;208,210,211,209;,
 3;212,195,194;,
 3;213,198,195;,
 3;214,200,198;,
 3;215,202,200;,
 3;216,204,202;,
 3;217,206,204;,
 3;218,208,206;,
 3;219,210,208;,
 3;220,197,196;,
 3;221,196,199;,
 3;222,199,201;,
 3;223,201,203;,
 3;224,203,205;,
 3;225,205,207;,
 3;226,207,209;,
 3;227,209,211;,
 3;228,229,230;,
 3;228,230,231;,
 3;228,231,232;,
 3;228,232,233;,
 3;228,233,234;,
 3;228,234,235;,
 3;228,235,236;,
 3;228,236,229;,
 3;237,238,239;,
 4;237,239,240,241;,
 3;242,243,244;,
 4;242,244,245,240;,
 3;246,247,248;,
 4;246,248,249,245;,
 3;250,251,252;,
 4;250,252,253,249;,
 3;254,255,256;,
 4;254,256,257,253;,
 3;258,259,260;,
 4;258,260,261,257;,
 3;262,263,264;,
 4;262,264,265,261;,
 3;266,267,268;,
 4;266,268,269,265;;
 
 MeshMaterialList {
  4;
  200;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\balloon_01-blue-nonline.png";
   }
  }
  Material {
   0.800000;0.050400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.499200;0.003200;1.000000;;
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
  193;
  0.000000;1.000000;0.000000;,
  0.000000;0.906682;-0.421815;,
  0.294551;0.907791;-0.298587;,
  0.417005;0.908904;0.000000;,
  0.294551;0.907791;0.298587;,
  0.000000;0.906682;0.421815;,
  -0.294550;0.907792;0.298587;,
  -0.417003;0.908905;0.000000;,
  -0.294550;0.907792;-0.298587;,
  0.000000;0.663999;-0.747734;,
  0.523839;0.666615;-0.530299;,
  0.743035;0.669253;0.000000;,
  0.523839;0.666615;0.530299;,
  0.000000;0.663999;0.747734;,
  -0.523838;0.666616;0.530300;,
  -0.743033;0.669255;0.000000;,
  -0.523838;0.666616;-0.530300;,
  0.000000;0.344613;-0.938745;,
  0.659532;0.346790;-0.666899;,
  0.937124;0.348996;0.000000;,
  0.659532;0.346790;0.666899;,
  0.000000;0.344613;0.938745;,
  -0.659531;0.346790;0.666900;,
  -0.937124;0.348997;0.000000;,
  -0.659531;0.346790;-0.666900;,
  0.000001;-0.000000;-1.000000;,
  0.703317;0.000000;-0.710877;,
  1.000000;0.000000;0.000000;,
  0.703317;0.000000;0.710877;,
  0.000000;0.000000;1.000000;,
  -0.703316;0.000000;0.710877;,
  -1.000000;0.000000;0.000000;,
  -0.703316;0.000000;-0.710877;,
  0.000000;-0.344613;-0.938745;,
  0.659531;-0.346790;-0.666899;,
  0.937124;-0.348996;-0.000000;,
  0.659532;-0.346790;0.666899;,
  0.000000;-0.344613;0.938745;,
  -0.659531;-0.346791;0.666900;,
  -0.937124;-0.348997;0.000000;,
  -0.659531;-0.346791;-0.666900;,
  0.000000;-0.664000;-0.747732;,
  0.523838;-0.666616;-0.530298;,
  0.743034;-0.669254;-0.000000;,
  0.523838;-0.666616;0.530298;,
  0.000000;-0.664000;0.747732;,
  -0.523837;-0.666617;0.530299;,
  -0.743032;-0.669256;0.000000;,
  -0.523837;-0.666617;-0.530299;,
  0.000000;-0.906684;-0.421811;,
  0.294548;-0.907793;-0.298584;,
  0.417000;-0.908906;-0.000000;,
  0.294548;-0.907793;0.298584;,
  0.000000;-0.906684;0.421811;,
  -0.294547;-0.907794;0.298584;,
  -0.416999;-0.908907;0.000000;,
  -0.294547;-0.907794;-0.298584;,
  0.000000;-1.000000;-0.000000;,
  0.000005;-1.000000;0.000000;,
  0.000005;-0.827321;-0.561730;,
  0.431250;-0.813096;-0.391022;,
  0.600611;-0.799541;-0.000000;,
  0.431249;-0.813096;0.391022;,
  0.000005;-0.827321;0.561730;,
  -0.431246;-0.813100;0.391019;,
  -0.600612;-0.799541;-0.000000;,
  -0.431247;-0.813099;-0.391018;,
  -0.000001;-0.631773;-0.775153;,
  0.586076;-0.609101;-0.534332;,
  0.808956;-0.587869;-0.000000;,
  0.586076;-0.609101;0.534332;,
  -0.000000;-0.631773;0.775153;,
  -0.586077;-0.609100;0.534332;,
  -0.808958;-0.587867;-0.000000;,
  -0.586077;-0.609100;-0.534332;,
  -1.000000;-0.000002;0.000000;,
  -0.884073;0.467349;0.000000;,
  -0.704082;0.710119;0.000000;,
  0.884066;0.467362;0.000000;,
  1.000000;-0.000002;-0.000000;,
  0.884071;-0.467352;-0.000000;,
  0.704086;-0.710115;-0.000000;,
  -0.884079;-0.467338;0.000000;,
  -0.707106;-0.000002;0.707108;,
  -0.625133;0.467347;0.625136;,
  -0.497863;0.710113;0.497867;,
  0.625128;0.467363;-0.625130;,
  0.707107;-0.000002;-0.707107;,
  0.625132;-0.467352;-0.625133;,
  0.497863;-0.710114;-0.497866;,
  -0.625137;-0.467337;0.625140;,
  -0.000000;-0.000002;1.000000;,
  -0.000000;0.467346;0.884074;,
  -0.000000;0.710109;0.704092;,
  -0.000000;0.467363;-0.884066;,
  -0.000001;-0.000002;-1.000000;,
  -0.000000;-0.467353;-0.884071;,
  -0.000000;-0.710114;-0.704086;,
  -0.000000;-0.467336;0.884080;,
  0.707107;-0.000002;0.707107;,
  0.625135;0.467347;0.625135;,
  0.497868;0.710109;0.497868;,
  -0.625129;0.467362;-0.625129;,
  -0.707107;-0.000002;-0.707107;,
  -0.625133;-0.467352;-0.625133;,
  -0.497864;-0.710114;-0.497864;,
  0.625139;-0.467337;0.625139;,
  1.000000;-0.000002;-0.000000;,
  0.884074;0.467346;0.000000;,
  0.704092;0.710109;0.000000;,
  -0.884066;0.467362;-0.000000;,
  -1.000000;-0.000002;0.000000;,
  -0.884071;-0.467352;-0.000000;,
  -0.704086;-0.710114;0.000000;,
  0.884080;-0.467336;-0.000000;,
  0.707107;-0.000002;-0.707107;,
  0.625135;0.467347;-0.625135;,
  0.497868;0.710109;-0.497868;,
  -0.625129;0.467362;0.625129;,
  -0.707107;-0.000002;0.707107;,
  -0.625133;-0.467352;0.625133;,
  -0.497864;-0.710114;0.497864;,
  0.625139;-0.467337;-0.625139;,
  -0.000000;-0.000002;-1.000000;,
  -0.000000;0.467346;-0.884074;,
  -0.000000;0.710109;-0.704092;,
  -0.000000;0.467363;0.884066;,
  -0.000001;-0.000002;1.000000;,
  -0.000000;-0.467353;0.884071;,
  -0.000000;-0.710114;0.704086;,
  -0.000000;-0.467336;-0.884080;,
  -0.707106;-0.000002;-0.707108;,
  -0.625133;0.467347;-0.625136;,
  -0.497863;0.710113;-0.497867;,
  0.625128;0.467363;0.625130;,
  0.707107;-0.000002;0.707107;,
  0.625132;-0.467352;0.625133;,
  0.497863;-0.710114;0.497866;,
  -0.625137;-0.467337;-0.625140;,
  0.704068;0.710133;0.000000;,
  0.497851;0.710132;-0.497853;,
  -0.704100;-0.710100;0.000000;,
  -0.497876;-0.710095;0.497880;,
  -0.000000;0.710132;-0.704068;,
  -0.000000;-0.710091;0.704110;,
  -0.497852;0.710132;-0.497852;,
  0.497881;-0.710091;0.497881;,
  -0.704068;0.710132;0.000000;,
  0.704110;-0.710091;-0.000000;,
  -0.497852;0.710132;0.497852;,
  0.497881;-0.710091;-0.497881;,
  -0.000000;0.710132;0.704068;,
  -0.000000;-0.710091;-0.704110;,
  0.497851;0.710132;0.497853;,
  -0.497876;-0.710095;-0.497880;,
  0.000000;0.661845;-0.749641;,
  0.530075;0.661845;-0.530077;,
  0.749640;0.661846;0.000000;,
  0.530075;0.661845;0.530077;,
  0.000000;0.661845;0.749641;,
  -0.530076;0.661845;0.530076;,
  -0.749641;0.661845;0.000000;,
  -0.530076;0.661845;-0.530076;,
  0.648855;0.711865;-0.268765;,
  -0.268765;0.711865;0.648856;,
  0.000000;1.000000;0.000000;,
  0.000004;0.000000;-1.000000;,
  0.707103;0.000000;-0.707110;,
  1.000000;0.000000;0.000000;,
  0.707103;0.000000;0.707110;,
  0.000004;0.000000;1.000000;,
  -0.707101;0.000000;0.707113;,
  -1.000000;0.000000;0.000000;,
  -0.707101;0.000000;-0.707113;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000552;,
  -0.000390;1.000000;0.000390;,
  -0.000552;1.000000;0.000000;,
  -0.000390;1.000000;-0.000390;,
  0.000000;1.000000;-0.000552;,
  0.000390;1.000000;-0.000390;,
  0.000552;1.000000;0.000000;,
  0.000390;1.000000;0.000390;,
  0.000000;0.447214;-0.894427;,
  0.632455;0.447214;-0.632455;,
  0.894427;0.447214;0.000000;,
  0.632455;0.447214;0.632455;,
  0.000000;0.447214;0.894427;,
  -0.632455;0.447214;0.632455;,
  -0.894427;0.447214;0.000000;,
  -0.632455;0.447214;-0.632455;;
  200;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;60,58,59;,
  3;61,58,60;,
  3;62,58,61;,
  3;63,58,62;,
  3;64,58,63;,
  3;65,58,64;,
  3;66,58,65;,
  3;59,58,66;,
  4;68,60,59,67;,
  4;69,61,60,68;,
  4;70,62,61,69;,
  4;71,63,62,70;,
  4;72,64,63,71;,
  4;73,65,64,72;,
  4;74,66,65,73;,
  4;67,59,66,74;,
  4;75,76,84,83;,
  4;76,77,85,84;,
  4;139,78,86,140;,
  4;78,79,87,86;,
  4;79,80,88,87;,
  4;80,81,89,88;,
  4;141,82,90,142;,
  4;82,75,83,90;,
  4;83,84,92,91;,
  4;84,85,93,92;,
  4;140,86,94,143;,
  4;86,87,95,94;,
  4;87,88,96,95;,
  4;88,89,97,96;,
  4;142,90,98,144;,
  4;90,83,91,98;,
  4;91,92,100,99;,
  4;92,93,101,100;,
  4;143,94,102,145;,
  4;94,95,103,102;,
  4;95,96,104,103;,
  4;96,97,105,104;,
  4;144,98,106,146;,
  4;98,91,99,106;,
  4;99,100,108,107;,
  4;100,101,109,108;,
  4;145,102,110,147;,
  4;102,103,111,110;,
  4;103,104,112,111;,
  4;104,105,113,112;,
  4;146,106,114,148;,
  4;106,99,107,114;,
  4;107,108,116,115;,
  4;108,109,117,116;,
  4;147,110,118,149;,
  4;110,111,119,118;,
  4;111,112,120,119;,
  4;112,113,121,120;,
  4;148,114,122,150;,
  4;114,107,115,122;,
  4;115,116,124,123;,
  4;116,117,125,124;,
  4;149,118,126,151;,
  4;118,119,127,126;,
  4;119,120,128,127;,
  4;120,121,129,128;,
  4;150,122,130,152;,
  4;122,115,123,130;,
  4;123,124,132,131;,
  4;124,125,133,132;,
  4;151,126,134,153;,
  4;126,127,135,134;,
  4;127,128,136,135;,
  4;128,129,137,136;,
  4;152,130,138,154;,
  4;130,123,131,138;,
  4;131,132,76,75;,
  4;132,133,77,76;,
  4;153,134,78,139;,
  4;134,135,79,78;,
  4;135,136,80,79;,
  4;136,137,81,80;,
  4;154,138,82,141;,
  4;138,131,75,82;,
  3;155,163,156;,
  3;156,163,157;,
  3;157,163,158;,
  3;158,164,159;,
  3;159,164,160;,
  3;160,164,161;,
  3;161,162,162;,
  3;162,162,155;,
  4;166,167,167,166;,
  4;167,168,168,167;,
  4;168,169,169,168;,
  4;169,170,170,169;,
  4;170,171,171,170;,
  4;171,172,172,171;,
  4;172,173,173,172;,
  4;173,166,166,173;,
  3;165,165,165;,
  3;165,165,165;,
  3;165,165,165;,
  3;165,165,165;,
  3;165,165,165;,
  3;165,165,165;,
  3;165,165,165;,
  3;165,165,165;,
  3;174,174,174;,
  3;174,174,174;,
  3;174,174,174;,
  3;174,174,174;,
  3;174,174,174;,
  3;174,174,174;,
  3;174,174,174;,
  3;174,174,174;,
  3;175,175,175;,
  3;175,175,175;,
  3;175,175,175;,
  3;175,175,175;,
  3;175,175,175;,
  3;175,175,175;,
  3;175,175,175;,
  3;175,175,175;,
  3;177,176,178;,
  4;185,186,186,185;,
  3;178,176,179;,
  4;186,187,187,186;,
  3;179,176,180;,
  4;187,188,188,187;,
  3;180,176,181;,
  4;188,189,189,188;,
  3;181,176,182;,
  4;189,190,190,189;,
  3;182,176,183;,
  4;190,191,191,190;,
  3;183,176,184;,
  4;191,192,192,191;,
  3;184,176,177;,
  4;192,185,185,192;;
 }
 MeshTextureCoords {
  270;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.000000;0.625000;,
  0.125000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.625000;,
  0.250000;0.750000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.375000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.375000;0.500000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.375000;0.875000;,
  0.375000;1.000000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.500000;0.500000;,
  0.500000;0.625000;,
  0.500000;0.750000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.750000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.750000;0.500000;,
  0.750000;0.625000;,
  0.750000;0.750000;,
  0.750000;0.875000;,
  0.750000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  0.875000;0.500000;,
  0.875000;0.625000;,
  0.875000;0.750000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  1.000000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  1.000000;0.500000;,
  1.000000;0.625000;,
  1.000000;0.750000;,
  1.000000;0.875000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.031320;0.498810;,
  0.062500;0.000000;,
  0.093680;0.498810;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.125000;0.498810;,
  0.125000;0.000000;,
  0.187350;0.498810;,
  0.250000;1.000000;,
  0.218680;0.498810;,
  0.187500;0.000000;,
  0.281030;0.498810;,
  0.375000;1.000000;,
  0.312350;0.498810;,
  0.250000;0.000000;,
  0.374700;0.498810;,
  0.500000;1.000000;,
  0.406030;0.498810;,
  0.312500;0.000000;,
  0.468380;0.498810;,
  0.625000;1.000000;,
  0.499700;0.498810;,
  0.375000;0.000000;,
  0.562050;0.498810;,
  0.750000;1.000000;,
  0.593380;0.498810;,
  0.437500;0.000000;,
  0.655730;0.498810;,
  0.875000;1.000000;,
  0.687050;0.498810;,
  0.500000;0.000000;,
  0.749410;0.498810;,
  1.000000;1.000000;;
 }
}
