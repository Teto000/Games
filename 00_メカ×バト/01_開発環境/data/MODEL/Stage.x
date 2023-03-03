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
 251;
 0.00000;432.26446;-3525.20162;,
 3052.91274;432.26446;-1762.60081;,
 3052.91274;-18.54376;-1762.60081;,
 0.00000;-18.54376;-3525.20162;,
 2442.32914;432.26446;-1410.08039;,
 0.00000;432.26446;-2820.16078;,
 0.00000;-18.54376;-2820.16078;,
 2442.32914;-18.54376;-1410.08039;,
 3052.91274;432.26446;1762.60081;,
 3052.91274;-18.54376;1762.60081;,
 2442.32855;432.26446;1410.08039;,
 2442.32855;-18.54376;1410.08039;,
 -0.00032;432.26446;3525.20162;,
 -0.00032;-18.54376;3525.20162;,
 -0.00024;432.26446;2820.16078;,
 -0.00024;-18.54376;2820.16078;,
 -3052.91274;432.26446;1762.59944;,
 -3052.91274;-18.54376;1762.59944;,
 -2442.32855;432.26446;1410.08039;,
 -2442.32855;-18.54376;1410.08039;,
 -3052.91274;432.26446;-1762.59944;,
 -3052.91274;-18.54376;-1762.59944;,
 -2442.32855;432.26446;-1410.08039;,
 -2442.32855;-18.54376;-1410.08039;,
 3056.87290;518.09932;-1764.88557;,
 0.00000;518.09932;-3529.77115;,
 0.00000;-22.28104;-3529.77115;,
 3056.87290;-22.28104;-1764.88557;,
 3056.87075;518.09932;1764.88557;,
 3056.87075;-22.28104;1764.88557;,
 -0.00032;518.09932;3529.77115;,
 -0.00032;-22.28104;3529.77115;,
 -3056.87075;518.09932;1764.88557;,
 -3056.87075;-22.28104;1764.88557;,
 -3056.87075;518.09932;-1764.88557;,
 -3056.87075;-22.28104;-1764.88557;,
 0.00000;518.09932;-4412.21530;,
 3821.08678;518.09932;-2206.10765;,
 3821.08678;518.09932;2206.10765;,
 3821.08678;-22.28104;-2206.10765;,
 3821.08678;-22.28104;2206.10765;,
 -0.00040;518.09932;4412.21530;,
 -0.00040;-22.28104;4412.21530;,
 -3821.08678;518.09932;2206.10765;,
 -3821.08678;-22.28104;2206.10765;,
 -3821.08678;518.09932;-2206.10765;,
 -3821.08678;-22.28104;-2206.10765;,
 3807.01256;640.02794;-2197.97484;,
 0.00000;640.02794;-4395.94967;,
 0.00000;-21.86424;-4395.94967;,
 3807.01256;-21.86424;-2197.97484;,
 3807.00865;640.02794;2197.97484;,
 3807.00865;-21.86424;2197.97484;,
 -0.00040;640.02794;4395.94967;,
 -0.00040;-21.86424;4395.94967;,
 -3807.00865;640.02794;2197.97484;,
 -3807.00865;-21.86424;2197.97484;,
 -3807.00865;640.02794;-2197.97484;,
 -3807.00865;-21.86424;-2197.97484;,
 0.00000;640.02794;-5494.94110;,
 4758.76296;640.02794;-2747.47055;,
 4758.76296;640.02794;2747.47270;,
 -0.00048;640.02794;5494.94110;,
 -4758.76296;640.02794;2747.47016;,
 -4758.76296;640.02794;-2747.47055;,
 4741.22937;1136.58713;-2737.34535;,
 0.00000;1136.58713;-5474.69071;,
 0.00000;-15.94952;-5474.69071;,
 4741.22937;-15.94952;-2737.34535;,
 4741.22937;1136.58713;2737.34535;,
 4741.22937;-15.94952;2737.34535;,
 -0.00048;1136.58713;5474.69071;,
 -0.00048;-15.94952;5474.69071;,
 -4741.22937;1136.58713;2737.34535;,
 -4741.22937;-15.94952;2737.34535;,
 -4741.22937;1136.58713;-2737.34535;,
 -4741.22937;-15.94952;-2737.34535;,
 0.00000;1136.58713;-6843.36338;,
 5926.51962;1136.58713;-3421.68169;,
 5926.51962;1136.58713;3421.68247;,
 -0.00060;1136.58713;6843.36338;,
 -5926.51962;1136.58713;3421.68169;,
 -5926.51962;1136.58713;-3421.68169;,
 -5733.69657;2503.55433;3060.95122;,
 -5430.68992;2503.55433;3156.48657;,
 -5430.68992;1109.61506;3156.48657;,
 -5733.69657;1109.61506;3060.95122;,
 -5526.22274;2503.55433;3459.48716;,
 -5526.22274;1109.61506;3459.48716;,
 -5829.23212;2503.55433;3363.94536;,
 -5829.23212;1109.61506;3363.94536;,
 -5629.95946;2503.55433;3260.21372;,
 -5629.95946;1109.61506;3260.21372;,
 5435.18992;2503.55433;3124.86430;,
 5749.80712;2503.55433;3080.64575;,
 5749.80712;1109.61506;3080.64575;,
 5435.18992;1109.61506;3124.86430;,
 5794.01806;2503.55433;3395.25747;,
 5794.01806;1109.61506;3395.25747;,
 5479.39383;2503.55433;3439.48247;,
 5479.39383;1109.61506;3439.48247;,
 5614.60790;2503.55433;3260.06450;,
 5614.60790;1109.61506;3260.06450;,
 5525.02782;2503.55433;-3473.30982;,
 5820.61688;2503.55433;-3356.86958;,
 5820.61688;1109.61506;-3356.86958;,
 5525.02782;1109.61506;-3473.30982;,
 5704.18368;2503.55433;-3061.26743;,
 5704.18368;1109.61506;-3061.26743;,
 5408.58719;2503.55433;-3177.71138;,
 5408.58719;1109.61506;-3177.71138;,
 5614.60790;2503.55433;-3267.29243;,
 5614.60790;1109.61506;-3267.29243;,
 15.45304;2503.55433;-6723.35010;,
 213.22940;2503.55433;-6474.70986;,
 213.22940;1109.61506;-6474.70986;,
 15.45304;1109.61506;-6723.35010;,
 -35.41316;2503.55433;-6276.93447;,
 -35.41316;1109.61506;-6276.93447;,
 -233.19231;2503.55433;-6525.57939;,
 -233.19231;1109.61506;-6525.57939;,
 -9.97996;2503.55433;-6500.15049;,
 -9.97996;1109.61506;-6500.15049;,
 15.45304;2503.55433;6279.63212;,
 213.22940;2503.55433;6528.27939;,
 213.22940;1109.61506;6528.27939;,
 15.45304;1109.61506;6279.63212;,
 -35.41316;2503.55433;6726.04619;,
 -35.41316;1109.61506;6726.04619;,
 -233.19231;2503.55433;6477.40752;,
 -233.19231;1109.61506;6477.40752;,
 -9.97996;2503.55433;6502.83643;,
 -9.97996;1109.61506;6502.83643;,
 -5511.28719;2503.55433;-3443.36568;,
 -5423.71883;2503.55433;-3137.97583;,
 -5423.71883;1109.61506;-3137.97583;,
 -5511.28719;1109.61506;-3443.36568;,
 -5729.11610;2503.55433;-3050.39790;,
 -5729.11610;1109.61506;-3050.39790;,
 -5816.69032;2503.55433;-3355.80435;,
 -5816.69032;1109.61506;-3355.80435;,
 -5620.19735;2503.55433;-3246.88657;,
 -5620.19735;1109.61506;-3246.88657;,
 4741.22937;2621.62680;-2737.34535;,
 0.00000;2621.62680;-5474.69071;,
 0.00000;2197.52171;-5474.69071;,
 4741.22937;2197.52171;-2737.34535;,
 4741.22937;2621.62680;2737.34535;,
 4741.22937;2197.52171;2737.34535;,
 -0.00048;2621.62680;5474.69071;,
 -0.00048;2197.52171;5474.69071;,
 -4741.22937;2621.62680;2737.34535;,
 -4741.22937;2197.52171;2737.34535;,
 -4741.22937;2621.62680;-2737.34535;,
 -4741.22937;2197.52171;-2737.34535;,
 -5926.51962;2621.62680;-3421.68169;,
 0.00000;2621.62680;-6843.36338;,
 0.00000;2197.52171;-6843.36338;,
 -5926.51962;2197.52171;-3421.68169;,
 5926.51962;2621.62680;-3421.68169;,
 5926.51962;2197.52171;-3421.68169;,
 5926.51962;2621.62680;3421.68247;,
 5926.51962;2197.52171;3421.68247;,
 -0.00060;2621.62680;6843.36338;,
 -0.00060;2197.52171;6843.36338;,
 -5926.51962;2621.62680;3421.68169;,
 -5926.51962;2197.52171;3421.68169;,
 -2648.96195;812.94738;1413.64426;,
 -2509.09301;812.94738;1457.74280;,
 -2509.09301;428.00196;1457.74280;,
 -2648.96195;428.00196;1413.64426;,
 -2553.19613;812.94738;1597.60676;,
 -2553.19613;428.00196;1597.60676;,
 -2693.05863;812.94738;1553.50608;,
 -2693.05863;428.00196;1553.50608;,
 -2601.07113;812.94738;1505.62307;,
 -2601.07113;428.00196;1505.62307;,
 2506.53539;812.94738;1443.14582;,
 2651.76254;812.94738;1422.73361;,
 2651.76254;428.00196;1422.73361;,
 2506.53539;428.00196;1443.14582;,
 2672.17231;812.94738;1567.95950;,
 2672.17231;428.00196;1567.95950;,
 2526.93949;812.94738;1588.36936;,
 2526.93949;428.00196;1588.36936;,
 2589.35609;812.94738;1505.55325;,
 2589.35609;428.00196;1505.55325;,
 2548.00453;812.94738;-1602.53157;,
 2684.44711;812.94738;-1548.78518;,
 2684.44711;428.00196;-1548.78518;,
 2548.00453;428.00196;-1602.53157;,
 2630.70063;812.94738;-1412.33703;,
 2630.70063;428.00196;-1412.33703;,
 2494.25394;812.94738;-1466.08742;,
 2494.25394;428.00196;-1466.08742;,
 2589.35609;812.94738;-1507.43459;,
 2589.35609;428.00196;-1507.43459;,
 4.81516;812.94738;-3102.73423;,
 96.10752;812.94738;-2987.96079;,
 96.10752;428.00196;-2987.96079;,
 4.81516;428.00196;-3102.73423;,
 -18.66440;812.94738;-2896.66957;,
 -18.66440;428.00196;-2896.66957;,
 -109.95812;812.94738;-3011.44262;,
 -109.95812;428.00196;-3011.44262;,
 -6.92456;812.94738;-2999.70454;,
 -6.92456;428.00196;-2999.70454;,
 4.81516;812.94738;2899.36938;,
 96.10752;812.94738;3014.14399;,
 96.10752;428.00196;3014.14399;,
 4.81516;428.00196;2899.36938;,
 -18.66440;812.94738;3105.43462;,
 -18.66440;428.00196;3105.43462;,
 -109.95812;812.94738;2990.65571;,
 -109.95812;428.00196;2990.65571;,
 -6.92456;812.94738;3002.40219;,
 -6.92456;428.00196;3002.40219;,
 -2546.29750;812.94738;-1588.71282;,
 -2505.87465;812.94738;-1447.74436;,
 -2505.87465;428.00196;-1447.74436;,
 -2546.29750;428.00196;-1588.71282;,
 -2646.84535;812.94738;-1407.31936;,
 -2646.84535;428.00196;-1407.31936;,
 -2687.27016;812.94738;-1548.29270;,
 -2687.27016;428.00196;-1548.29270;,
 -2596.56977;812.94738;-1498.01526;,
 -2596.56977;428.00196;-1498.01526;,
 0.00000;848.50548;-3189.40669;,
 2776.89223;848.50548;-1586.16623;,
 2776.89223;780.50323;-1586.16623;,
 0.00000;780.50323;-3189.40669;,
 2479.14847;852.44952;-1414.26340;,
 0.00000;852.44952;-2845.60239;,
 0.00000;776.55861;-2845.60239;,
 2479.14847;776.55861;-1414.26340;,
 2776.89223;848.50548;1620.31077;,
 2776.89223;780.50323;1620.31077;,
 2479.14847;852.44952;1448.40940;,
 2479.14847;776.55861;1448.40940;,
 -0.00028;848.50548;3223.55298;,
 -0.00028;780.50323;3223.55298;,
 -0.00024;852.44952;2879.74477;,
 -0.00024;776.55861;2879.74477;,
 -2776.89223;848.50548;1620.31008;,
 -2776.89223;780.50323;1620.31008;,
 -2479.14847;852.44952;1448.40940;,
 -2479.14847;776.55861;1448.40940;,
 -2776.89223;848.50548;-1586.16623;,
 -2776.89223;780.50323;-1586.16623;,
 -2479.14847;852.44952;-1414.26340;,
 -2479.14847;776.55861;-1414.26340;;
 
 251;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,4,7,11;,
 4;8,12,13,9;,
 4;14,10,11,15;,
 4;12,16,17,13;,
 4;18,14,15,19;,
 4;16,20,21,17;,
 4;22,18,19,23;,
 4;20,0,3,21;,
 4;5,22,23,6;,
 4;0,5,4,1;,
 4;3,2,7,6;,
 4;1,4,10,8;,
 4;2,9,11,7;,
 4;8,10,14,12;,
 4;9,13,15,11;,
 4;12,14,18,16;,
 4;13,17,19,15;,
 4;16,18,22,20;,
 4;17,21,23,19;,
 4;20,22,5,0;,
 4;21,3,6,23;,
 4;24,25,26,27;,
 4;28,24,27,29;,
 4;30,28,29,31;,
 4;32,30,31,33;,
 4;34,32,33,35;,
 4;25,34,35,26;,
 4;36,25,24,37;,
 4;37,24,28,38;,
 4;39,40,29,27;,
 4;38,28,30,41;,
 4;40,42,31,29;,
 4;41,30,32,43;,
 4;42,44,33,31;,
 4;43,32,34,45;,
 4;44,46,35,33;,
 4;45,34,25,36;,
 4;47,48,49,50;,
 4;51,47,50,52;,
 4;53,51,52,54;,
 4;55,53,54,56;,
 4;57,55,56,58;,
 4;48,57,58,49;,
 4;59,48,47,60;,
 4;60,47,51,61;,
 4;61,51,53,62;,
 4;62,53,55,63;,
 4;63,55,57,64;,
 4;64,57,48,59;,
 4;65,66,67,68;,
 4;69,65,68,70;,
 4;71,69,70,72;,
 4;73,71,72,74;,
 4;75,73,74,76;,
 4;66,75,76,67;,
 4;77,66,65,78;,
 4;78,65,69,79;,
 4;79,69,71,80;,
 4;80,71,73,81;,
 4;81,73,75,82;,
 4;82,75,66,77;,
 4;83,84,85,86;,
 4;84,87,88,85;,
 4;87,89,90,88;,
 4;89,83,86,90;,
 3;91,84,83;,
 3;91,87,84;,
 3;91,89,87;,
 3;91,83,89;,
 3;92,86,85;,
 3;92,85,88;,
 3;92,88,90;,
 3;92,90,86;,
 4;93,94,95,96;,
 4;94,97,98,95;,
 4;97,99,100,98;,
 4;99,93,96,100;,
 3;101,94,93;,
 3;101,97,94;,
 3;101,99,97;,
 3;101,93,99;,
 3;102,96,95;,
 3;102,95,98;,
 3;102,98,100;,
 3;102,100,96;,
 4;103,104,105,106;,
 4;104,107,108,105;,
 4;107,109,110,108;,
 4;109,103,106,110;,
 3;111,104,103;,
 3;111,107,104;,
 3;111,109,107;,
 3;111,103,109;,
 3;112,106,105;,
 3;112,105,108;,
 3;112,108,110;,
 3;112,110,106;,
 4;113,114,115,116;,
 4;114,117,118,115;,
 4;117,119,120,118;,
 4;119,113,116,120;,
 3;121,114,113;,
 3;121,117,114;,
 3;121,119,117;,
 3;121,113,119;,
 3;122,116,115;,
 3;122,115,118;,
 3;122,118,120;,
 3;122,120,116;,
 4;123,124,125,126;,
 4;124,127,128,125;,
 4;127,129,130,128;,
 4;129,123,126,130;,
 3;131,124,123;,
 3;131,127,124;,
 3;131,129,127;,
 3;131,123,129;,
 3;132,126,125;,
 3;132,125,128;,
 3;132,128,130;,
 3;132,130,126;,
 4;133,134,135,136;,
 4;134,137,138,135;,
 4;137,139,140,138;,
 4;139,133,136,140;,
 3;141,134,133;,
 3;141,137,134;,
 3;141,139,137;,
 3;141,133,139;,
 3;142,136,135;,
 3;142,135,138;,
 3;142,138,140;,
 3;142,140,136;,
 4;143,144,145,146;,
 4;147,143,146,148;,
 4;149,147,148,150;,
 4;151,149,150,152;,
 4;153,151,152,154;,
 4;155,156,157,158;,
 4;144,153,154,145;,
 4;156,144,143,159;,
 4;157,160,146,145;,
 4;159,143,147,161;,
 4;160,162,148,146;,
 4;161,147,149,163;,
 4;162,164,150,148;,
 4;163,149,151,165;,
 4;164,166,152,150;,
 4;165,151,153,155;,
 4;166,158,154,152;,
 4;155,153,144,156;,
 4;158,157,145,154;,
 4;167,168,169,170;,
 4;168,171,172,169;,
 4;171,173,174,172;,
 4;173,167,170,174;,
 3;175,168,167;,
 3;175,171,168;,
 3;175,173,171;,
 3;175,167,173;,
 3;176,170,169;,
 3;176,169,172;,
 3;176,172,174;,
 3;176,174,170;,
 4;177,178,179,180;,
 4;178,181,182,179;,
 4;181,183,184,182;,
 4;183,177,180,184;,
 3;185,178,177;,
 3;185,181,178;,
 3;185,183,181;,
 3;185,177,183;,
 3;186,180,179;,
 3;186,179,182;,
 3;186,182,184;,
 3;186,184,180;,
 4;187,188,189,190;,
 4;188,191,192,189;,
 4;191,193,194,192;,
 4;193,187,190,194;,
 3;195,188,187;,
 3;195,191,188;,
 3;195,193,191;,
 3;195,187,193;,
 3;196,190,189;,
 3;196,189,192;,
 3;196,192,194;,
 3;196,194,190;,
 4;197,198,199,200;,
 4;198,201,202,199;,
 4;201,203,204,202;,
 4;203,197,200,204;,
 3;205,198,197;,
 3;205,201,198;,
 3;205,203,201;,
 3;205,197,203;,
 3;206,200,199;,
 3;206,199,202;,
 3;206,202,204;,
 3;206,204,200;,
 4;207,208,209,210;,
 4;208,211,212,209;,
 4;211,213,214,212;,
 4;213,207,210,214;,
 3;215,208,207;,
 3;215,211,208;,
 3;215,213,211;,
 3;215,207,213;,
 3;216,210,209;,
 3;216,209,212;,
 3;216,212,214;,
 3;216,214,210;,
 4;217,218,219,220;,
 4;218,221,222,219;,
 4;221,223,224,222;,
 4;223,217,220,224;,
 3;225,218,217;,
 3;225,221,218;,
 3;225,223,221;,
 3;225,217,223;,
 3;226,220,219;,
 3;226,219,222;,
 3;226,222,224;,
 3;226,224,220;,
 4;227,228,229,230;,
 4;231,232,233,234;,
 4;228,235,236,229;,
 4;237,231,234,238;,
 4;235,239,240,236;,
 4;241,237,238,242;,
 4;239,243,244,240;,
 4;245,241,242,246;,
 4;243,247,248,244;,
 4;249,245,246,250;,
 4;247,227,230,248;,
 4;232,249,250,233;,
 4;227,232,231,228;,
 4;230,229,234,233;,
 4;228,231,237,235;,
 4;229,236,238,234;,
 4;235,237,241,239;,
 4;236,240,242,238;,
 4;239,241,245,243;,
 4;240,244,246,242;,
 4;243,245,249,247;,
 4;244,248,250,246;,
 4;247,249,232,227;,
 4;248,230,233,250;;
 
 MeshMaterialList {
  5;
  251;
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
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
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
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
  4;;
  Material {
   0.765600;0.800000;0.307200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.690196;0.690196;0.385882;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.084800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.476800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.398400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  128;
  0.500000;0.000000;-0.866025;,
  1.000000;0.000000;0.000000;,
  0.500000;0.000000;0.866025;,
  -0.500000;0.000000;0.866025;,
  -1.000000;0.000000;0.000000;,
  -0.500000;0.000000;0.866025;,
  -1.000000;0.000000;-0.000000;,
  -0.500000;0.000000;-0.866025;,
  0.500000;0.000000;-0.866025;,
  -0.500000;0.000000;-0.866025;,
  0.500000;0.000000;0.866025;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.500000;0.000000;0.866026;,
  -1.000000;0.000000;-0.000001;,
  -0.500000;0.000000;-0.866025;,
  0.500000;0.000000;-0.866025;,
  1.000000;0.000000;0.000000;,
  0.500000;0.000000;0.866025;,
  0.000000;1.000000;0.000000;,
  -0.499999;0.000000;0.866026;,
  -1.000000;0.000000;-0.000001;,
  -0.499999;0.000000;-0.866026;,
  0.500000;0.000000;-0.866026;,
  1.000000;0.000000;0.000000;,
  0.500000;0.000000;0.866026;,
  0.000000;1.000000;0.000000;,
  -0.499999;0.000000;0.866026;,
  -1.000000;0.000000;0.000000;,
  -0.499999;0.000000;-0.866026;,
  0.499999;0.000000;-0.866026;,
  1.000000;0.000000;0.000000;,
  0.499999;0.000000;0.866026;,
  0.000000;1.000000;0.000000;,
  0.300699;0.000000;-0.953719;,
  0.953720;0.000000;0.300697;,
  -0.300715;0.000000;0.953714;,
  0.000000;-1.000000;-0.000000;,
  -0.953715;0.000000;-0.300711;,
  0.000000;1.000000;0.000000;,
  -0.139179;0.000000;-0.990267;,
  0.990270;0.000000;-0.139158;,
  0.139196;0.000000;0.990265;,
  0.000000;-1.000000;-0.000000;,
  -0.990274;0.000000;0.139134;,
  0.000000;1.000000;0.000000;,
  0.366514;0.000000;-0.930413;,
  0.930426;0.000000;0.366481;,
  -0.366516;0.000000;0.930412;,
  0.000000;-1.000000;-0.000000;,
  -0.930416;0.000000;-0.366505;,
  0.000000;1.000000;0.000000;,
  0.782610;0.000000;-0.622513;,
  0.622507;0.000000;0.782614;,
  -0.782611;0.000000;0.622511;,
  0.000000;-1.000000;-0.000000;,
  -0.622494;0.000000;-0.782625;,
  0.000000;1.000000;0.000000;,
  0.782618;0.000000;-0.622502;,
  0.622491;0.000000;0.782627;,
  -0.782604;0.000000;0.622520;,
  0.000000;-1.000000;-0.000000;,
  -0.622503;0.000000;-0.782618;,
  0.000000;1.000000;0.000000;,
  0.961262;0.000000;-0.275635;,
  0.275657;0.000000;0.961256;,
  -0.961261;0.000000;0.275638;,
  0.000000;-1.000000;-0.000000;,
  -0.275604;0.000000;-0.961271;,
  -0.500000;0.000000;-0.866025;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.499999;0.000000;0.866026;,
  -1.000000;0.000000;0.000000;,
  -0.499999;0.000000;-0.866026;,
  0.499999;0.000000;-0.866026;,
  1.000000;0.000000;0.000000;,
  0.499999;0.000000;0.866026;,
  0.000000;1.000000;0.000000;,
  0.300694;0.000000;-0.953721;,
  0.953709;0.000000;0.300732;,
  -0.300719;0.000000;0.953713;,
  0.000000;-1.000000;-0.000000;,
  -0.139186;0.000000;-0.990266;,
  0.990268;0.000000;-0.139170;,
  0.139165;0.000000;0.990269;,
  0.366503;0.000000;-0.930417;,
  0.930422;0.000000;0.366490;,
  -0.366517;0.000000;0.930412;,
  0.782617;0.000000;-0.622504;,
  0.622504;0.000000;0.782616;,
  -0.782611;0.000000;0.622511;,
  0.782620;0.000000;-0.622500;,
  0.622502;0.000000;0.782618;,
  -0.782627;0.000000;0.622491;,
  0.961260;0.000000;-0.275642;,
  0.275652;0.000000;0.961258;,
  -0.961259;0.000000;0.275646;,
  -0.953720;0.000000;-0.300696;,
  -0.990273;0.000000;0.139135;,
  -0.930409;0.000000;-0.366524;,
  -0.622501;0.000000;-0.782619;,
  -0.622479;0.000000;-0.782636;,
  -0.275618;0.000000;-0.961267;,
  0.500000;0.000000;-0.866025;,
  1.000000;0.000000;0.000000;,
  0.500001;0.000000;0.866025;,
  -0.500001;0.000000;0.866025;,
  -1.000000;0.000000;0.000000;,
  -0.500000;0.000000;0.866025;,
  -0.500000;0.000000;-0.866026;,
  0.500000;0.000000;-0.866026;,
  -0.500000;0.000000;-0.866025;,
  0.500000;0.000000;0.866025;,
  0.000000;0.999934;-0.011471;,
  0.009934;0.999934;-0.005735;,
  0.000000;-0.999934;-0.011473;,
  0.009936;-0.999934;-0.005736;,
  0.009934;0.999934;0.005735;,
  0.009936;-0.999934;0.005736;,
  -0.000000;0.999934;0.011471;,
  -0.000000;-0.999934;0.011473;,
  -0.009934;0.999934;0.005735;,
  -0.009936;-0.999934;0.005736;,
  -0.009934;0.999934;-0.005735;,
  -0.009936;-0.999934;-0.005736;;
  251;
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;1,1,1,1;,
  4;6,6,6,6;,
  4;2,2,2,2;,
  4;7,7,7,7;,
  4;3,3,3,3;,
  4;8,8,8,8;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;40,40,40,40;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;35,35,35;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  3;39,39,39;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;46,46,46,46;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  3;45,45,45;,
  4;48,48,48,48;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;52,52,52,52;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  3;51,51,51;,
  4;54,54,54,54;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;58,58,58,58;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;53,53,53;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;64,64,64,64;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;,
  3;59,59,59;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  3;63,63,63;,
  4;66,66,66,66;,
  4;67,67,67,67;,
  4;68,68,68,68;,
  4;70,70,70,70;,
  3;65,65,65;,
  3;65,65,65;,
  3;65,65,65;,
  3;65,65,65;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  3;69,69,69;,
  4;74,74,74,74;,
  4;75,75,75,75;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;78,78,78,78;,
  4;71,71,71,71;,
  4;79,79,79,79;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;81,81,81,81;,
  4;82,82,82,82;,
  4;83,83,83,83;,
  4;100,100,100,100;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  4;85,85,85,85;,
  4;86,86,86,86;,
  4;87,87,87,87;,
  4;101,101,101,101;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  4;88,88,88,88;,
  4;89,89,89,89;,
  4;90,90,90,90;,
  4;102,102,102,102;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  4;91,91,91,91;,
  4;92,92,92,92;,
  4;93,93,93,93;,
  4;103,103,103,103;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  4;94,94,94,94;,
  4;95,95,95,95;,
  4;96,96,96,96;,
  4;104,104,104,104;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  4;97,97,97,97;,
  4;98,98,98,98;,
  4;99,99,99,99;,
  4;105,105,105,105;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;80,80,80;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  3;84,84,84;,
  4;106,106,106,106;,
  4;111,111,111,111;,
  4;107,107,107,107;,
  4;110,110,110,110;,
  4;108,108,108,108;,
  4;112,112,112,112;,
  4;109,109,109,109;,
  4;113,113,113,113;,
  4;110,110,110,110;,
  4;107,107,107,107;,
  4;114,114,114,114;,
  4;115,115,115,115;,
  4;116,116,117,117;,
  4;118,119,119,118;,
  4;117,117,120,120;,
  4;119,121,121,119;,
  4;120,120,122,122;,
  4;121,123,123,121;,
  4;122,122,124,124;,
  4;123,125,125,123;,
  4;124,124,126,126;,
  4;125,127,127,125;,
  4;126,126,116,116;,
  4;127,118,118,127;;
 }
}
