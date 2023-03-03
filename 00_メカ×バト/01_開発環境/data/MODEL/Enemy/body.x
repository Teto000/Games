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
 130.22373;37.04985;-9.23925;,
 121.83114;112.85174;-12.63008;,
 54.56791;112.85174;55.81735;,
 58.10475;37.04985;64.14956;,
 -44.78485;37.04985;65.04755;,
 -41.39404;112.85174;56.65485;,
 -109.84148;112.85174;-10.60828;,
 -118.17361;37.04985;-7.07148;,
 -110.67904;112.85174;-106.57018;,
 -119.07163;37.04985;-109.96109;,
 -43.41577;112.85174;-175.01789;,
 -46.95259;37.04985;-183.34986;,
 52.54613;112.85174;-175.85520;,
 55.93697;37.04985;-184.24781;,
 120.99363;112.85174;-108.59202;,
 129.32578;37.04985;-112.12892;,
 5.57605;305.92359;-59.60011;,
 5.57605;37.04985;-59.60011;,
 28.93734;64.79525;98.27193;,
 14.59537;14.77411;183.51903;,
 -13.41376;64.79525;99.10952;,
 1.01382;14.77411;184.41690;,
 -29.19948;168.87671;-141.52626;,
 38.81231;169.30506;-141.86277;,
 -13.82377;229.47080;-105.30336;,
 24.11468;229.71997;-105.48488;,
 17.30530;208.67935;-92.13993;,
 -6.91246;208.52046;-92.02409;,
 26.68742;169.52879;-115.36145;,
 -16.72743;169.25528;-115.14672;,
 -36.62164;36.80216;-91.09171;,
 -36.62162;36.80216;-28.10857;,
 -36.62162;0.04911;-28.10857;,
 -36.62164;0.04911;-91.09171;,
 -80.60276;36.80216;-28.10856;,
 -80.60276;0.04911;-28.10856;,
 -80.60276;36.80216;-91.09168;,
 -80.60276;0.04911;-91.09168;,
 92.25056;36.80216;-91.09172;,
 92.25056;36.80216;-28.10859;,
 92.25056;0.04911;-28.10859;,
 92.25056;0.04911;-91.09172;,
 48.26943;36.80216;-28.10858;,
 48.26943;0.04911;-28.10858;,
 48.26942;36.80216;-91.09171;,
 48.26942;0.04911;-91.09171;;
 
 46;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,1,0;,
 3;1,16,2;,
 3;2,16,5;,
 3;5,16,6;,
 3;6,16,8;,
 3;8,16,10;,
 3;12,16,14;,
 3;14,16,1;,
 3;17,0,3;,
 3;17,3,4;,
 3;17,4,7;,
 3;17,7,9;,
 3;17,9,11;,
 3;17,11,13;,
 3;17,13,15;,
 3;17,15,0;,
 4;18,19,3,2;,
 4;20,18,2,5;,
 4;21,20,5,4;,
 4;19,21,4,3;,
 4;19,18,20,21;,
 4;22,23,12,10;,
 3;24,16,25;,
 4;26,27,24,25;,
 4;28,26,25,23;,
 4;29,28,23,22;,
 4;27,29,22,24;,
 4;27,26,28,29;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,30,33,37;,
 4;36,34,31,30;,
 4;33,32,35,37;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;42,44,45,43;,
 4;44,38,41,45;,
 4;44,42,39,38;,
 4;41,40,43,45;;
 
 MeshMaterialList {
  6;
  46;
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
  0,
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
  1;;
  Material {
   0.800000;0.759200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.734118;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.514400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.232000;0.000000;1.000000;;
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
   0.800000;0.772000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  46;
  0.920643;0.118571;0.371964;,
  0.776029;0.186501;0.602492;,
  -0.759740;0.194295;0.620520;,
  -0.914011;0.118570;0.387975;,
  -0.920643;0.118570;-0.371963;,
  -0.387975;0.118570;-0.914011;,
  0.371964;0.118570;-0.920643;,
  0.914011;0.118571;-0.387975;,
  0.871012;0.342778;0.351912;,
  0.478454;0.454685;0.751228;,
  -0.460491;0.457590;0.760631;,
  -0.864737;0.342778;0.367060;,
  -0.871012;0.342778;-0.351911;,
  -0.367059;0.342778;-0.864738;,
  0.351912;0.342778;-0.871012;,
  0.864737;0.342778;-0.367060;,
  0.006996;0.597724;0.801672;,
  0.000000;-1.000000;-0.000000;,
  0.828150;0.259749;0.496688;,
  -0.808393;0.275248;0.520325;,
  0.325449;0.674701;0.662466;,
  -0.293524;0.680523;0.671366;,
  -0.007925;0.867366;-0.497607;,
  -0.007482;0.514488;-0.857465;,
  -0.007927;0.865716;-0.500473;,
  -0.908661;0.029502;-0.416492;,
  -0.000525;-0.535482;-0.844546;,
  -0.571814;0.597725;-0.561920;,
  0.771995;0.544648;-0.327693;,
  -0.002249;-0.998151;-0.060735;,
  -0.006721;-0.983363;-0.181529;,
  0.021591;0.863214;0.504377;,
  0.903410;0.026395;-0.427964;,
  -0.007460;0.508807;-0.860849;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000001;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  46;
  4;0,8,9,1;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,0;,
  3;8,16,9;,
  3;9,16,10;,
  3;10,16,11;,
  3;11,27,12;,
  3;12,27,13;,
  3;14,28,15;,
  3;15,28,8;,
  3;17,17,29;,
  3;17,29,29;,
  3;17,29,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  4;20,18,1,9;,
  4;21,20,9,10;,
  4;19,21,10,2;,
  4;30,30,29,29;,
  4;31,20,21,31;,
  4;22,22,14,13;,
  3;23,27,23;,
  4;26,26,26,26;,
  4;25,25,25,25;,
  4;24,24,22,22;,
  4;32,32,32,32;,
  4;33,33,24,24;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;;
 }
}
