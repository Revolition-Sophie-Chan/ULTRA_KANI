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
 104;
 -1.07189;0.39814;1.19658;,
 0.00391;0.41365;1.96803;,
 -0.12635;0.42243;3.28547;,
 -2.27793;0.39138;1.74256;,
 1.20996;0.42037;1.42204;,
 2.28573;0.43590;2.19350;,
 1.34022;0.41164;0.10460;,
 2.54627;0.41839;-0.44139;,
 0.26443;0.39615;-0.66686;,
 0.39469;0.38739;-1.98430;,
 -0.94160;0.38940;-0.12086;,
 -2.01742;0.37389;-0.89232;,
 -0.25661;0.43114;4.60293;,
 -3.48397;0.38468;2.28854;,
 3.36154;0.45141;2.96496;,
 3.75232;0.42512;-0.98737;,
 0.52494;0.37864;-3.30175;,
 -3.09318;0.35839;-1.66377;,
 -0.38688;0.43991;5.92037;,
 -4.69002;0.37792;2.83454;,
 4.43732;0.46692;3.73641;,
 4.95837;0.43190;-1.53336;,
 0.65522;0.36988;-4.61920;,
 -4.16900;0.34288;-2.43524;,
 -0.51716;0.44868;7.23779;,
 -5.89609;0.37115;3.38052;,
 5.51312;0.48243;4.50787;,
 6.16442;0.43866;-2.07934;,
 0.78549;0.36111;-5.93662;,
 -5.24477;0.32738;-3.20670;,
 -5.89609;0.37115;3.38052;,
 -0.51716;0.44868;7.23779;,
 -0.59374;8.95340;7.17370;,
 -5.97270;8.87589;3.31641;,
 5.51312;0.48243;4.50787;,
 5.43650;8.98713;4.44377;,
 6.16442;0.43866;-2.07934;,
 6.08780;8.94339;-2.14344;,
 0.78549;0.36111;-5.93662;,
 0.70889;8.86583;-6.00073;,
 -5.24477;0.32738;-3.20670;,
 -5.32137;8.83210;-3.27079;,
 -5.89609;0.37115;3.38052;,
 -5.97270;8.87589;3.31641;,
 -0.67034;17.45812;7.10960;,
 -6.04930;17.38061;3.25232;,
 5.35987;17.49187;4.37967;,
 6.01120;17.44811;-2.20754;,
 0.63225;17.37058;-6.06484;,
 -5.39801;17.33681;-3.33489;,
 -6.04930;17.38061;3.25232;,
 -0.74698;25.96285;7.04549;,
 -6.12590;25.88530;3.18824;,
 5.28328;25.99661;4.31557;,
 5.93459;25.95282;-2.27164;,
 0.55566;25.87528;-6.12893;,
 -5.47460;25.84157;-3.39900;,
 -6.12590;25.88530;3.18824;,
 -0.82359;34.46758;6.98140;,
 -6.20252;34.39006;3.12412;,
 5.20665;34.50131;4.25147;,
 5.85798;34.45756;-2.33575;,
 0.47904;34.38002;-6.19302;,
 -5.55120;34.34628;-3.46309;,
 -6.20252;34.39006;3.12412;,
 -0.90020;42.97228;6.91729;,
 -6.27915;42.89474;3.06004;,
 5.13005;43.00601;4.18738;,
 5.78138;42.96227;-2.39984;,
 0.40243;42.88477;-6.25713;,
 -5.62781;42.85097;-3.52718;,
 -6.27915;42.89474;3.06004;,
 -6.27915;42.89474;3.06004;,
 -0.90020;42.97228;6.91729;,
 -0.76994;42.96350;5.59986;,
 -5.07308;42.90152;2.51404;,
 5.13005;43.00601;4.18738;,
 4.05427;42.99052;3.41592;,
 5.78138;42.96227;-2.39984;,
 4.57533;42.95554;-1.85386;,
 0.40243;42.88477;-6.25713;,
 0.27218;42.89350;-4.93968;,
 -5.62781;42.85097;-3.52718;,
 -4.55203;42.86653;-2.75573;,
 -0.63966;42.95473;4.28244;,
 -3.86701;42.90831;1.96804;,
 2.97849;42.97501;2.64447;,
 3.36927;42.94872;-1.30786;,
 0.14190;42.90227;-3.62225;,
 -3.47626;42.88197;-1.98427;,
 -0.50942;42.94600;2.96498;,
 -2.66097;42.91500;1.42207;,
 1.90269;42.95952;1.87300;,
 2.16323;42.94203;-0.76188;,
 0.01162;42.91099;-2.30480;,
 -2.40044;42.89749;-1.21282;,
 -0.37917;42.93728;1.64753;,
 -1.45493;42.92176;0.87608;,
 0.82691;42.94400;1.10155;,
 0.95716;42.93532;-0.21590;,
 -0.11862;42.91979;-0.98735;,
 -1.32467;42.91306;-0.44137;,
 0.13417;0.40489;0.65058;,
 -0.24888;42.92855;0.33009;;
 
 90;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,0,3,11;,
 4;3,2,12,13;,
 4;2,5,14,12;,
 4;5,7,15,14;,
 4;7,9,16,15;,
 4;9,11,17,16;,
 4;11,3,13,17;,
 4;13,12,18,19;,
 4;12,14,20,18;,
 4;14,15,21,20;,
 4;15,16,22,21;,
 4;16,17,23,22;,
 4;17,13,19,23;,
 4;19,18,24,25;,
 4;18,20,26,24;,
 4;20,21,27,26;,
 4;21,22,28,27;,
 4;22,23,29,28;,
 4;23,19,25,29;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;33,32,44,45;,
 4;32,35,46,44;,
 4;35,37,47,46;,
 4;37,39,48,47;,
 4;39,41,49,48;,
 4;41,43,50,49;,
 4;45,44,51,52;,
 4;44,46,53,51;,
 4;46,47,54,53;,
 4;47,48,55,54;,
 4;48,49,56,55;,
 4;49,50,57,56;,
 4;52,51,58,59;,
 4;51,53,60,58;,
 4;53,54,61,60;,
 4;54,55,62,61;,
 4;55,56,63,62;,
 4;56,57,64,63;,
 4;59,58,65,66;,
 4;58,60,67,65;,
 4;60,61,68,67;,
 4;61,62,69,68;,
 4;62,63,70,69;,
 4;63,64,71,70;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,72,75,83;,
 4;75,74,84,85;,
 4;74,77,86,84;,
 4;77,79,87,86;,
 4;79,81,88,87;,
 4;81,83,89,88;,
 4;83,75,85,89;,
 4;85,84,90,91;,
 4;84,86,92,90;,
 4;86,87,93,92;,
 4;87,88,94,93;,
 4;88,89,95,94;,
 4;89,85,91,95;,
 4;91,90,96,97;,
 4;90,92,98,96;,
 4;92,93,99,98;,
 4;93,94,100,99;,
 4;94,95,101,100;,
 4;95,91,97,101;,
 3;1,0,102;,
 3;4,1,102;,
 3;6,4,102;,
 3;8,6,102;,
 3;10,8,102;,
 3;0,10,102;,
 3;97,96,103;,
 3;96,98,103;,
 3;98,99,103;,
 3;99,100,103;,
 3;100,101,103;,
 3;101,97,103;;
 
 MeshMaterialList {
  1;
  90;
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
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  98;
  0.009010;-0.999931;0.007535;,
  0.009001;-0.999931;0.007545;,
  0.008999;-0.999931;0.007535;,
  0.009005;-0.999931;0.007526;,
  0.009005;-0.999931;0.007531;,
  0.009007;-0.999931;0.007531;,
  0.009006;-0.999931;0.007537;,
  0.009004;-0.999931;0.007543;,
  0.009004;-0.999931;0.007537;,
  0.009006;-0.999931;0.007533;,
  0.009005;-0.999931;0.007534;,
  0.009005;-0.999931;0.007533;,
  0.009001;-0.999931;0.007538;,
  0.009004;-0.999931;0.007536;,
  0.009009;-0.999931;0.007536;,
  0.009008;-0.999931;0.007535;,
  0.009006;-0.999931;0.007533;,
  0.009004;-0.999931;0.007536;,
  0.009006;-0.999931;0.007537;,
  0.009007;-0.999931;0.007539;,
  0.009016;-0.999931;0.007540;,
  0.009014;-0.999931;0.007534;,
  0.009009;-0.999931;0.007535;,
  0.009009;-0.999931;0.007539;,
  0.009009;-0.999931;0.007537;,
  0.009009;-0.999931;0.007541;,
  0.009017;-0.999931;0.007542;,
  0.009016;-0.999931;0.007536;,
  0.009009;-0.999931;0.007539;,
  0.009010;-0.999931;0.007540;,
  -0.582763;0.000876;0.812642;,
  0.412342;0.010580;0.910968;,
  0.995107;0.009706;0.098327;,
  0.582766;-0.000875;-0.812640;,
  -0.412341;-0.010581;-0.910968;,
  -0.582763;0.000875;0.812642;,
  0.412342;0.010581;0.910967;,
  0.995107;0.009705;0.098328;,
  0.582765;-0.000875;-0.812640;,
  -0.412342;-0.010581;-0.910968;,
  -0.582763;0.000875;0.812642;,
  0.412341;0.010581;0.910968;,
  0.995107;0.009705;0.098328;,
  0.582765;-0.000876;-0.812641;,
  -0.412342;-0.010579;-0.910968;,
  -0.582763;0.000875;0.812642;,
  0.412341;0.010580;0.910968;,
  0.995107;0.009705;0.098329;,
  0.582764;-0.000876;-0.812641;,
  -0.412343;-0.010580;-0.910967;,
  -0.582763;0.000875;0.812642;,
  0.412340;0.010580;0.910968;,
  0.995107;0.009704;0.098329;,
  0.582764;-0.000876;-0.812641;,
  -0.412344;-0.010580;-0.910967;,
  -0.009015;0.999931;-0.007532;,
  -0.009010;0.999931;-0.007533;,
  -0.009018;0.999931;-0.007538;,
  -0.009019;0.999931;-0.007527;,
  -0.009011;0.999931;-0.007524;,
  -0.009015;0.999931;-0.007533;,
  -0.008997;0.999931;-0.007534;,
  -0.009006;0.999931;-0.007528;,
  -0.009013;0.999931;-0.007533;,
  -0.009010;0.999931;-0.007532;,
  -0.009006;0.999931;-0.007523;,
  -0.009000;0.999931;-0.007530;,
  -0.009016;0.999931;-0.007528;,
  -0.009007;0.999931;-0.007527;,
  -0.008992;0.999931;-0.007522;,
  -0.008989;0.999931;-0.007539;,
  -0.009005;0.999931;-0.007556;,
  -0.009017;0.999931;-0.007541;,
  -0.009036;0.999931;-0.007512;,
  -0.009008;0.999931;-0.007523;,
  -0.008988;0.999931;-0.007507;,
  -0.009003;0.999931;-0.007524;,
  -0.009009;0.999931;-0.007559;,
  -0.009021;0.999931;-0.007533;,
  0.009000;-0.999931;0.007530;,
  -0.009007;0.999931;-0.007515;,
  -0.582763;0.000876;0.812641;,
  0.412340;0.010580;0.910968;,
  0.995107;0.009706;0.098326;,
  0.582766;-0.000876;-0.812640;,
  -0.412341;-0.010580;-0.910968;,
  -0.995107;-0.009705;-0.098328;,
  -0.995107;-0.009705;-0.098327;,
  -0.995107;-0.009704;-0.098325;,
  -0.995107;-0.009704;-0.098326;,
  -0.995107;-0.009705;-0.098328;,
  -0.995107;-0.009705;-0.098329;,
  -0.009026;0.999931;-0.007534;,
  -0.009009;0.999931;-0.007536;,
  -0.009003;0.999931;-0.007534;,
  -0.009004;0.999931;-0.007530;,
  -0.009012;0.999931;-0.007539;,
  -0.009029;0.999931;-0.007540;;
  90;
  4;0,1,7,6;,
  4;1,2,8,7;,
  4;2,3,9,8;,
  4;3,4,10,9;,
  4;4,5,11,10;,
  4;5,0,6,11;,
  4;6,7,13,12;,
  4;7,8,14,13;,
  4;8,9,15,14;,
  4;9,10,16,15;,
  4;10,11,17,16;,
  4;11,6,12,17;,
  4;12,13,19,18;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;15,16,22,21;,
  4;16,17,23,22;,
  4;17,12,18,23;,
  4;18,19,25,24;,
  4;19,20,26,25;,
  4;20,21,27,26;,
  4;21,22,28,27;,
  4;22,23,29,28;,
  4;23,18,24,29;,
  4;81,81,30,30;,
  4;82,82,31,31;,
  4;83,83,32,32;,
  4;84,84,33,33;,
  4;85,85,34,34;,
  4;86,86,87,87;,
  4;30,30,35,35;,
  4;31,31,36,36;,
  4;32,32,37,37;,
  4;33,33,38,38;,
  4;34,34,39,39;,
  4;87,87,88,88;,
  4;35,35,40,40;,
  4;36,36,41,41;,
  4;37,37,42,42;,
  4;38,38,43,43;,
  4;39,39,44,44;,
  4;88,88,89,89;,
  4;40,40,45,45;,
  4;41,41,46,46;,
  4;42,42,47,47;,
  4;43,43,48,48;,
  4;44,44,49,49;,
  4;89,89,90,90;,
  4;45,45,50,50;,
  4;46,46,51,51;,
  4;47,47,52,52;,
  4;48,48,53,53;,
  4;49,49,54,54;,
  4;90,90,91,91;,
  4;92,93,56,55;,
  4;93,94,57,56;,
  4;94,95,58,57;,
  4;95,96,59,58;,
  4;96,97,60,59;,
  4;97,92,55,60;,
  4;55,56,62,61;,
  4;56,57,63,62;,
  4;57,58,64,63;,
  4;58,59,65,64;,
  4;59,60,66,65;,
  4;60,55,61,66;,
  4;61,62,68,67;,
  4;62,63,69,68;,
  4;63,64,70,69;,
  4;64,65,71,70;,
  4;65,66,72,71;,
  4;66,61,67,72;,
  4;67,68,74,73;,
  4;68,69,75,74;,
  4;69,70,76,75;,
  4;70,71,77,76;,
  4;71,72,78,77;,
  4;72,67,73,78;,
  3;1,0,79;,
  3;2,1,79;,
  3;3,2,79;,
  3;4,3,79;,
  3;5,4,79;,
  3;0,5,79;,
  3;73,74,80;,
  3;74,75,80;,
  3;75,76,80;,
  3;76,77,80;,
  3;77,78,80;,
  3;78,73,80;;
 }
 MeshTextureCoords {
  104;
  0.515625;0.129187;,
  0.484375;0.129187;,
  0.468750;0.102123;,
  0.531250;0.102123;,
  0.468750;0.156250;,
  0.437500;0.156250;,
  0.484375;0.183313;,
  0.468750;0.210377;,
  0.515625;0.183313;,
  0.531250;0.210377;,
  0.531250;0.156250;,
  0.562500;0.156250;,
  0.453125;0.075060;,
  0.546875;0.075060;,
  0.406250;0.156250;,
  0.453125;0.237440;,
  0.546875;0.237440;,
  0.593750;0.156250;,
  0.437500;0.047997;,
  0.562500;0.047997;,
  0.375000;0.156250;,
  0.437500;0.264503;,
  0.562500;0.264503;,
  0.625000;0.156250;,
  0.421875;0.020934;,
  0.578125;0.020934;,
  0.343750;0.156250;,
  0.421875;0.291566;,
  0.578125;0.291566;,
  0.656250;0.156250;,
  0.375000;0.312500;,
  0.416667;0.312500;,
  0.416667;0.387688;,
  0.375000;0.387688;,
  0.458333;0.312500;,
  0.458333;0.387688;,
  0.500000;0.312500;,
  0.500000;0.387688;,
  0.541667;0.312500;,
  0.541667;0.387688;,
  0.583333;0.312500;,
  0.583333;0.387688;,
  0.625000;0.312500;,
  0.625000;0.387688;,
  0.416667;0.462876;,
  0.375000;0.462876;,
  0.458333;0.462876;,
  0.500000;0.462876;,
  0.541667;0.462876;,
  0.583333;0.462876;,
  0.625000;0.462876;,
  0.416667;0.538064;,
  0.375000;0.538064;,
  0.458333;0.538064;,
  0.500000;0.538064;,
  0.541667;0.538064;,
  0.583333;0.538064;,
  0.625000;0.538064;,
  0.416667;0.613252;,
  0.375000;0.613252;,
  0.458333;0.613252;,
  0.500000;0.613252;,
  0.541667;0.613252;,
  0.583333;0.613252;,
  0.625000;0.613252;,
  0.416667;0.688440;,
  0.375000;0.688440;,
  0.458333;0.688440;,
  0.500000;0.688440;,
  0.541667;0.688440;,
  0.583333;0.688440;,
  0.625000;0.688440;,
  0.578125;0.979066;,
  0.421875;0.979066;,
  0.437500;0.952003;,
  0.562500;0.952003;,
  0.343750;0.843750;,
  0.375000;0.843750;,
  0.421875;0.708434;,
  0.437500;0.735497;,
  0.578125;0.708434;,
  0.562500;0.735497;,
  0.656250;0.843750;,
  0.625000;0.843750;,
  0.453125;0.924940;,
  0.546875;0.924940;,
  0.406250;0.843750;,
  0.453125;0.762560;,
  0.546875;0.762560;,
  0.593750;0.843750;,
  0.468750;0.897877;,
  0.531250;0.897877;,
  0.437500;0.843750;,
  0.468750;0.789623;,
  0.531250;0.789623;,
  0.562500;0.843750;,
  0.484375;0.870813;,
  0.515625;0.870813;,
  0.468750;0.843750;,
  0.484375;0.816687;,
  0.515625;0.816687;,
  0.531250;0.843750;,
  0.500000;0.150000;,
  0.500000;0.837500;;
 }
}